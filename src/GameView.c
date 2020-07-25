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
#include "PlayerView.h"
#include "TrapView.h"

typedef struct gameView
{
	int score;
	Map map;
	Round currentRound;
	Player currentPlayer;
	TrapView trapLocations;			// TrapView queue
	PlayerView player[NUM_PLAYERS]; // PlayerView array
} gameView;

////////////////////////////////////////////////////////////////////////
// Static

/**
 * Parse through each char of play string which is 7 char long
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
	new->trapLocations = TvNew();
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
	TvFree(gv->trapLocations);
	for (int i = 0; i < NUM_PLAYERS; i++)
		PvFree(gv->player[i]);
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
	return PvGetLocationHistory(gv->player[player])[gv->currentRound];
}

PlaceId GvGetVampireLocation(GameView gv)
{
	return TvGetVampireLocation(gv->trapLocations);
}

PlaceId *GvGetTrapLocations(GameView gv, int *numTraps)
{
	return TvGetTrapLocations(gv->trapLocations, numTraps);
}

////////////////////////////////////////////////////////////////////////
// Game History

PlaceId *GvGetMoveHistory(GameView gv, Player player,
						  int *numReturnedMoves, bool *canFree)
{
	
	*numReturnedMoves = gv->currentRound;
	*canFree = false;
	return gv->player[player]->moveHistory;
	//return PvGetMoves(gv->player[player], gv->currentRound, numReturnedMoves, canFree);
}

PlaceId *GvGetLastMoves(GameView gv, Player player, int numMoves,
						int *numReturnedMoves, bool *canFree)
{
	PlaceId *lastMoves = malloc(numMoves * sizeof(PlaceId));
	int j = 0;
	*canFree = true;
	return lastMoves;
	//return PvGetMoves(gv->player[player], numMoves, numReturnedMoves, canFree);
}

PlaceId *GvGetLocationHistory(GameView gv, Player player,
							  int *numReturnedLocs, bool *canFree)
{
	return PvGetLocations(gv->player[player], gv->currentRound, numReturnedLocs, canFree);
}

PlaceId *GvGetLastLocations(GameView gv, Player player, int numLocs,
							int *numReturnedLocs, bool *canFree)
{
	PlaceId *lastLocs = malloc(numLocs * sizeof(PlaceId));
	*numReturnedLocs = 0;
	int j = 0;
	for (int i = gv->currentRound; i > gv->currentRound - numLocs && i > 0; i--) {
		lastLocs[j] = gv->player[player]->locationHistory[i];
		*numReturnedLocs++;
	}
	*canFree = true;
	return lastLocs;
	//return PvGetLocations(gv->player[player], numLocs, numReturnedLocs, canFree);
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
