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

typedef struct gameView
{
	/* Game information */
	int score;			  // Number of current score
	Map map;			  // Map ADT
	Round round;		  // Number of current round
	Player currentPlayer; // Who the current player is

	/* Encounter locations */
	PlaceId trapLocations[MAX_ENCOUNTERS]; // Array of trap locations
	PlaceId vampireLocation;			   // Vampire location
	bool draculaHistory[MAX_ROUNDS];	   // Boolean to complement Dracula's moveHistory if is known to hunters

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

/* Move and location functions */
static void updateMoveHistory(GameView gv, PlaceId move);
static void updateLocationHistory(GameView gv, PlaceId location);

/* Encounter functions */
static void setTrap(GameView gv, PlaceId location);
static void setVampire(GameView gv, PlaceId location);
static void revealDracula(GameView gv, int round);
static void removeTrap(GameView gv, PlaceId location);
static void removeVampire(GameView gv);
static void expireTrap(GameView gv);
static void expireVampire(GameView gv);

/* Revealing functions */
static bool isKnownTrapLocation(GameView gv, PlaceId trapLocation, PlaceId hunterLocation);
static bool isKnownVampireLocation(GameView gv, PlaceId vampireLocation, PlaceId hunterLocation);
static bool isKnownDraculaLocation(GameView gv, PlaceId draculaLocation, PlaceId hunterLocation);
static void encounterTrap(GameView gv, PlaceId location);
static void encounterVampire(GameView gv, PlaceId location);
static void encounterDracula(GameView gv);

/* Player functions */
static bool isHunterResting(GameView gv);
static bool isDraculaHiding(GameView gv);
static bool isPlayerNotMoving(GameView gv);
static void hunterDies(GameView gv);

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
		.trapLocations = {NOWHERE, NOWHERE, NOWHERE, NOWHERE, NOWHERE, NOWHERE},
		.vampireLocation = NOWHERE,
		.draculaHistory = {0},
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
	// free(gv);
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
	// Player hasn't started yet.
	if (player >= gv->currentPlayer && gv->round == 0)
		return NOWHERE;

	// Get location of requested player.
	int location = gv->locationHistory[player][gv->round];

	// Invalid location.
	if (location == NOWHERE)
		return NOWHERE;

	// If requested player is not Dracula or Dracula requested a player.
	if (player != PLAYER_DRACULA || gv->currentPlayer == PLAYER_DRACULA)
		return location;

	// Hunters ask for Dracula's location.
	if (isKnownDraculaLocation(gv, UNKNOWN_PLACE, location))
		return location;

	// Dracula's location is hidden.
	if (placeIdToType(location) == SEA)
		return SEA_UNKNOWN;
	return CITY_UNKNOWN;
}

PlaceId GvGetVampireLocation(GameView gv)
{
	// Vampire doesn't exist
	if (gv->vampireLocation == NOWHERE)
		return NOWHERE;

	// Vampire location is known
	if (isKnownVampireLocation(gv, gv->vampireLocation, UNKNOWN_PLACE))
		return gv->vampireLocation;

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
		if (&gv->trapLocations[*numTraps] == NULL)
			break;

	return &gv->trapLocations[*numTraps];
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
 * 							  Extra ADT Functions							  *
 ******************************************************************************/

PlaceId GvGetMoveByRound(GameView gv, Player player, Round round)
{
	if (gv->round > round)
		return NOWHERE;

	return gv->moveHistory[player][round];
}

PlaceId GvGetLocationByRound(GameView gv, Player player, Round round)
{
	if (gv->round > round)
		return NOWHERE;

	return gv->locationHistory[player][round];
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

		// Get location to move to.
		char loc[3] = {[0] = *(play + 1), [1] = *(play + 2), [2] = '\0'};
		PlaceId location = placeAbbrevToId(loc);

		// Dracula play string is different to hunter play string.
		if (gv->currentPlayer == PLAYER_DRACULA)
			playDracula(gv, play, messages, location);
		else
			playHunter(gv, play, messages, location);

		gv->currentPlayer = (gv->currentPlayer + 1) % NUM_PLAYERS;

		// Game over
		if (gv->healths[PLAYER_DRACULA] <= 0 || gv->score <= 0) // this causes bug where round finishes at 21 instead of 28
			return;
	}

	free(tmp);
}

/**
 * Play strings are interpretted differently depending on the player type.
 * Order of char matters in a Dracula string.
 */
static void playDracula(GameView gv, char *play, Message messages[], int move)
{
	gv->score -= SCORE_LOSS_DRACULA_TURN;

	/* Move Phase */

	PlaceId location = move;
	switch (move)
	{
	case TELEPORT:
		location = CASTLE_DRACULA;
		break;
	case HIDE:
		location = GvGetLocationByRound(gv, PLAYER_DRACULA, gv->round - 1);
		break;
	case DOUBLE_BACK_1:
		location = GvGetLocationByRound(gv, PLAYER_DRACULA, gv->round - 1);
		break;
	case DOUBLE_BACK_2:
		location = GvGetLocationByRound(gv, PLAYER_DRACULA, gv->round - 2);
		break;
	case DOUBLE_BACK_3:
		location = GvGetLocationByRound(gv, PLAYER_DRACULA, gv->round - 3);
		break;
	case DOUBLE_BACK_4:
		location = GvGetLocationByRound(gv, PLAYER_DRACULA, gv->round - 4);
		break;
	case DOUBLE_BACK_5:
		location = GvGetLocationByRound(gv, PLAYER_DRACULA, gv->round - 5);
		break;
	}

	updateMoveHistory(gv, move);
	updateLocationHistory(gv, location);

	/* Action Phase */

	if (location == CASTLE_DRACULA || isKnownDraculaLocation(gv, location, UNKNOWN_PLACE))
		revealDracula(gv, gv->round);

	if (isDraculaHiding(gv))
		gv->healths[PLAYER_DRACULA] += LIFE_GAIN_CASTLE_DRACULA;

	if (placeIsSea(location))
		gv->healths[PLAYER_DRACULA] -= LIFE_LOSS_SEA;

	if (location == CASTLE_DRACULA)
		gv->healths[PLAYER_DRACULA] += LIFE_GAIN_CASTLE_DRACULA;

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

static void playHunter(GameView gv, char *play, Message messages[], int move)
{
	/* Move Phase */

	PlaceId location = move;
	updateMoveHistory(gv, move);
	updateLocationHistory(gv, location);

	/* Action Phase */

	// Hunters gain `LIFE_GAIN_REST` hp for max of `GAME_START_HUNTER_LIFE_POINTS` hp.
	if (isHunterResting(gv))
	{
		gv->healths[gv->currentPlayer] += LIFE_GAIN_REST;
		if (gv->healths[gv->currentPlayer] > GAME_START_HUNTER_LIFE_POINTS)
			gv->healths[gv->currentPlayer] = GAME_START_HUNTER_LIFE_POINTS;

		gv->research++;
	}

	// Hunter research or HIDE revealed
	if (gv->research == NUM_PLAYERS - 1 || GvGetMoveByRound(gv, PLAYER_DRACULA, gv->round - 6) == HIDE)
		revealDracula(gv, gv->round - 6);

	// Hunter dies and does nothing for remainder of their turn.
	if (gv->healths[gv->currentPlayer] <= 0)
	{
		hunterDies(gv);
		return;
	}

	for (int i = 3; i < 7; i++)
		switch (play[i])
		{
		case 'T':
			encounterTrap(gv, location);
			break;
		case 'V':
			encounterVampire(gv, location);
			break;
		case 'D':
			encounterDracula(gv);
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
	gv->trapLocations[gv->round] = location;
}

/**
 * Set a vampire in a given location.
 */
static void setVampire(GameView gv, PlaceId location)
{
	gv->vampireLocation = location;
}

/**
 * Reveal Dracula's location that HIDE or DOUBLE_BACK was pointing to
 * recursively.
 */
static void revealDracula(GameView gv, int round)
{
	// Reveal HIDE when they become last move in Dracula's trail.
	if (round == HIDE && gv->research == 0)
	{
		gv->draculaHistory[round] = true;
		return;
	}

	// Base case for recursive search.
	if (!(DOUBLE_BACK_1 < round && round < DOUBLE_BACK_5))
	{
		gv->draculaHistory[round] = true;
		return;
	}

	return revealDracula(gv, round);
}

/**
 * Removes a trap in the given location by splicing the trap from the array.
 */
static void removeTrap(GameView gv, PlaceId location)
{
	int i = 0;
	for (; i < MAX_ENCOUNTERS - 1; i++)
		if (gv->trapLocations[i] == location)
			break;

	for (int j = i; j < MAX_ENCOUNTERS - 1; j++)
		gv->trapLocations[j] = gv->trapLocations[j + 1];
}

/**
 * Remove the vampire by setting its location to NOWHERE and is known parameter
 * to false.
 */
static void removeVampire(GameView gv)
{
	gv->vampireLocation = NOWHERE;
}

/**
 * Oldest trap malfunctions which removes it from the game.
 */
static void expireTrap(GameView gv)
{
	removeTrap(gv, gv->trapLocations[0]);
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
 * Trap location is known if it is shared with a hunter.
 * 
 * isKnownTrapLocation takes either trapLocation or hunterLocation.
 */
static bool isKnownTrapLocation(GameView gv, PlaceId trapLocation, PlaceId hunterLocation)
{
	if (trapLocation != UNKNOWN_PLACE)
		for (int i = 0; i < NUM_PLAYERS - 1; i++)
			if (gv->moveHistory[i][gv->round] == trapLocation)
				return true;

	if (hunterLocation != UNKNOWN_PLACE)
		for (int i = 0; i < MAX_ENCOUNTERS; i++)
			if (gv->trapLocations[i] == hunterLocation)
				return true;

	return false;
}

/**
 * Vampire location is known if it is shared with a hunter.
 * 
 * isKnownVampireLocation takes either vampireLocation or hunterLocation.
 */
static bool isKnownVampireLocation(GameView gv, PlaceId vampireLocation, PlaceId hunterLocation)
{
	// Use hunter location
	if (hunterLocation != UNKNOWN_PLACE)
		if (hunterLocation == gv->vampireLocation)
			return true;

	// Use vampire location
	if (vampireLocation != UNKNOWN_PLACE)
		for (int i = 0; i < NUM_PLAYERS - 1; i++)
			if (gv->moveHistory[i][gv->round] == vampireLocation)
				return true;

	return false;
}

/**
 * Dracula location is known if it is shared with a hunter.
 */
static bool isKnownDraculaLocation(GameView gv, PlaceId draculaLocation, PlaceId hunterLocation)
{
	// Use hunter location
	if (hunterLocation != UNKNOWN_PLACE)
		if (hunterLocation == gv->moveHistory[PLAYER_DRACULA][gv->round])
			return true;

	// Use dracula location
	if (draculaLocation != UNKNOWN_PLACE)
		for (int i = 0; i < NUM_PLAYERS - 1; i++)
			if (gv->moveHistory[i][gv->round] == draculaLocation)
				return true;

	return false;
}

/**
 * Hunter function where trap is encountered and effects take place.
 */
static void encounterTrap(GameView gv, PlaceId location)
{
	gv->healths[gv->currentPlayer] -= LIFE_LOSS_TRAP_ENCOUNTER;
	removeTrap(gv, location);
}

/**
 * Hunter function where vampire is encountered and effects take place.
 */
static void encounterVampire(GameView gv, PlaceId location)
{
	removeVampire(gv);
}

/**
 * Hunter function where Dracula is encountered and effects take place.
 */
static void encounterDracula(GameView gv)
{
	gv->healths[gv->currentPlayer] -= LIFE_LOSS_DRACULA_ENCOUNTER;
	gv->healths[PLAYER_DRACULA] -= LIFE_LOSS_HUNTER_ENCOUNTER;
}

/**
 * Returns true if hunter has RESTED i.e. not changed locations between
 * previous and current round.
 */
static bool isHunterResting(GameView gv)
{
	return isPlayerNotMoving(gv);
}

/**
 * Returns true if Dracula is HIDING i.e. not changed locations between
 * previous and current round.
 */
static bool isDraculaHiding(GameView gv)
{
	return isPlayerNotMoving(gv);
}

/**
 * Hunter or Dracula can call this function to check if they are RESTING or
 * HIDING respectively.
 */
static bool isPlayerNotMoving(GameView gv)
{
	int numReturned[1] = {0};
	bool canFree[1] = {false};
	PlaceId *locations = GvGetLastLocations(gv, gv->currentPlayer, 2, numReturned, canFree);

	if (*numReturned < 2)
		return false;

	if (locations[0] == locations[1])
		return true;

	return false;
}

/**
 * When hunter dies, they respawn at the Hospital and the score is deducted.
 */
static void hunterDies(GameView gv)
{
	updateLocationHistory(gv, HOSPITAL_PLACE);
	gv->score -= SCORE_LOSS_HUNTER_HOSPITAL;
	gv->healths[gv->currentPlayer] = GAME_START_HUNTER_LIFE_POINTS;
}