////////////////////////////////////////////////////////////////////////
// COMP2521 20T2 ... the Fury of Dracula
// DraculaView.c: the DraculaView ADT implementation
//
// 2014-07-01	v1.0	Team Dracula <cs2521@cse.unsw.edu.au>
// 2017-12-01	v1.1	Team Dracula <cs2521@cse.unsw.edu.au>
// 2018-12-31	v2.0	Team Dracula <cs2521@cse.unsw.edu.au>
// 2020-07-10	v3.0	Team Dracula <cs2521@cse.unsw.edu.au>
//
////////////////////////////////////////////////////////////////////////

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "DraculaView.h"
#include "Game.h"
#include "GameView.h"

struct draculaView
{
} draculaView;

////////////////////////////////////////////////////////////////////////
// Constructor/Destructor

DraculaView DvNew(char *pastPlays, Message messages[])
{
	DraculaView dv = (void *)GvNew(pastPlays, messages);
	return dv;
}

void DvFree(DraculaView dv)
{
	GvFree((GameView)dv);
}

////////////////////////////////////////////////////////////////////////
// Game State Information

Round DvGetRound(DraculaView dv)
{
	return GvGetRound((GameView)dv);
}

int DvGetScore(DraculaView dv)
{
	return GvGetScore((GameView)dv);
}

int DvGetHealth(DraculaView dv, Player player)
{
	return GvGetHealth((GameView)dv, player);
}

PlaceId DvGetPlayerLocation(DraculaView dv, Player player)
{
	return GvGetPlayerLocation((GameView)dv, player);
}

PlaceId DvGetVampireLocation(DraculaView dv)
{
	return GvGetVampireLocation((GameView)(dv));
}

PlaceId *DvGetTrapLocations(DraculaView dv, int *numTraps)
{
	return GvGetTrapLocations((GameView)dv, numTraps);
}

////////////////////////////////////////////////////////////////////////
// Making a Move

PlaceId *DvGetValidMoves(DraculaView dv, int *numReturnedMoves)
{
	// Dracula  hasn't  made  a move yet
	int numDraculaMoves = 0;
	bool canFree = false;
	GvGetMoveHistory((GameView)dv, PLAYER_DRACULA, &numDraculaMoves, &canFree);
	if (numDraculaMoves == 0) return NULL;

	// Dracula cannot make a HIDE or DOUBLE_BACK move if he has made on in the
	// last five rounds
	int numLastFive = 0;
	PlaceId *lastFiveLocations = GvGetLastMoves((GameView)dv, PLAYER_DRACULA, 5, &numLastFive, &canFree);
	bool canHide = true, canDoubleBack1 = true, canDoubleBack2 = true, 
	canDoubleBack3 = true, canDoubleBack4 = true, canDoubleBack5 = true;
	for (int i = 0; i < numLastFive; i++) {
		if (lastFiveLocations[i] == HIDE) canHide = false;
		else if (lastFiveLocations[i] == DOUBLE_BACK_1) canDoubleBack1 = false;
		else if (lastFiveLocations[i] == DOUBLE_BACK_2) canDoubleBack2 = false;
		else if (lastFiveLocations[i] == DOUBLE_BACK_3) canDoubleBack3 = false;
		else if (lastFiveLocations[i] == DOUBLE_BACK_4) canDoubleBack4 = false;
		else if (lastFiveLocations[i] == DOUBLE_BACK_5) canDoubleBack5 = false;
	}

	// Get valid locations
	int numValidLocations = 0;
	PlaceId *validLocations = DvWhereCanIGo(dv, &numValidLocations);

	PlaceId *validMoves = malloc((numValidLocations+6)*sizeof(PlaceId));
	assert(validMoves != NULL);
	for (int i = 0; i < numValidLocations; i++) {
		validMoves[i] = validLocations[i];
		(*numReturnedMoves)++;
	}
	if (canHide) validMoves[(*numReturnedMoves)++] = HIDE;
	if (canDoubleBack1) validMoves[(*numReturnedMoves)++] = DOUBLE_BACK_1;
	if (canDoubleBack2) validMoves[(*numReturnedMoves)++] = DOUBLE_BACK_2;
	if (canDoubleBack3) validMoves[(*numReturnedMoves)++] = DOUBLE_BACK_3;
	if (canDoubleBack4) validMoves[(*numReturnedMoves)++] = DOUBLE_BACK_4;
	if (canDoubleBack5) validMoves[(*numReturnedMoves)++] = DOUBLE_BACK_5;
	if (*numReturnedMoves == 0) {return NULL;}
	return validMoves;
}

PlaceId *DvWhereCanIGo(DraculaView dv, int *numReturnedLocs)
{
	bool road = true, boat = true;
	return DvWhereCanIGoByType(dv, road, boat, numReturnedLocs);
}

PlaceId *DvWhereCanIGoByType(DraculaView dv, bool road, bool boat,
							 int *numReturnedLocs)
{
	bool rail = false;
	return DvWhereCanTheyGoByType(dv, PLAYER_DRACULA, road, rail, boat, numReturnedLocs);
}

PlaceId *DvWhereCanTheyGo(DraculaView dv, Player player,
						  int *numReturnedLocs)
{
	bool road = true, rail = true, boat = true;
	return DvWhereCanTheyGoByType(dv, player, road, rail, boat, numReturnedLocs);
}

PlaceId *DvWhereCanTheyGoByType(DraculaView dv, Player player,
								bool road, bool rail, bool boat,
								int *numReturnedLocs)
{
	*numReturnedLocs = 0;

	// player  hasn't  made  a move yet
	int numPlayerMoves = 0;
	bool canFree = false;
	GvGetMoveHistory((GameView)dv, player, &numPlayerMoves, &canFree);
	if (numPlayerMoves == 0) return NULL;

	int numReachable = 0;
	Round round = DvGetRound(dv);
	PlaceId from = DvGetPlayerLocation(dv, player);
	PlaceId *reachable = GvGetReachableByType((GameView)dv, player, round, from, 
												road, rail, boat, &numReachable);
	
	if (player != PLAYER_DRACULA) {
		*numReturnedLocs = numReachable;
		return reachable;
	}
	// Dracula cannot make a LOCATION move if he has already made 
	// a LOCATION move to that same location in the last 5 rounds
	PlaceId *validLocations = malloc(numReachable*sizeof(PlaceId));
	assert(validLocations != NULL);
	int numLastFive = 0;
	PlaceId *lastFiveLocations = GvGetLastMoves((GameView)dv, PLAYER_DRACULA, 5, &numLastFive, &canFree);
	for (int i = 0; i < numReachable; i++) {
		bool found = false;
		for (int j = 0; j < numLastFive; j++) {
			if (reachable[i] == lastFiveLocations[j]) {
				found = true;
				break;
			}
		}
		if (found == true) continue;
		validLocations[(*numReturnedLocs)++] = reachable[i];
	}
	return validLocations;
}
////////////////////////////////////////////////////////////////////////
// Your own interface functions

// TODO
