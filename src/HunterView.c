////////////////////////////////////////////////////////////////////////
// COMP2521 20T2 ... the Fury of Dracula
// HunterView.c: the HunterView ADT implementation
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
#include "HunterView.h"
#include "Map.h"

struct hunterView
{
	GameView super;
} hunterView;

////////////////////////////////////////////////////////////////////////
// Constructor/Destructor

HunterView HvNew(char *pastPlays, Message messages[])
{
	HunterView hv = (void *)GvNew(pastPlays, messages);
	return hv;
}

void HvFree(HunterView hv)
{
	GvFree((GameView)hv);
}

////////////////////////////////////////////////////////////////////////
// Game State Information

Round HvGetRound(HunterView hv)
{
	return GvGetRound((GameView)hv);
}

Player HvGetPlayer(HunterView hv)
{
	return GvGetPlayer((GameView)hv);
}

int HvGetScore(HunterView hv)
{
	return GvGetScore((GameView)hv);
}

int HvGetHealth(HunterView hv, Player player)
{
	return GvGetHealth((GameView)hv, player);
}

PlaceId HvGetPlayerLocation(HunterView hv, Player player)
{
	return GvGetPlayerLocation((GameView)hv, player);
}

PlaceId HvGetVampireLocation(HunterView hv)
{
	return GvGetVampireLocation((GameView)hv);
}

////////////////////////////////////////////////////////////////////////
// Utility Functions

PlaceId HvGetLastKnownDraculaLocation(HunterView hv, Round *round)
{
	return GvGetLastKnownDraculaLocation((GameView)hv, round);
}

//static int adjacent(Map m, PlaceId x, PlaceId y) {
   //for (int i = 0; i < )
   
   //return (g->edges[x][y] != 0);
//}

PlaceId *HvGetShortestPathTo(HunterView hv, Player hunter, PlaceId dest,
							 int *pathLength)
{	/*
	assert ((GameView)hv != NULL);
	PlaceId src = HvGetPlayerLocation(hv, hunter);
	int *visited = calloc(MapNumPlaces(hv->map), sizeof(int));
	PlaceId *pred = calloc(MapNumPlaces(hv->map), sizeof(PlaceId));
	ConnQueue q = newQueue();
	Enqueue(q,src, );
	bool isFound = false;
	visited[src] = 1;
	if (src == dest) isFound = true;
	else {
		while (q->head != NULL && !isFound) {
			PlaceId y, x = Dequeue(q);
			for (y = 0; y < MapNumPlaces(hv->map); y++) {
				if (!)
			}
		}
	}
	
	
	
	
	if (src == dest) {
		*pathLength = 1;
		PlaceId *Location = malloc(NUM_REAL_PLACES * sizeof(PlaceId));
		assert(Location != NULL);
		*Location = src;
		return Location;
	}

	int visited[NUM_REAL_PLACES] = {0};
	int pred[NUM_REAL_PLACES];
	for (int i = 0; i < NUM_REAL_PLACES; i++)
	{
		pred[i] = -1;
	}

	Queue queue = QueueNew();
	Enqueue(queue, src, 0); 
	while (!QueueIsEmpty(queue)) {
		QueueNode current = Dequeue(queue);
		if (current->head->location == dest) 
		{ 
			break; 
		} 
		ConnList *LocationList = MapGetConnections((GameView)hv, src);

		for (PlaceId w = 0; w < NUM_REAL_PLACES; w++) 
		{
			if (visited[w] == 0) 
			{
				pred[w] = current;
				visited[w] = 1;
				Enqueue(queue, w, 0);	
			}
		}			
	}
	if (pred[dest] != -1) {
		PlaceId *temp = malloc(NUM_REAL_PLACES * sizeof(PlaceId));
		PlaceId v = dest;
		while (v != src) {
			temp[*pathLength++] = v;
			v = pred[v];
		}
		PlaceId *path = malloc(NUM_REAL_PLACES * sizeof(PlaceId));
		for (int i = 0; i < pathLength; i++) {
			path[i] = temp[*pathLength - 1 - i]; 
		}
		free(temp);
		return path; 
	}
	return NULL;*/
	*pathLength = 0;
	return NULL;
}

////////////////////////////////////////////////////////////////////////
// Making a Move

PlaceId *HvWhereCanIGo(HunterView hv, int *numReturnedLocs)
{
	Player player = HvGetPlayer(hv);
	bool road = true, rail = true, boat = true;
	return HvWhereCanTheyGoByType(hv, player, road, rail, boat, numReturnedLocs);
}

PlaceId *HvWhereCanIGoByType(HunterView hv, bool road, bool rail,
							 bool boat, int *numReturnedLocs)
{
	Player player = HvGetPlayer(hv);
	return HvWhereCanTheyGoByType(hv, player, road, rail, boat, numReturnedLocs);
}

PlaceId *HvWhereCanTheyGo(HunterView hv, Player player,
						  int *numReturnedLocs)
{
	bool road = true, rail = true, boat = true;
	return HvWhereCanTheyGoByType(hv, player, road, rail, boat, numReturnedLocs);
}

PlaceId *HvWhereCanTheyGoByType(HunterView hv, Player player,
								bool road, bool rail, bool boat,
								int *numReturnedLocs)
{
	*numReturnedLocs = 0;
	// player  hasn't  made  a move yet
	int numPlayerMoves = 0;
	bool canFree = false;
	GvGetMoveHistory((GameView)hv, player, &numPlayerMoves, &canFree);
	if (numPlayerMoves == 0) return NULL;

	int numReachable = 0;
	Round round = HvGetRound(hv);
	PlaceId from = HvGetPlayerLocation(hv, player);
	PlaceId *reachable = GvGetReachableByType((GameView)hv, player, round, from, 
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
	PlaceId *lastFiveLocations = GvGetLastMoves((GameView)hv, PLAYER_DRACULA, 5, &numLastFive, &canFree);
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
