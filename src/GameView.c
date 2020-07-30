////////////////////////////////////////////////////////////////////////
// COMP2521 20T2 ... the Fury of Dracula
// GameView.c: GameView ADT implementation
//
// 2014-07-01	v1.0	Team Dracula <cs2521@cse.unsw.edu.au>
// 2017-12-01	v1.1	Team Dracula <cs2521@cse.unsw.edu.au>
// 2018-12-31	v2.0	Team Dracula <cs2521@cse.unsw.edu.au>
// 2020-07-10   v3.0    Team Dracula <cs2521@cse.unsw.edu.au>
//
////////////////////////////////////////////////////////////////////////

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Game.h"
#include "GameView.h"
#include "Map.h"
#include "Places.h"

#define ARRAY_BUFFER 32
#define NUM_CHAR_IN_ROUND 40
#define NUM_CHAR_IN_TURN 8
#define MAX_ROUNDS (GAME_START_SCORE)
#define MAX_ENCOUNTERS 6

#define NUM_PARAM 2
#define IS_KNOWN_PARAM 0
#define PLACE_ID_PARAM 1

typedef struct gameView
{
	/* Game information */
	int score;			  // Number of current score
	Map map;			  // Map ADT
	Round round;		  // Number of current round
	Player currentPlayer; // Who the current player is

	/* Encounter locations */
	PlaceId trapLocations[NUM_PARAM][MAX_ENCOUNTERS]; // Usage: [PARAM][PLACE_ID]
	PlaceId vampireLocation[NUM_PARAM];				  // Usage: [0] = IS_KNOWN_PARAM, [1] = PLACE_ID_PARAM,
	PlaceId draculaRumour[NUM_PARAM];				  // Usage: [0] = IS_KNOWN_PARAM, [1] = PLACE_ID_PARAM

	/* Player information */
	int healths[NUM_PLAYERS];						  // Usage: [PLAYER]
	PlaceId moveHistory[NUM_PLAYERS][MAX_ROUNDS];	  // Usage: [PLAYER][ROUND]
	PlaceId locationHistory[NUM_PLAYERS][MAX_ROUNDS]; // Usage: [PLAYER][ROUND]
	int research;									  // Progress of research
} gameView;

/******************************************************************************
 * 								Static Functions							  *
 ******************************************************************************/

/* Gameplay functions */
static void playGame(GameView gv, char *pastPlays, Message messages[]);
static void playDracula(GameView gv, char *play, Message messages[], PlaceId location);
static void playHunter(GameView gv, char *play, Message messages[], PlaceId location);

/* Update history functions */
static void updateMoveHistory(GameView gv, PlaceId move);
static void updateLocationHistory(GameView gv, PlaceId location);

/* Setters */
static void setTrap(GameView gv, PlaceId location);
static void setVampire(GameView gv, PlaceId location);
static void setDraculaRumour(GameView gv);

/* Destroyers */
static void removeTrap(GameView gv, PlaceId location);
static void removeVampire(GameView gv);
static void expireTrap(GameView gv);
static void expireVampire(GameView gv);

/* Check if location is known to hunters */
static bool isKnownTrapLocation(GameView gv, PlaceId location);
static bool isKnownVampireLocation(GameView gv, PlaceId location);
static bool isKnownDraculaLocation(GameView gv, PlaceId location);

/* Revealing functions */
static int revealTrap(GameView gv, PlaceId location);
static int revealVampire(GameView gv, PlaceId location);
static int revealDracula(GameView gv, PlaceId location);

/******************************************************************************
 * 								GameView ADT							 	  *
 ******************************************************************************/

void *GvNew(char *pastPlays, Message messages[])
{
	// Initialise the game
	GameView gv = &(gameView){
		.score = GAME_START_SCORE,
		.map = MapNew(),
		.round = 0,
		.currentPlayer = PLAYER_LORD_GODALMING,
		.trapLocations = {{0}},
		.vampireLocation = {0},
		.draculaRumour = {0},
		.healths = {
			[PLAYER_LORD_GODALMING] = GAME_START_HUNTER_LIFE_POINTS,
			[PLAYER_DR_SEWARD] = GAME_START_HUNTER_LIFE_POINTS,
			[PLAYER_VAN_HELSING] = GAME_START_HUNTER_LIFE_POINTS,
			[PLAYER_MINA_HARKER] = GAME_START_HUNTER_LIFE_POINTS,
			[PLAYER_DRACULA] = GAME_START_BLOOD_POINTS,
		},
		.moveHistory = {{0}},
		.locationHistory = {{0}},
	};

	// GameView gv = malloc(sizeof(gameView));
	// gv->score = GAME_START_SCORE;
	// gv->map = MapNew();
	// gv->round = 0;
	// gv->currentPlayer = PLAYER_LORD_GODALMING;
	// gv->tra

	if (gv == NULL)
	{
		fprintf(stderr, "Couldn't allocate GameView!\n");
		exit(EXIT_FAILURE);
	}

	if (*pastPlays != '\0')
		playGame(gv, pastPlays, messages);

	return gv;
}

void GvFree(GameView gv)
{
	free(gv);
}

/******************************************************************************
 * 								Game State Info							  	  *
 ******************************************************************************/

Round GvGetRound(GameView gv)
{
	return gv->round;
}

Player GvGetPlayer(GameView gv)
{
	return gv->currentPlayer;
}

int GvGetScore(GameView gv)
{
	return gv->score;
}

int GvGetHealth(GameView gv, Player player)
{
	return gv->healths[player];
}

PlaceId GvGetPlayerLocation(GameView gv, Player player)
{
	// Get location of requested player.
	int location = gv->locationHistory[player][gv->round];

	// Invalid location.
	if (location == NOWHERE)
		return NOWHERE;

	// If requested player is not Dracula or Dracula requested a player.
	if (player != PLAYER_DRACULA || gv->currentPlayer == PLAYER_DRACULA)
		return location;

	// Hunters ask for Dracula's location.
	if (isKnownDraculaLocation(gv, location))
		return location;

	// Dracula's location is hidden.
	if (placeIdToType(location) == SEA)
		return SEA_UNKNOWN;
	return CITY_UNKNOWN;
}

PlaceId GvGetVampireLocation(GameView gv)
{
	// Get vampire location
	int location = gv->vampireLocation[PLACE_ID_PARAM];

	// Vampire doesn't exist
	if (location == NOWHERE)
		return NOWHERE;

	// Vampire location is known
	if (isKnownVampireLocation(gv, location))
		return location;

	// Vampire location is unknown
	return CITY_UNKNOWN;
}

/**
 * Returns trap locations from the GameView struct and updates numTraps.
 * 
 * Assumes the array is in order with NULL elements towards the end.
 */
PlaceId *GvGetTrapLocations(GameView gv, int *numTraps)
{
	*numTraps = 0;
	for (; *numTraps < MAX_ENCOUNTERS; numTraps++)
		if (&gv->trapLocations[PLACE_ID_PARAM][*numTraps] == NULL)
			break;

	return &gv->trapLocations[PLACE_ID_PARAM][0];
}

/******************************************************************************
 * 								Game History								  *
 ******************************************************************************/

PlaceId *GvGetMoveHistory(GameView gv, Player player, int *numReturnedMoves,
						  bool *canFree)
{
	return GvGetLastMoves(gv, player, gv->round, numReturnedMoves, canFree);
}

PlaceId *GvGetLastMoves(GameView gv, Player player, int numMoves,
						int *numReturnedMoves, bool *canFree)
{
	*canFree = false;
	int j = 0; // counter for returned index

	// Iterate 'numMoves' backwards through moveHistory
	for (int i = gv->round; i > gv->round - numMoves; i--, j++)
		if (&gv->moveHistory[player][i] == NULL)
			break;

	*numReturnedMoves = j;

	return &gv->moveHistory[player][gv->round - *numReturnedMoves];
}

PlaceId *GvGetLocationHistory(GameView gv, Player player,
							  int *numReturnedLocs, bool *canFree)
{
	return GvGetLastLocations(gv, player, gv->round, numReturnedLocs, canFree);
}

PlaceId *GvGetLastLocations(GameView gv, Player player, int numLocs,
							int *numReturnedLocs, bool *canFree)
{
	*canFree = false;
	int j = 0; // counter for returned index

	// Iterate 'numMoves' backwards through locationHistory
	for (int i = gv->round; i > gv->round - numLocs; i--, j++)
		if (&gv->locationHistory[player][i] == NULL)
			break;

	*numReturnedLocs = j;

	return &gv->locationHistory[player][gv->round - *numReturnedLocs];
}

/******************************************************************************
 * 								Making a Move								  *
 ******************************************************************************/

PlaceId *GvGetReachable(GameView gv, Player player, Round round,
						PlaceId from, int *numReturnedLocs)
{
	return GvGetReachableByType(gv, player, round, from, true, true, true, numReturnedLocs)
}

PlaceId *GvGetReachableByType(GameView gv, Player player, Round round,
							  PlaceId from, bool road, bool rail,
							  bool boat, int *numReturnedLocs)
{
	PlaceId *LocationList = malloc(NUM_REAL_PLACES * sizeof(PlaceId));
	int visited[NUM_REAL_PLACES] = {0};

	numReturnedLocs = 0;
	LocationList[*numReturnedLocs++] = from;
	visited[from] = 1;

	for (ConnList current = g->map->connections[from]; !current; current = current->next)
	{
		// 1.  
		// 2. 
		// 3. 
		if ((current->type == ROAD) &&
			(road = true) &&
			(visited[current->p] == 0))
		{
			// connListInsert(LocationList, current);
			LocationList[numReturnedLocs++] = current->p;
			visited[current->p] = 1;
		}
		// 1.
		// 2.
		// 3.
		if (current->type == BOAT) &&
			(boat = true) &&
			(visited[current->p] == 0))
		{
			LocationList[numReturnedLocs++] = current->p
			visited[current->p] = 1;	
		}
	}
	//
	//
	//
	if ((player != PLAYER_DRACULA) && 
		(rail == true))
	{
		int sum = (player + round) % 4;
		for (i = sum; i >= 0; i--)
		{
			findRailConnections(g->map,from, i, visited, LocationList, numReturnedLocs);
		}
	}
	return LocationList;
}

static PlaceId findRailConnections(Map m, PlaceId from, int sum, int *visited, int *LocationList, int *numReturnedLocs)
{
	if (sum > 0)
	{
		for (ConnList current = g->map->connections[from]; !current; current = current->next) 
		{
			if (visited[current->p] == 0)
			{
				LocationList[numReturnedLocs++] = current->p;
				visited[current->p] = 1;
			}
		}
	} else {
		return NULL;
	}
}

/******************************************************************************
 * 								Play Functions							  	  *
 ******************************************************************************/

/**
 * 
 */
static void playGame(GameView gv, char *pastPlays, Message messages[])
{
	/* Game */
	char *end, *tmp;
	tmp = end = strdup(pastPlays);
	if (end == NULL)
	{
		fprintf(stderr, "ERROR: Could not allocate memory for strdup(pastPlays).\n");
		exit(EXIT_FAILURE);
	}

	char *play;
	while ((play = strsep(&end, " ")) != NULL)
	{
		if (strlen(play) != 7)
		{
			fprintf(stderr, "ERROR: Invalid length, %ld, of play string.\n", strlen(play));
			// exit(EXIT_FAILURE);
		}

		// switch (play[0])
		// {
		// case 'G':
		// 	gv->currentPlayer = PLAYER_LORD_GODALMING;
		// 	break;
		// case 'S':
		// 	gv->currentPlayer = PLAYER_DR_SEWARD;
		// 	break;
		// case 'H':
		// 	gv->currentPlayer = PLAYER_VAN_HELSING;
		// 	break;
		// case 'M':
		// 	gv->currentPlayer = PLAYER_MINA_HARKER;
		// 	break;
		// case 'D':
		// 	gv->currentPlayer = PLAYER_DRACULA;
		// 	break;
		// default:
		// 	fprintf(stderr, "ERROR: Invalid char, %c, in play[%d].\n", play[0], 0);
		// 	// exit(EXIT_FAILURE);
		// }

		/* Move Phase */
		char loc[3] = {[0] = *(play + 1), [1] = *(play + 2), [2] = '\0'};
		PlaceId location = placeAbbrevToId(loc);
		updateMoveHistory(gv, location);
		updateLocationHistory(gv, location);

		/* Action Phase */
		if (gv->currentPlayer == PLAYER_DRACULA)
			playDracula(gv, play, messages, location);
		else
			playHunter(gv, play, messages, location);

		gv->currentPlayer = (gv->currentPlayer + 1) % NUM_PLAYERS;

		// Game over
		if (gv->healths[PLAYER_DRACULA] <= 0 || gv->score <= 0)
			return;
	}

	free(tmp);
}

/**
 * Play strings are interpretted differently depending on the player type.
 * Order of char matters in a Dracula string.
 */
static void playDracula(GameView gv, char *play, Message messages[], PlaceId location)
{
	// Interpret 4th char
	switch (play[3])
	{
	case 'T':
		setTrap(gv, location);
		break;
	case '.':
		break;
	default:
		fprintf(stderr, "ERROR: Invalid char, %c, in play[%d].\n", play[3], 3);
		// exit(EXIT_FAILURE);
	}

	// Interpret 5th char
	switch (play[4])
	{
	case 'V':
		setVampire(gv, location);
		break;
	case '.':
		break;
	default:
		fprintf(stderr, "ERROR: Invalid char, %c, in play[%d].\n", play[4], 4);
		// exit(EXIT_FAILURE);
	}

	// Interpret 6th char
	switch (play[5])
	{
	case 'V':
		expireVampire(gv);
		break;
	case 'M':
		expireTrap(gv);
		break;
	case '.':
		break;
	default:
		fprintf(stderr, "ERROR: Invalid char, %c, in play[%d].\n", play[5], 5);
		// exit(EXIT_FAILURE);
	}

	// Interpret 7th char
	switch (play[6])
	{
	case '.':
		break;
	default:
		fprintf(stderr, "ERROR: Invalid char, %c, in play[%d].\n", play[6], 6);
		// exit(EXIT_FAILURE);
	}

	gv->round++;
}

static void playHunter(GameView gv, char *play, Message messages[], PlaceId location)
{
	for (int i = 3; i < 7; i++)
		switch (play[i])
		{
		case 'T':
			revealTrap(gv, location);
			break;
		case 'V':
			revealVampire(gv, location);
			break;
		case 'D':
			revealDracula(gv, location);
			break;
		case '.':
			break;
		default:
			fprintf(stderr, "ERROR: Invalid char, %c, in play[%d].\n", play[3], 3);
			// exit(EXIT_FAILURE);
		}
}

/******************************************************************************
 * 								Static Functions							  *
 ******************************************************************************/

/**
 * Appends the given move to the moveHistory.
 */
static void updateMoveHistory(GameView gv, PlaceId move)
{
	gv->moveHistory[gv->currentPlayer][gv->round] = move;
}

/**
 * Behaves the same as updateMoveHistory but masks Dracula's location.
 */
static void updateLocationHistory(GameView gv, PlaceId location)
{
	if (gv->currentPlayer == PLAYER_DRACULA)
	{
		if (location == CASTLE_DRACULA)
			gv->locationHistory[gv->currentPlayer][gv->round] = CASTLE_DRACULA;
		else if (placeIsLand(location))
			gv->locationHistory[gv->currentPlayer][gv->round] = CITY_UNKNOWN;
		else
			gv->locationHistory[gv->currentPlayer][gv->round] = SEA_UNKNOWN;
	}
	else
		gv->locationHistory[gv->currentPlayer][gv->round] = location;
}

/**
 * Set a trap in a given location.
 */
static void setTrap(GameView gv, PlaceId location)
{
	gv->trapLocations[PLACE_ID_PARAM][gv->round] = location;
	gv->trapLocations[IS_KNOWN_PARAM][gv->round] = false;
}

/**
 * Set a vampire in a given location.
 */
static void setVampire(GameView gv, PlaceId location)
{
	gv->vampireLocation[PLACE_ID_PARAM] = location;
	gv->vampireLocation[IS_KNOWN_PARAM] = false;
}

/**
 * Set a rumour of Dracula's location.
 */
static void setDraculaRumour(GameView gv)
{
	gv->vampireLocation[PLACE_ID_PARAM] = gv->locationHistory[PLAYER_DRACULA][gv->round];
	gv->vampireLocation[IS_KNOWN_PARAM] = false;
}

/**
 * Removes a trap in the given location by splicing the trap from the array.
 */
static void removeTrap(GameView gv, PlaceId location)
{
	int i = 0;
	for (; i < MAX_ENCOUNTERS - 1; i++)
		if (gv->trapLocations[PLACE_ID_PARAM][i] == location)
			break;

	for (int j = i; j < MAX_ENCOUNTERS - 1; j++)
	{
		gv->trapLocations[PLACE_ID_PARAM][j] = gv->trapLocations[PLACE_ID_PARAM][j + 1];
		gv->trapLocations[IS_KNOWN_PARAM][j] = gv->trapLocations[IS_KNOWN_PARAM][j + 1];
	}
}

/**
 * Remove the vampire by setting its location to NOWHERE and is known parameter
 * to false.
 */
static void removeVampire(GameView gv)
{
	gv->vampireLocation[PLACE_ID_PARAM] = NOWHERE;
	gv->vampireLocation[IS_KNOWN_PARAM] = false;
}

/**
 * Oldest trap malfunctions which removes it from the game.
 */
static void expireTrap(GameView gv)
{
	removeTrap(gv, gv->trapLocations[PLACE_ID_PARAM][0]);
}

/**
 * Vampire matures which removes it from the game and deducts the score.
 */
static void expireVampire(GameView gv)
{
	removeVampire(gv);
	gv->score -= SCORE_LOSS_VAMPIRE_MATURES;
}

/**
 * If the given location is the location of a trap and its location is known
 * then return true, otherwise false.
 */
static bool isKnownTrapLocation(GameView gv, PlaceId location)
{
	for (int i = 0; i < MAX_ENCOUNTERS; i++)
		if (gv->trapLocations[PLACE_ID_PARAM][i] == location)
			if (gv->trapLocations[IS_KNOWN_PARAM][i] == true)
				return true;

	return false;
}

/**
 * If the given location is the location of the vampire and the sightings are
 * true then return true, otherwise false.
 */
static bool isKnownVampireLocation(GameView gv, PlaceId location)
{
	if (gv->vampireLocation[PLACE_ID_PARAM] == location)
		if (gv->vampireLocation[IS_KNOWN_PARAM] == true)
			return true;

	return false;
}

/**
 * If the given location is the location of Dracula and the sightings are true
 * then return true, otherwise false.
 */
static bool isKnownDraculaLocation(GameView gv, PlaceId location)
{
	if (gv->draculaRumour[PLACE_ID_PARAM] == location)
		if (gv->draculaRumour[IS_KNOWN_PARAM] == true)
			return true;

	return false;
}

/**
 * Reveals all traps in a single location if given location matches.
 * 
 * Returns number of traps on reveal else 0 if no traps are revealed.
 */
static int revealTrap(GameView gv, PlaceId location)
{
	int numTraps = 0;
	for (int i = 0; i < TRAIL_SIZE; i++)
		if (location == gv->trapLocations[PLACE_ID_PARAM][i])
		{
			gv->trapLocations[IS_KNOWN_PARAM][i] = true;
			numTraps++;
		}
	return numTraps;
}

/**
 * Reveals the vampire if given location matches.
 * 
 * Returns true on reveal else false.
 */
static int revealVampire(GameView gv, PlaceId location)
{
	int isVampire = 0;
	if (location == gv->vampireLocation[PLACE_ID_PARAM])
	{
		gv->vampireLocation[IS_KNOWN_PARAM] = true;
		isVampire++;
	}
	return isVampire;
}

/**
 * Reveals Dracula's location if given location matches.
 * 
 * Returns true on reveal else false.
 */
static int revealDracula(GameView gv, PlaceId location)
{
	int isDracula = 0;
	if (location == gv->draculaRumour[PLACE_ID_PARAM])
	{
		gv->draculaRumour[IS_KNOWN_PARAM] = true;
		isDracula++;
	}
	return isDracula;
}
