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
#include "Queue.h"

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

static bool isReachable(HunterView hv, Player player, Round round, PlaceId from, 
						PlaceId dest);

PlaceId *HvGetShortestPathTo(HunterView hv, Player hunter, PlaceId dest,
							 int *pathLength)
{
	//assert (hv->super->map != NULL);

	//assert (MapNumPlaces(hv->super->map) == NUM_REAL_PLACES);

	// declare array to store if Place has been visited
	bool *visited = malloc(NUM_REAL_PLACES * sizeof(PlaceId));
	if (visited == NULL)
	{
		fprintf(stderr, "ERROR: Could not allocate memory.\n");
		exit(EXIT_FAILURE);
	}

	// declare array to store predecessor node along path
	PlaceId *pred = malloc(NUM_REAL_PLACES * sizeof(PlaceId));
	if (pred == NULL)
	{
		fprintf(stderr, "ERROR: Could not allocate memory.\n");
		exit(EXIT_FAILURE);
	}

	// declare array to store round number after move
	int *round = malloc(NUM_REAL_PLACES * sizeof(int));
	if (round == NULL)
	{
		fprintf(stderr, "ERROR: Could not allocate memory.\n");
		exit(EXIT_FAILURE);
	}
	Round roundNum = HvGetRound(hv);
	
	for (int i = 0; i < NUM_REAL_PLACES; i++) {
		visited[i] = false;
		pred[i] = NOWHERE;
		round[i] = roundNum;
	}

	// create a queue to store Places
	_Queue q = _QueueNew();
	
	// add 'from' to queue
	PlaceId from = HvGetPlayerLocation(hv, hunter);
	_Enqueue(q, from);
	visited[from] = true;
	
	bool isFound = false;
	// special case: 'from' is same as 'dest'
	if (from == dest) isFound = true;
	else {
		while (!_QueueIsEmpty(q) && !isFound) {
		    PlaceId b, a = _Dequeue(q);
		    for (b = MIN_REAL_PLACE; b < NUM_REAL_PLACES; b++) {
				bool reachable = isReachable(hv, hunter, round[a], a, b);
		        if (!reachable || visited[b]) continue;
		        visited[b] = true;
		        pred[b] = a;
				round[b] = round[a]++;
		        if (b == dest) { isFound = true; break; }
		        _Enqueue(q, b);
		    }
		}
	}
	if (!isFound) return NULL; // no path
	else {
		PlaceId *path = malloc(NUM_REAL_PLACES * sizeof(PlaceId));
		if (path == NULL)
		{
			fprintf(stderr, "ERROR: Could not allocate memory.\n");
			exit(EXIT_FAILURE);
		}
		if (path == NULL)
		{
			fprintf(stderr, "ERROR: Could not allocate memory for locations.\n");
			exit(EXIT_FAILURE);
		}
		int count = 0;
	    // extract dest->from path using pred[v]
	    for (PlaceId v = dest; v != from; v = pred[v]) {
	        path[count] = v;
    	    count++;
	    }
	    // reverse path array to go from->dest
	    int temp; 
	    int start = 0;
	    int end = count - 1;
	    while (start < end) 
	    { 
	        temp = path[start];    
	        path[start] = path[end]; 
	        path[end] = temp; 
	        start++; 
	        end--; 
	    }

	    // free memory
	    free(visited);
	    free(pred);
		free(round);
	    _QueueFree(q);
		*pathLength = count;
	    return path;
	}
	//return GvGetShortestPathTo((GameView)hv, hunter, dest, pathLength);
}

static bool isReachable(HunterView hv, Player hunter, Round round, PlaceId from, PlaceId dest)
{
	// get reachable places
	int numReachable = 0;
	PlaceId *reachable = GvGetReachable((GameView)hv, hunter, round, from, &numReachable);
	for (int i = 0; i < numReachable; i++)
		if (reachable[i] == dest) return true;
   	return false;
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
	if (validLocations == NULL)
	{
		fprintf(stderr, "ERROR: Could not allocate memory.\n");
		exit(EXIT_FAILURE);
	}
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
