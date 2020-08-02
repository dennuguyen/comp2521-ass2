////////////////////////////////////////////////////////////////////////
// COMP2521 20T2 ... the Fury of Dracula
// hunter.c: your "Fury of Dracula" hunter AI.
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
 * - strategy in moving around (when you don't know where Dracula is)
 * - strategy in moving around (when you do know where Dracula is)
 * - localising Dracula (Dracula's where-abouts)
 * - strategy in finding vampire locations
 */

#include <string.h>
#include <time.h>

#include "Game.h"
#include "hunter.h"
#include "HunterView.h"

/**
 * Random strategy.
 */
static PlaceId strategy1(HunterView hv)
{
	srand(time(NULL));
	int numReturnedMoves = 0;
	PlaceId *validMoves = HvWhereCanIGo(hv, &numReturnedMoves);
	int index = rand() % 10;

	for (int i = 0; i < numReturnedMoves; i++)
		if (validMoves[i] == index)
			return validMoves[i];

	switch (HvGetPlayer(hv))
	{
	case PLAYER_LORD_GODALMING:
		return TOULOUSE;
	case PLAYER_DR_SEWARD:
		return FRANKFURT;
	case PLAYER_VAN_HELSING:
		return VENICE;
	case PLAYER_MINA_HARKER:
		return BELGRADE;
	case PLAYER_DRACULA:
		break;
	}

	return GENOA;
}

/**
 * Simulate possible future game states and pick best move.
 */
// static PlaceId strategy2(HunterView hv)
// {
// }

void decideHunterMove(HunterView hv)
{
	char *move = malloc(3 * sizeof(char));
	strncpy(move, placeIdToAbbrev(strategy1(hv)), 3);
	registerBestPlay(move, "GW");
	free(move);
}
