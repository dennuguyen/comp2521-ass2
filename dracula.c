////////////////////////////////////////////////////////////////////////
// COMP2521 20T2 ... the Fury of Dracula
// dracula.c: your "Fury of Dracula" Dracula AI
//
// 2014-07-01	v1.0	Team Dracula <cs2521@cse.unsw.edu.au>
// 2017-12-01	v1.1	Team Dracula <cs2521@cse.unsw.edu.au>
// 2018-12-31	v2.0	Team Dracula <cs2521@cse.unsw.edu.au>
// 2020-07-10	v3.0	Team Dracula <cs2521@cse.unsw.edu.au>
//
////////////////////////////////////////////////////////////////////////

/**
 * Objectives:
 * - Keep score low
 * 
 * Heuristics:
 * - 
 * 
 * Strategies:
 * - starting location
 * - strategy in avoiding players (keep out of their where-abouts)
 * - strategy in placing traps (offensive)
 * - strategy in placing vampires
 * 
 * 
 */

#include <string.h>
#include <time.h>

#include "dracula.h"
#include "DraculaView.h"
#include "Game.h"

/**
 * Random strategy.
 */
static PlaceId strategy1(DraculaView dv)
{
	srand(time(NULL));
	int numReturnedMoves = 0;
	PlaceId *validMoves = DvGetValidMoves(dv, &numReturnedMoves);
	int index = rand() % 10;

	for (int i = 0; i < numReturnedMoves; i++)
		if (validMoves[i] == index)
			return validMoves[i];

	return GRANADA;
}

/**
 * Simulate possible future game states and pick best move.
 */
// static PlaceId strategy2(DraculaView dv)
// {
// }

void decideDraculaMove(DraculaView dv)
{
	char *move = malloc(3 * sizeof(char));
	strncpy(move, placeIdToAbbrev(strategy1(dv)), 3);
	registerBestPlay(move, "GW");
	free(move);
}
