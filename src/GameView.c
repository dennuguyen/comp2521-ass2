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

typedef struct locationView *LocationView;
typedef struct playerView *PlayerView;

typedef struct locationView
{
	PlaceId location; // Location id
	bool isVampire;	  // Is there a vampire here
	bool isEncountered;
	bool isResearched;
} locationView;

typedef struct playerView
{
	Player player;					  // Player id
	int health;						  // Player health
	PlaceId lastKnownDraculaLocation; // Player's knowledge of Dracula's last location
	PlaceId *knownTrail;			  // Player's knowledge of known trail locations
	LocationView *moveHistory;		  // Dynamic array of PlaceView structs
} playerView;

typedef struct gameView
{
	int score;						// Number of current score
	Map map;						// Map ADT
	Round currentRound;				// Number of current round
	Player currentPlayer;			// Who the current player is
	PlayerView player[NUM_PLAYERS]; // Array of PlayerView structs
} gameView;

////////////////////////////////////////////////////////////////////////
// Static

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

static LocationView *getPlaces(PlayerView pv, int numMoves)
{
	return last numMoves for pv;
}

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

////////////////////////////////////////////////////////////////////////
// Constructor/Destructor

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
		new->player[i] = PvNew(i);

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
		free(gv->player[i]->moveHistory);
		free(gv->player[i]);
	}
	free(gv);
}

////////////////////////////////////////////////////////////////////////
// Game State Information

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
	return PvGetHealth(gv->player[player]);
}

PlaceId GvGetPlayerLocation(GameView gv, Player player)
{
	int *numReturnedLocs = 0;
	bool *canFree = false;
	return PvGetLocations(gv->player[player], 1, numReturnedLocs, canFree)[0];
}

PlaceId GvGetVampireLocation(GameView gv)
{
	PlaceView places = getPlaces(gv->player[PLAYER_DRACULA], 6);
	for (int i = 0; i < 6; i++)
		if (places->isVampire)
			return places->id;
	return CITY_UNKNOWN;
}

PlaceId *GvGetTrapLocations(GameView gv, int *numTraps)
{
	return getPlaces(gv->player[PLAYER_DRACULA], numTraps);
}

////////////////////////////////////////////////////////////////////////
// Game History

PlaceId *GvGetMoveHistory(GameView gv, Player player,
						  int *numReturnedMoves, bool *canFree)
{
	return GvGetLastMoves(gv, player, gv->currentRound, numReturnedMoves, canFree);
}

PlaceId *GvGetLastMoves(GameView gv, Player player, int numMoves,
						int *numReturnedMoves, bool *canFree)
{
	PlaceView *places = getPlaces(gv->player[player], numMoves);
	PlaceId *locations;
}

PlaceId *GvGetLocationHistory(GameView gv, Player player,
							  int *numReturnedLocs, bool *canFree)
{
	return GvGetLastLocations(gv, player, gv->currentRound, numReturnedLocs, canFree);
}

PlaceId *GvGetLastLocations(GameView gv, Player player, int numLocs,
							int *numReturnedLocs, bool *canFree)
{
	PlaceId *locations = getPlaces(gv->player[player], numLocs);

	if (player == PLAYER_DRACULA)
		return locations;

	// for each location in locations
	// 	if location != knownTrail
	// 		location = UNKNOWN
	// return locations;
}

////////////////////////////////////////////////////////////////////////
// Making a Move

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

////////////////////////////////////////////////////////////////////////
// Your own interface functions
