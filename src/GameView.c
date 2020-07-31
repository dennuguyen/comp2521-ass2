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
	int trapIndex;						   // Incrementor for trapLocations
	PlaceId trapLocations[MAX_ENCOUNTERS]; // Array of trap locations
	PlaceId vampireLocation;			   // Vampire location

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
// static void setDraculaRumour(GameView gv);

/* Destroyers */
static void removeTrap(GameView gv, PlaceId location);
static void removeVampire(GameView gv);
static void expireTrap(GameView gv);
static void expireVampire(GameView gv);

/* Revealing functions */
// static bool isKnownTrapLocation(GameView gv, PlaceId trapLocation, PlaceId hunterLocation);
// static bool isKnownVampireLocation(GameView gv, PlaceId vampireLocation, PlaceId hunterLocation);
// static bool isKnownDraculaLocation(GameView gv, PlaceId draculaLocation, PlaceId hunterLocation);
static void encounterTrap(GameView gv, PlaceId location);
static void encounterVampire(GameView gv, PlaceId location);
static void encounterDracula(GameView gv);

/* Player functions */
static void revealDracula(GameView gv, int round);
static bool isHunterResting(GameView gv);
// static bool isDraculaHiding(GameView gv);
static bool isPlayerNotMoving(GameView gv);
static void hunterDies(GameView gv);
static void draculaDies(GameView gv);

/******************************************************************************
 * 								GameView ADT							 	  *
 ******************************************************************************/

void *GvNew(char *pastPlays, Message messages[])
{
	GameView gv = malloc(sizeof(gameView));
	if (gv == NULL)
	{
		fprintf(stderr, "Couldn't allocate GameView!\n");
		exit(EXIT_FAILURE);
	}

	gv->score = GAME_START_SCORE;
	gv->map = MapNew();
	gv->round = 0;
	gv->currentPlayer = PLAYER_LORD_GODALMING;

	for (int i = 0; i < MAX_ENCOUNTERS; i++)
		gv->trapLocations[i] = NOWHERE;

	gv->vampireLocation = NOWHERE;

	for (int i = 0; i < NUM_PLAYERS - 1; i++)
		gv->healths[i] = GAME_START_HUNTER_LIFE_POINTS;

	gv->healths[PLAYER_DRACULA] = GAME_START_BLOOD_POINTS;

	for (int i = 0; i < NUM_PLAYERS; i++)
		for (int j = 0; j < MAX_REAL_PLACE; j++)
		{
			gv->moveHistory[i][j] = NOWHERE;
			gv->locationHistory[i][j] = NOWHERE;
		}

	gv->research = 0;

	// Parse the pastPlays string and update the GameView accordingly.
	if (*pastPlays != '\0')
		playGame(gv, pastPlays, messages);

	return gv;
}

void GvFree(GameView gv)
{
	MapFree(gv->map);
	free(gv);
	gv = NULL;
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

	if (player >= gv->currentPlayer)
		return gv->locationHistory[player][gv->round - 1];
	else
		return gv->locationHistory[player][gv->round];

	// Get location of requested player.
	// if (gv->round == 0)
	// return gv->locationHistory[player][gv->round];
	// else
	// 	return gv->locationHistory[player][gv->round - 1]; // offset round counter

	// // Invalid location.
	// if (location == NOWHERE)
	// 	return NOWHERE;

	// // If requested player is not Dracula or Dracula requested a player.
	// if (player != PLAYER_DRACULA || gv->currentPlayer == PLAYER_DRACULA)
	// 	return location;

	// // Hunters ask for Dracula's location.
	// if (isKnownDraculaLocation(gv, UNKNOWN_PLACE, location))
	// 	return location;

	// // Dracula's location is hidden.
	// if (placeIdToType(location) == SEA)
	// 	return SEA_UNKNOWN;
	// return CITY_UNKNOWN;
}

PlaceId GvGetVampireLocation(GameView gv)
{
	// Vampire doesn't exist
	if (gv->vampireLocation == NOWHERE)
		return NOWHERE;

	return gv->vampireLocation;
	// // Vampire location is known
	// if (isKnownVampireLocation(gv, gv->vampireLocation, UNKNOWN_PLACE))
	// 	return gv->vampireLocation;

	// // Vampire location is unknown
	// return CITY_UNKNOWN;
}

/**
 * Returns trap locations from the GameView struct and updates numTraps.
 */
PlaceId *GvGetTrapLocations(GameView gv, int *numTraps)
{
	PlaceId *traps = malloc(MAX_ENCOUNTERS * sizeof(PlaceId));

	int i;

	for (i = 0; i < MAX_ENCOUNTERS; i++)
		traps[i] = NOWHERE;

	for (i = 0; i < MAX_ENCOUNTERS; i++)
		if (placeIsReal(gv->trapLocations[i]))
		{
			traps[*numTraps] = gv->trapLocations[i];
			(*numTraps)++;
		}

	return traps; // dynamic return

	// int i;
	// for (i = 0; i < MAX_ENCOUNTERS; i++)
	// 	if (&gv->trapLocations[i] == NULL)
	// 		break;

	// *numTraps = i;
	// return &gv->trapLocations[MAX_ENCOUNTERS - i]; // static return
}

/******************************************************************************
 * 								Game History								  *
 ******************************************************************************/

/**
 * Returns the whole moveHistory.
 */
PlaceId *GvGetMoveHistory(GameView gv, Player player, int *numReturnedMoves,
						  bool *canFree)
{
	return GvGetLastMoves(gv, player, gv->round, numReturnedMoves, canFree);
}

/**
 * Iterate 'numMoves' backwards through moveHistory and returns the address
 * to the static array 'numMoves' ago.
 */
PlaceId *GvGetLastMoves(GameView gv, Player player, int numMoves,
						int *numReturnedMoves, bool *canFree)
{
	*canFree = false;

	// Player hasn't started yet.
	if (player >= gv->currentPlayer && gv->round == 0)
		return &gv->moveHistory[player][gv->round];

	// i increments history backwards
	int i = gv->round;
	if (player >= gv->currentPlayer)
		i--;

	for (; i >= gv->round - numMoves && i >= 0; i--)
		if (gv->moveHistory[player][i] == NOWHERE)
			break;

	(*numReturnedMoves) = gv->round - i;

	// Off-set round increment
	if (player < gv->currentPlayer)
		(*numReturnedMoves)++;

	return &gv->moveHistory[player][i];
}

/**
 * Returns the whole locationHistory.
 */
PlaceId *GvGetLocationHistory(GameView gv, Player player,
							  int *numReturnedLocs, bool *canFree)
{
	return GvGetLastLocations(gv, player, gv->round, numReturnedLocs, canFree);
}

/**
 * Iterate 'numLocs' backwards through locationHistory and returns the address
 * to the static array 'numLocs' ago.
 */
PlaceId *GvGetLastLocations(GameView gv, Player player, int numLocs,
							int *numReturnedLocs, bool *canFree)
{
	*canFree = false;

	// Player hasn't started yet.
	if (player >= gv->currentPlayer && gv->round == 0)
		return &gv->locationHistory[player][gv->round];

	// i increments history backwards
	int i = gv->round;
	if (player >= gv->currentPlayer)
		i--;

	for (; i >= gv->round - numLocs && i >= 0; i--)
		if (gv->locationHistory[player][i] == NOWHERE)
			break;

	(*numReturnedLocs) = gv->round - i;

	// Off-set round increment
	if (player < gv->currentPlayer)
		(*numReturnedLocs)++;

	return &gv->locationHistory[player][i];
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
	if (round > gv->round)
		return NOWHERE;

	return gv->locationHistory[player][round];
}

PlaceId GvGetLastKnownDraculaLocation(GameView gv, Round *round)
{
	for (int i = gv->round; i >= 0; i--)
		if (placeIsReal(gv->locationHistory[PLAYER_DRACULA][i]))
		{
			*round = i;
			return gv->locationHistory[PLAYER_DRACULA][i];
		}

	return NOWHERE;
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

		// Check if hunters have researched
		if (gv->research == NUM_PLAYERS - 1)
			revealDracula(gv, gv->round - 6);

		// Reveal Dracula's HIDE move from 6 rounds ago (if he made one).
		if (GvGetMoveByRound(gv, PLAYER_DRACULA, gv->round - 6) == HIDE)
			revealDracula(gv, gv->round - 6);

		gv->currentPlayer = (gv->currentPlayer + 1) % NUM_PLAYERS;

		// Game over - Hunters win
		if (gv->healths[PLAYER_DRACULA] <= 0)
		{
			draculaDies(gv);
			return;
		}

		// Game over - Dracula wins
		if (gv->score <= 0)
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

	if (placeIsSea(location))
		gv->healths[PLAYER_DRACULA] -= LIFE_LOSS_SEA;

	if (location == CASTLE_DRACULA)
		gv->healths[PLAYER_DRACULA] += LIFE_GAIN_CASTLE_DRACULA;

	// Interpret 6th char
	// This is interpretted first so an expired trap makes room for setting a
	// new trap.
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
	if (gv->healths[gv->currentPlayer] <= 0)
		gv->healths[gv->currentPlayer] = GAME_START_HUNTER_LIFE_POINTS;

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

	for (int i = 3; i < 7; i++)
	{
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

		// Hunter dies and does nothing for remainder of their turn.
		if (gv->healths[gv->currentPlayer] <= 0)
		{
			hunterDies(gv);
			return;
		}
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
	// if (gv->currentPlayer == PLAYER_DRACULA)
	// {
	// 	if (location == CASTLE_DRACULA)
	// 		gv->locationHistory[gv->currentPlayer][gv->round] = CASTLE_DRACULA;
	// 	else if (placeIsLand(location))
	// 		gv->locationHistory[gv->currentPlayer][gv->round] = CITY_UNKNOWN;
	// 	else
	// 		gv->locationHistory[gv->currentPlayer][gv->round] = SEA_UNKNOWN;
	// }
	// else
	gv->locationHistory[gv->currentPlayer][gv->round] = location;
}

/**
 * Set a trap in a given location.
 */
static void setTrap(GameView gv, PlaceId location)
{
	for (int i = 0; i < MAX_ENCOUNTERS; i++)
		if (gv->trapLocations[i] == NOWHERE)
		{
			gv->trapLocations[i] = location;
			return;
		}

	gv->trapLocations[MAX_ENCOUNTERS - 1] = location;

	fprintf(stderr, "ERROR: trap locations array is full.\n");

	// circular array implementation
	// gv->trapLocations[gv->trapIndex % MAX_ENCOUNTERS] = location;
	// gv->trapIndex++;
}

/**
 * Set a vampire in a given location.
 */
static void setVampire(GameView gv, PlaceId location)
{
	gv->vampireLocation = location;
}

/**
 * Reveal Dracula's location that HIDE or DOUBLE_BACK was pointing to.
 * 
 * TODO:
 */
static void revealDracula(GameView gv, int round)
{
	// Reveal HIDE when they become last move in Dracula's trail.
	// if (round == HIDE && gv->research == 0)
	// {
	// 	gv->locationHistory[round] = GvGetMoveByRound(gv, PLAYER_DRACULA, gv->round - 6);; // set dracula's real location;
	// 	return;
	// }
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
	int j = i;
	for (; j < MAX_ENCOUNTERS - 1; j++)
		gv->trapLocations[j] = gv->trapLocations[j + 1];

	gv->trapLocations[j] = NOWHERE;
	// gv->trapIndex--;
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

	// circular array implementation
	// removeTrap(gv, gv->trapLocations[(gv->trapIndex) % MAX_ENCOUNTERS]);
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
// static bool isKnownTrapLocation(GameView gv, PlaceId trapLocation, PlaceId hunterLocation)
// {
// 	// Use trap location
// 	if (trapLocation != UNKNOWN_PLACE)
// 		for (int i = 0; i < NUM_PLAYERS - 1; i++)
// 			if (gv->moveHistory[i][gv->round] == trapLocation)
// 				return true;

// 	// Use hunter location
// 	if (hunterLocation != UNKNOWN_PLACE)
// 		for (int i = 0; i < MAX_ENCOUNTERS; i++)
// 			if (gv->trapLocations[i] == hunterLocation)
// 				return true;

// 	return false;
// }

/**
 * Vampire location is known if it is shared with a hunter.
 * 
 * isKnownVampireLocation takes either vampireLocation or hunterLocation.
 */
// static bool isKnownVampireLocation(GameView gv, PlaceId vampireLocation, PlaceId hunterLocation)
// {
// 	// Use hunter location
// 	if (hunterLocation != UNKNOWN_PLACE)
// 		if (hunterLocation == gv->vampireLocation)
// 			return true;

// 	// Use vampire location
// 	if (vampireLocation != UNKNOWN_PLACE)
// 		for (int i = 0; i < NUM_PLAYERS - 1; i++)
// 			if (gv->moveHistory[i][gv->round] == vampireLocation)
// 				return true;

// 	return false;
// }

/**
 * Dracula location is known if it is shared with a hunter.
 */
// static bool isKnownDraculaLocation(GameView gv, PlaceId draculaLocation, PlaceId hunterLocation)
// {
// 	// Use hunter location
// 	if (hunterLocation != UNKNOWN_PLACE)
// 		if (hunterLocation == gv->moveHistory[PLAYER_DRACULA][gv->round])
// 			return true;

// 	// Use dracula location
// 	if (draculaLocation != UNKNOWN_PLACE)
// 		for (int i = 0; i < NUM_PLAYERS - 1; i++)
// 			if (gv->moveHistory[i][gv->round] == draculaLocation)
// 				return true;

// 	return false;
// }

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
// static bool isDraculaHiding(GameView gv)
// {
// 	return isPlayerNotMoving(gv);
// }

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
 * Set their health to 0.
 */
static void hunterDies(GameView gv)
{
	gv->score -= SCORE_LOSS_HUNTER_HOSPITAL;
	gv->healths[gv->currentPlayer] = 0;
	updateLocationHistory(gv, HOSPITAL_PLACE);
}

/**
 * Set Dracula's health to 0 when he dies.
 */
static void draculaDies(GameView gv)
{
	gv->healths[PLAYER_DRACULA] = 0;
}