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
{
	/*
	assert(g != NULL);

    // cities are visited only once therefore leaving only one predecessor
    int *breadcrumbs = malloc(g->nV * sizeof(int));
    for (int i = 0; i < g->nV; i++)
        path[i] = breadcrumbs[i] = -1;

    Queue pq = newQueue(); // previous city queue
    Queue nq = newQueue(); // next city queue
    Queue wq = newQueue(); // weighting queue for number of trips
    QueueJoin(pq, src);
    QueueJoin(nq, src);
    QueueJoin(wq, 1);

    while (!QueueIsEmpty(nq))
    {
        Item p_city = QueueLeave(pq);
        Item n_city = QueueLeave(nq);
        Item n_trip = QueueLeave(wq);

        // if city is not in breadcrumb trail
        if (breadcrumbs[n_city] == -1)
        {
            breadcrumbs[n_city] = p_city;

            // arrived at destination
            if (n_city == dest)
            {
                // follow breadcrumbs back to src
                path[n_trip - 1] = dest;
                for (int i = n_trip - 2, b = dest; i >= 0; i--)
                    path[i] = b = breadcrumbs[b];
                dropQueue(pq);
                dropQueue(nq);
                dropQueue(wq);
                free(breadcrumbs);
                return n_trip; // return number of trips
            }

            // enqueue children cities from parent city if distance < max
            for (int i = 0; i < g->nV; i++)
                if (g->edges[n_city][i] < max)
                {
                    QueueJoin(pq, n_city);
                    QueueJoin(nq, i);
                    QueueJoin(wq, n_trip + 1);
                }
        }
    }

    dropQueue(pq);
    dropQueue(nq);
    dropQueue(wq);
    free(breadcrumbs);
	*/

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
	if (numPlayerMoves == 0)
		return NULL;

	int numReachable = 0;
	Round round = HvGetRound(hv);
	PlaceId from = HvGetPlayerLocation(hv, player);
	PlaceId *reachable = GvGetReachableByType((GameView)hv, player, round, from,
											  road, rail, boat, &numReachable);

	if (player != PLAYER_DRACULA)
	{
		*numReturnedLocs = numReachable;
		return reachable;
	}
	// Dracula cannot make a LOCATION move if he has already made
	// a LOCATION move to that same location in the last 5 rounds
	PlaceId *validLocations = malloc(numReachable * sizeof(PlaceId));
	assert(validLocations != NULL);
	int numLastFive = 0;
	PlaceId *lastFiveLocations = GvGetLastMoves((GameView)hv, PLAYER_DRACULA, 5, &numLastFive, &canFree);
	for (int i = 0; i < numReachable; i++)
	{
		bool found = false;
		for (int j = 0; j < numLastFive; j++)
		{
			if (reachable[i] == lastFiveLocations[j])
			{
				found = true;
				break;
			}
		}
		if (found == true)
			continue;
		validLocations[(*numReturnedLocs)++] = reachable[i];
	}
	return validLocations;
}

////////////////////////////////////////////////////////////////////////
// Your own interface functions

// TODO
