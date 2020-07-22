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

#include "Game.h"
#include "GameView.h"
#include "Map.h"
#include "Places.h"

typedef struct playerView *PlayerView;
typedef struct trapView *TrapView;

typedef struct playerView
{
	Player player;
	int health;
	PlaceId *moveHistory;
	PlaceId *locationHistory; // locationHistory would include current location
} playerView;

typedef struct trapView
{
	PlaceId location;
	bool isVampire;
	TrapView next;
} trapView;

typedef struct gameView
{
	int score;
	Map map;
	Round currentRound;
	Player currentPlayer;
	TrapView trapLocations;			// linked list of encounters
	PlayerView player[NUM_PLAYERS]; // enum is actually int
} gameView;

////////////////////////////////////////////////////////////////////////
// Static

// static char *messageParser(Message message)
// {
// }

// static char *pastPlaysParser(Message message)
// {
// }

static void *PvNew()
{
	PlayerView new = malloc(sizeof(playerView));
	if (new == NULL)
	{
		fprintf(stderr, "Couldn't allocate PlayerView!\n");
		exit(EXIT_FAILURE);
	}

	new->player = PLAYER_LORD_GODALMING;
	new->health = GAME_START_HUNTER_LIFE_POINTS;

	return new;
}

////////////////////////////////////////////////////////////////////////
// Constructor/Destructor

GameView GvNew(char *pastPlays, Message messages[])
{
	// TODO: REPLACE THIS WITH YOUR OWN IMPLEMENTATION
	GameView new = malloc(sizeof(gameView));
	if (new == NULL)
	{
		fprintf(stderr, "Couldn't allocate GameView!\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < NUM_PLAYERS; i++)
		new->player[i] = PvNew();

	new->score = GAME_START_SCORE;

	// PARSE pastPlayers and messages[]

	return new;
}

void GvFree(GameView gv)
{
	// TODO: REPLACE THIS WITH YOUR OWN IMPLEMENTATION
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
	return gv->player[player]->health;
}

PlaceId GvGetPlayerLocation(GameView gv, Player player)
{
	return gv->player[player]->locationHistory[gv->currentRound];
}

PlaceId GvGetVampireLocation(GameView gv)
{
	TrapView curr = gv->trapLocations;
	while (curr != NULL) {
		if (curr->isVampire) return curr->location;
	}
	return NOWHERE;
}

PlaceId *GvGetTrapLocations(GameView gv, int *numTraps)
{
	*numTraps = 0;
	PlaceId *traps = malloc(6*sizeof(int));
	TrapView curr = gv->trapLocations;
	i = 0;
	while (curr != NULL) {
		if (!curr->isVampire) traps[i] = curr->location;
		i++;
		*numTraps++;
	}
	return traps;
}

////////////////////////////////////////////////////////////////////////
// Game History

PlaceId *GvGetMoveHistory(GameView gv, Player player,
						  int *numReturnedMoves, bool *canFree)
{
	// TODO: REPLACE THIS WITH YOUR OWN IMPLEMENTATION
	*numReturnedMoves = 0;
	*canFree = false;
	return NULL;
}

PlaceId *GvGetLastMoves(GameView gv, Player player, int numMoves,
						int *numReturnedMoves, bool *canFree)
{
	// TODO: REPLACE THIS WITH YOUR OWN IMPLEMENTATION
	*numReturnedMoves = 0;
	*canFree = false;
	return NULL;
}

PlaceId *GvGetLocationHistory(GameView gv, Player player,
							  int *numReturnedLocs, bool *canFree)
{
	// TODO: REPLACE THIS WITH YOUR OWN IMPLEMENTATION
	*numReturnedLocs = 0;
	*canFree = false;
	return NULL;
}

PlaceId *GvGetLastLocations(GameView gv, Player player, int numLocs,
							int *numReturnedLocs, bool *canFree)
{
	// TODO: REPLACE THIS WITH YOUR OWN IMPLEMENTATION
	*numReturnedLocs = 0;
	*canFree = false;
	return 0;
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

// TODO
