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
#define MAX_ROUNDS 366
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
	PlaceId draculaSightings[NUM_PARAM];			  // Usage: [0] = IS_KNOWN_PARAM, [1] = PLACE_ID_PARAM

	/* Player information */
	int healths[NUM_PLAYERS];						  // Array of players healths
	PlaceId moveHistory[NUM_PLAYERS][MAX_ROUNDS];	  // Array of player move histories
	PlaceId locationHistory[NUM_PLAYERS][MAX_ROUNDS]; // Array of player location histories
	int research;									  // Progress of research
} gameView;

/******************************************************************************
 * 								Static Functions							  *
 ******************************************************************************/

/**
 * Parse through each char of play string which is 7 char long
 * 		e.g. ABBCCCD
 * 			A: 	'G', 'S', 'H', 'M', 'D', represents the player
 * 			B: 	'LO', location to move to
 * 				'C?', city unknown
 * 			C: 	'T', Dracula places trap or hunter encounters trap;
 * 				'V', Dracula places vampire or hunter encounters vampire
 * 				'D', Hunter encounters Dracula
 * 				'M', Trap malfunction
 */

static void playGame(GameView gv, char *pastPlays, Message messages[]);
static void removeTrap(GameView gv, PlaceId location);
static void removeVampire(GameView gv);
static void expireEncounter(GameView gv);
// static bool isKnownTrapLocation(GameView gv, PlaceId location);
static bool isKnownVampireLocation(GameView gv, PlaceId location);
static bool isKnownDraculaLocation(GameView gv, PlaceId location);
static int revealTrap(GameView gv, PlaceId location);
static int revealVampire(GameView gv, PlaceId location);

/******************************************************************************
 * 								GameView ADT							 	  *
 ******************************************************************************/

GameView GvNew(char *pastPlays, Message messages[])
{
	// Initialise the game
	GameView gv = &(gameView){
		.score = GAME_START_SCORE,
		.map = MapNew(),
		.round = 0,
		.currentPlayer = PLAYER_LORD_GODALMING,
		.trapLocations = {{0}},
		.vampireLocation = {0},
		.draculaSightings = {0},
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

	if (gv == NULL)
	{
		fprintf(stderr, "ERROR: Could not allocate memory for GameView\n");
		exit(EXIT_FAILURE);
	}

	playGame(gv, pastPlays, messages);

	return gv;
}

void GvFree(GameView gv)
{
	MapFree(gv->map);
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
	// TODO: REPLACE THIS WITH YOUR OWN IMPLEMENTATION
	*numReturnedLocs = 0;
	return NULL;
}

PlaceId *GvGetReachableByType(GameView gv, Player player, Round round,
							  PlaceId from, bool road, bool rail,
							  bool boat, int *numReturnedLocs)
{
	// TODO: REPLACE THIS WITH YOUR OWN IMPLEMENTATION
	*numReturnedLocs = 0;
	return NULL;
}

/******************************************************************************
 * 								Static Functions							  *
 ******************************************************************************/

static void playGame(GameView gv, char *pastPlays, Message messages[])
{
	for (int i = 1; i < strlen(pastPlays);) // Game
	{
		// Pre-round
		if (i % NUM_CHAR_IN_ROUND == 0)
			gv->round++;

		while (i < i + NUM_CHAR_IN_ROUND) // Round
		{
			// Pre-turn
			if ((i - 6) % 8 == 0)
				gv->currentPlayer = (gv->currentPlayer + 1) % NUM_PLAYERS;

			for (; i < i + NUM_CHAR_IN_TURN; i++) // Turn
			{
				if (gv->currentPlayer == PLAYER_DRACULA)
					playDracula(gv, pastPlays, messages);
				else
					playHunter(gv, pastPlays, messages);
				// Dracula's actions
				// if (pastPlays[i] == 'T')

				// 	if (pastPlays[i] == 'V')
			}

			// Post-turn
			if (gv->healths[PLAYER_DRACULA] <= 0 || gv->score <= 0)
				break;
		}

		// Post-round
		expireEncounter(gv);
	}
}

static void playDracula(GameView gv, char *pastPlays, Message messages[])
{
}

static void playHunter(GameView gv, char *pastPlays, Message messages[])
{
	int location = 10;
	revealTrap(gv, location);
	revealVampire(gv, location);
}

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

static void removeVampire(GameView gv)
{
	gv->vampireLocation[PLACE_ID_PARAM] = NOWHERE;
	gv->vampireLocation[IS_KNOWN_PARAM] = false;
}

static void expireEncounter(GameView gv)
{
	if (gv->round % 13 == 0)
		removeVampire(gv);
	else
		removeTrap(gv, gv->trapLocations[PLACE_ID_PARAM][0]);
}

// static bool isKnownTrapLocation(GameView gv, PlaceId location)
// {
// 	for (int i = 0; i < MAX_ENCOUNTERS; i++)
// 		if (gv->trapLocations[PLACE_ID_PARAM][i] == location)
// 			if (gv->trapLocations[IS_KNOWN_PARAM][i] == true)
// 				return true;

// 	return false;
// }

static bool isKnownVampireLocation(GameView gv, PlaceId location)
{
	if (gv->vampireLocation[PLACE_ID_PARAM] == location)
		if (gv->vampireLocation[IS_KNOWN_PARAM] == true)
			return true;

	return false;
}

static bool isKnownDraculaLocation(GameView gv, PlaceId location)
{
	if (gv->draculaSightings[PLACE_ID_PARAM] == location)
		if (gv->draculaSightings[IS_KNOWN_PARAM] == true)
			return true;

	return false;
}

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

// static bool spottedDracula(GameView gv, PlaceId location)
// {
// 	if (gv->locationHistory[PLAYER_DRACULA][gv->round] == CASTLE_DRACULA)
// 		gv->knownDraculaLocation = ;

// 	return false;
// }

// static void revealedDracula(GameView gv)
// {
// 	if (spottedDracula(gv))
// }
