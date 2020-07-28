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

typedef struct locationNode *LocationNode;
typedef struct locationView *LocationView;
typedef struct playerView *PlayerView;

typedef struct locationNode
{
	PlaceId location;	// Location id
	bool isTrapped;		// Is there a trap at this location
	bool isVampire;		// Is there a vampire at this location
	bool isEncountered; // Has location been encountered by a hunter
	bool isResearched;	// Has location been researched by a hunter
} locationNode;

typedef struct locationView
{
	LocationNode *history; // Dynamic array of LocationNodes
	size_t used;		   // How much of the array has been used
	size_t size;		   // Total size of array
} locationView;

typedef struct playerView
{
	Player player;			  // Player id
	int health;				  // Player health
	LocationView moveHistory; // Dynamic array of TrailView structs
} playerView;

typedef struct gameView
{
	int score;						// Number of current score
	Map map;						// Map ADT
	Round currentRound;				// Number of current round
	Player currentPlayer;			// Who the current player is
	PlayerView player[NUM_PLAYERS]; // Array of PlayerView structs
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
 * 			D:
 * 
 */
static void interpretPlay(GameView gv, char *play)
{
	for (int i = 0; i < 7; i++)
	{
		// char c = play[i]; // depending on what c is, change the gv struct
	}
}
// static char *messageParser(Message message);

static bool hasTrap(LocationNode node)
{
	if (node->isTrapped)
		return true;
	return false;
}

static bool hasVampire(LocationNode node)
{
	if (node->isVampire)
		return true;
	return false;
}

static bool hasEncountered(LocationNode node)
{
	if (node->isEncountered)
		return true;
	return false;
}

static bool hasResearched(LocationNode node)
{
	if (node->isResearched)
		return true;
	return false;
}

/******************************************************************************
 * 								LocationView ADT							  *
 ******************************************************************************/

/**
 * Create new dynamic array for LocationView.
 */
static LocationView LvNew(size_t size)
{
	LocationView new = malloc(sizeof(locationView));
	if (new == NULL)
	{
		fprintf(stderr, "ERROR: Could not allocate memory for LocationView\n");
		exit(EXIT_FAILURE);
	}

	new->history = malloc(ARRAY_BUFFER * sizeof(locationNode));
	if (new->history == NULL)
	{
		fprintf(stderr, "ERROR: Could not allocate memory for LocationView.history\n");
		exit(EXIT_FAILURE);
	}

	new->size = size;

	return new;
}

/**
 * Free LocationView.
 */
static void LvFree(LocationView lv)
{
	if (lv == NULL)
		return;

	for (int i = 0; i < lv->used; i++)
		free(lv->history);

	free(lv);
}

/**
 * Insert a trail to the LocationView history.
 */
// static void LvInsertLocation(LocationView lv,
// 							 PlaceId location,
// 							 bool isTrapped,
// 							 bool isVampire,
// 							 bool isEncountered,
// 							 bool isResearched)
// {
// 	// Dynamic array is full
// 	if (lv->used == lv->size)
// 	{
// 		lv->size += ARRAY_BUFFER;
// 		realloc(lv->history, lv->size * sizeof(locationNode));
// 	}

// 	lv->used++; // Increment used amount
// 	lv->history[lv->used]->location = location;
// 	lv->history[lv->used]->isTrapped = isTrapped;
// 	lv->history[lv->used]->isVampire = isVampire;
// 	lv->history[lv->used]->isEncountered = isEncountered;
// 	lv->history[lv->used]->isResearched = isResearched;
// }

/**
 * Show the LocationView.
 */
// static void LvShow(LocationView lv)
// {
// 	if (lv == NULL)
// 		return;

// 	printf("LocationView Size: %ld\n", lv->size);
// 	printf("LocationView Used: %ld\n", lv->used);
// 	printf("LocationView:\n");

// 	for (int i = 0; i < lv->size; i++)
// 		printf("{%d, %d, %d, %d}\n",
// 			   lv->history[i]->location,
// 			   lv->history[i]->isVampire,
// 			   lv->history[i]->isEncountered,
// 			   lv->history[i]->isResearched);
// }

/**
 * Get the most recent trail up to 'num'.
 */
static PlaceId *LvGetLocations(LocationView lv,
							   int num,
							   int *numReturned,
							   bool *canFree,
							   bool hunterRequest,
							   bool cmptor(LocationNode))
{
	PlaceId *locations = malloc(ARRAY_BUFFER * sizeof(PlaceId));

	*numReturned = 0;
	*canFree = false;

	for (int i = 0, j = lv->used - num; j < lv->used; i++, j++)
	{
		// if comparator was not specified then do not filter
		if (cmptor == NULL)
			locations[*numReturned++] = lv->history[j]->location;

		// add location if it passes the comparator
		else if (cmptor(lv->history[j]))
			locations[*numReturned++] = lv->history[j]->location;
	}

	// mask trail if request to get locations was made by hunter
	if (hunterRequest == true)
	{
		for (int i = 0; i < *numReturned; i++)
			if (!hasEncountered(lv->history[locations[i]]) || !hasResearched(lv->history[locations[i]]))
			{
				if (placeIdToType(locations[i]) == LAND)
					locations[i] = CITY_UNKNOWN;
				else if (placeIdToType(locations[i]) == SEA)
					locations[i] = SEA_UNKNOWN;
			}
	}

	return locations;
}

/******************************************************************************
 * 								PlayerView ADT								  *
 ******************************************************************************/

PlayerView PvNew(Player player)
{
	PlayerView new = malloc(sizeof(playerView));
	if (new == NULL)
	{
		fprintf(stderr, "ERROR: Could not allocate memory for PlayerView\n");
		exit(EXIT_FAILURE);
	}

	new->player = player;
	new->moveHistory = NULL;

	if (player == PLAYER_DRACULA)
		new->health = GAME_START_BLOOD_POINTS;
	else
		new->health = GAME_START_HUNTER_LIFE_POINTS;

	return new;
}

/******************************************************************************
 * 								GameView ADT							 	  *
 ******************************************************************************/

GameView GvNew(char *pastPlays, Message messages[])
{
	GameView new = malloc(sizeof(gameView));
	if (new == NULL)
	{
		fprintf(stderr, "ERROR: Could not allocate memory for GameView\n");
		exit(EXIT_FAILURE);
	}

	new->score = GAME_START_SCORE;
	new->map = MapNew();
	new->currentRound = 0;
	new->currentPlayer = PLAYER_LORD_GODALMING;
	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		new->player[i] = PvNew(i);
		new->player[i]->moveHistory = LvNew(ARRAY_BUFFER);
	}

	// Each move in pastPlayers is separated by a space
	const char *delimiter = " ";
	for (char *play = strtok(pastPlays, delimiter); play != NULL; play = strtok(NULL, delimiter))
		interpretPlay(new, play);

	return new;
}

void GvFree(GameView gv)
{
	MapFree(gv->map);
	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		LvFree(gv->player[i]->moveHistory);
		free(gv->player[i]);
	}
	free(gv);
}

/******************************************************************************
 * 								Game State Info							  	  *
 ******************************************************************************/

Round GvGetRound(GameView gv)
{
	return gv->currentRound;
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
	return gv->player[player]->health;
}

PlaceId GvGetPlayerLocation(GameView gv, Player player)
{
	int *numReturned = 0;
	bool *canFree = false;
	bool hunterRequest = gv->currentPlayer == PLAYER_DRACULA ? false : true;
	return LvGetLocations(gv->player[player]->moveHistory,
						  1,
						  numReturned,
						  canFree,
						  hunterRequest,
						  NULL)[0];
}

PlaceId GvGetVampireLocation(GameView gv)
{
	int *numReturned = 0;
	bool *canFree = false;
	bool hunterRequest = gv->currentPlayer == PLAYER_DRACULA ? false : true;
	return LvGetLocations(gv->player[PLAYER_DRACULA]->moveHistory,
						  TRAIL_SIZE,
						  numReturned,
						  canFree,
						  hunterRequest,
						  hasVampire)[0];
}

PlaceId *GvGetTrapLocations(GameView gv, int *numTraps)
{
	int *numReturned = 0;
	bool *canFree = false;
	bool hunterRequest = gv->currentPlayer == PLAYER_DRACULA ? false : true;
	return LvGetLocations(gv->player[PLAYER_DRACULA]->moveHistory,
						  TRAIL_SIZE,
						  numReturned,
						  canFree,
						  hunterRequest,
						  hasTrap);
}

/******************************************************************************
 * 								Game History								  *
 ******************************************************************************/

PlaceId *GvGetMoveHistory(GameView gv,
						  Player player,
						  int *numReturnedMoves,
						  bool *canFree)
{
	return LvGetLocations(gv->player[player]->moveHistory,
						  gv->currentRound,
						  numReturnedMoves,
						  canFree,
						  false,
						  NULL);
}

PlaceId *GvGetLastMoves(GameView gv,
						Player player,
						int numMoves,
						int *numReturnedMoves,
						bool *canFree)
{
	return LvGetLocations(gv->player[player]->moveHistory,
						  numMoves,
						  numReturnedMoves,
						  canFree,
						  false,
						  NULL);
}

PlaceId *GvGetLocationHistory(GameView gv,
							  Player player,
							  int *numReturnedLocs,
							  bool *canFree)
{
	bool hunterRequest = gv->currentPlayer == PLAYER_DRACULA ? false : true;
	return LvGetLocations(gv->player[player]->moveHistory,
						  gv->currentRound,
						  numReturnedLocs,
						  canFree,
						  hunterRequest,
						  NULL);
}

PlaceId *GvGetLastLocations(GameView gv,
							Player player,
							int numLocs,
							int *numReturnedLocs,
							bool *canFree)
{
	bool hunterRequest = gv->currentPlayer == PLAYER_DRACULA ? false : true;
	return LvGetLocations(gv->player[player]->moveHistory,
						  numLocs,
						  numReturnedLocs,
						  canFree,
						  hunterRequest,
						  NULL);
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
