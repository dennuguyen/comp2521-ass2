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
#include "Queue.h"
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
	
}

PlaceId *HvGetShortestPathTo(HunterView hv, Player hunter, PlaceId dest,
							 int *pathLength)
{
	assert ((GameView)hv != NULL);
	PlaceId src = HvGetPlayerLocation(hv, hunter);
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


	struct QueueView queue = QueueNew();
	Enqueue(queue, src, 0); 
	while (!QueueIsEmpty(queue)) {
		PlaceId current = Dequeue(queue)->location;
		if (current == dest) 
		{ 
			break; 
		} 
		ConnList *LocationList = MapGetConnections(hv->map, current);
		for (PlaceId w = 0; w < NUM_REAL_PLACES; w++) 
		{
			if (connListContains(g->map->connections, w, ANY) && visited[w] == 0) 
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
			temp[pathLength++] = v;
			v = pred[v];
		}
		PlaceId *path = malloc(NUM_REAL_PLACES * sizeof(PlaceId));
		for (int i = 0; i < pathLength; i++) {
			path[i] = temp[pathLength - 1 - i]; 
		}
		free(temp);
		return path; 
	}
	return NULL;

}

////////////////////////////////////////////////////////////////////////
// Making a Move

PlaceId *HvWhereCanIGo(HunterView hv, int *numReturnedLocs)
{
	PlaceId *edges;
	Round round = HvGetRound(hv);
	Player player = HvGetPlayer(hv);
	PlaceId src = HvGetPlayerLocation(hv, player);

	edges = GvGetReachable((GameView)hv, player, round, src, numReturnedLocs);

	return edges;
}

PlaceId *HvWhereCanIGoByType(HunterView hv, bool road, bool rail,
							 bool boat, int *numReturnedLocs)
{
	PlaceId *edges;
	Round round = HvGetRound(hv);
	Player player = HvGetPlayer(hv);
	PlaceId src = HvGetPlayerLocation(hv, player);

	edges = GvGetReachableByType((GameView)hv, player, round, src, road, rail, boat, numReturnedLocs);

	return edges;
}

PlaceId *HvWhereCanTheyGo(HunterView hv, Player player,
						  int *numReturnedLocs)
{
	PlaceId *edges;
	Round round = HvGetRound(hv);
	PlaceId src = HvGetPlayerLocation(hv, player);

	edges = GvGetReachable((GameView)hv, player, round, src, numReturnedLocs);

	return edges;
}

PlaceId *HvWhereCanTheyGoByType(HunterView hv, Player player,
								bool road, bool rail, bool boat,
								int *numReturnedLocs)
{
	PlaceId *edges;
	Round round = HvGetRound(hv);
	PlaceId src = HvGetPlayerLocation(hv, player);

	edges = GvGetReachableByType((GameView)hv, player, round, src, road, rail, boat, numReturnedLocs);

	return edges;
}

////////////////////////////////////////////////////////////////////////
// Your own interface functions

// TODO