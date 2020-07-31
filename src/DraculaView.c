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
	GameView super;
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
	// TODO: REPLACE THIS WITH YOUR OWN IMPLEMENTATION
	*numReturnedMoves = 0;
	return NULL;
}

PlaceId *DvWhereCanIGo(DraculaView dv, int *numReturnedLocs)
{
	PlaceId *edges;
	Round round = DvGetRound(hv);
	PlaceId src = DvGetPlayerLocation(hv, player);

	edges = GvGetReachable((GameView)dv, PLAYER_DRACULA, round, src, numReturnedLocs);

	return edges;
}

PlaceId *DvWhereCanIGoByType(DraculaView dv, bool road, bool boat,
							 int *numReturnedLocs)
{
	PlaceId *edges;
	Round round = DvGetRound(hv);
	PlaceId src = DvGetPlayerLocation(hv, player);

	edges = GvGetReachableByType((GameView)dv, PLAYER_DRACULA, round, road, false, boat, src, numReturnedLocs);

	return edges;
}

PlaceId *DvWhereCanTheyGo(DraculaView dv, Player player,
						  int *numReturnedLocs)
{
	PlaceId *edges;
	Round round = DvGetRound(hv);
	Player player = DvGetPlayer(hv);
	PlaceId src = DvGetPlayerLocation(hv, player);

	edges = GvGetReachable((GameView)hv, player, round, src, numReturnedLocs);

	return edges;
}

PlaceId *DvWhereCanTheyGoByType(DraculaView dv, Player player,
								bool road, bool rail, bool boat,
								int *numReturnedLocs)
{
	PlaceId *edges;
	Round round = DvGetRound(hv);
	Player player = DvGetPlayer(hv);
	PlaceId src = DvGetPlayerLocation(hv, player);

	edges = GvGetReachableByType((GameView)dv, player, round, road, rail, boat, src, numReturnedLocs);

	return edges;
}

////////////////////////////////////////////////////////////////////////
// Your own interface functions

// TODO
