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

#if 0

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

#else

#define CRITICAL_HEALTH 				3

#define START_LORD_GODALMING			
#define START_DR_SEWARD
#define START_VAN_HELSING
#define START_MINA_HARKER


// 
//  
// 
PlaceId FirstMove(HunterView hv);
// 
// 
// 
PlaceId RandomMove(HunterView hv, PlaceId nextpossibledest[], int *numReturnedLocs);
// 
// 
// 
PlaceId AmbushMove(HunterView hv, PlaceId nextpossibledest[], int *numReturnedLocs);
// 
// 
// 
PlaceId ShortestMove(HunterView hv, PlaceId nextpossibledest[], int *numReturnedLocs);
// 
// 
// 
PlaceId RetreatMove(HunterView hv);
// 
// 
// 
PlaceId ResearchMove(HunterView hv);
// 
// 
// 
PlaceId CastleMove(HunterView hv);




void decideHunterMove(HunterView hv)
{

	Round round = HvGetRound(hv);
	Player player = HvGetPlayer(hv);
	int score = HvGetScore(hv, player);
	int health = HvGetHealth(hv, player);
	PlaceId LastDracLoc = HvGetLastKnownDraculaLocation(hv, &round); 

	if (round == 0) 
	{	
		FirstMove(hv);
		return;
	}

	int *numReturnedLocs = malloc(sizeof(int));
	PlaceId nextpossibledest = HvWhereCanIGo(hv, &numReturnedLocs);
	PlaceId MyLocation = hVGetPlayerLocation(hv, player);

	if (player == PLAYER_VAN_HELSING)
	{

	}
	if ()
	{
		AmbushMove(hv, nextpossibledest, &numReturnedLocs);
	}

	if () 
	{
		ResearchMove(hv);
	}

	ShortestMove(hv, nextpossibledest, &numReturnedLocs);


	
}

PlaceId FirstMove(HunterView hv)
{
	Player player = HvGetPlayer(hv);
	switch (player)
	{
		case PLAYER_LORD_GODALMING:	
			char *play = placeIdToAbbrev(START_LORD_GODALMING);
			Message message = "First Move....";	
			registerBestPlay(play, message);
			return START_LORD_GODALMING;
		case PLAYER_DR_SEWARD:
			char *play = placeIdToAbbrev(START_DR_SEWARD);
			Message message = "First Move....";	
			registerBestPlay(play, message);
			return START_DR_SEWARD;
		case PLAYER_VAN_HELSING:
			char *play = placeIdToAbbrev(START_VAN_HELSING);
			Message message = "First Move....";	
			registerBestPlay(play, message);
			return START_VAN_HELSING;
		case PLAYER_MINA_HARKER:
			char *play = placeIdToAbbrev(START_MINA_HARKER);
			Message message = "First Move....";	
			registerBestPlay(play, message);
			return START_MINA_HARKER;		
	}
	return UNKNOWN_PLACE;
}

PlaceId AmbushMove(HunterView hv, PlaceId nextpossibledest[], int *numReturnedLocs)
{
	Round round = HvGetRound(hv);
	PlaceId LastDracLoc = HvGetLastKnownDraculaLocation(hv, round);

	for (int i = 0; i < numReturnedLocs; i++)
	{
		if (LastDracLoc == nextpossibledest[i])
		{
			char *play = placeIdToAbbrev(LastDracLoc);
			Message message = "Suprise Attack....";
			registerBestPlay(play, message);
			return LastDracLoc;
		}
	}
	return UNKNOWN_PLACE;
}

PlaceId ShortestMove(HunterView hv, PlaceId nextpossibledest[], int *numReturnedLocs)
{
	Player player = HvGtePlayer(hv);
	PlaceId MyLocation = HvGetPlayerLocation(hv, player);
	Round round = HvGetRound(hv);
	PlaceId LastDracLoc = HvGetLastKnownDraculaLocation(hv, round);


	if (MyLocation >= MIN_REAL_PLACE && MyLocation <= MAX_REAL_PLACE && LastDracLoc >= MIN_REAL_PLACE && LastDracLoc <= MAX_REAL_PLACE)
	{
		int *pathLength = malloc(sizeof(int));
		PlaceId *PathToDrac = HvGetShortestPathTo(hv, player, LastDracLoc, &pathLength);


		char *play = placeIdToAbbrev(path[1]);
		Message message = "Coming For You....";
		registerBestPlay(play, message);
		return path[1];
	} else
	{
		return UNKNOWN_PLACE;
	}
}

PlaceId RetreatMove(HunterView hv)
{
	Player player = HvGetPlayer(hv);
	PlaceId MyLocation = HvGetPlayerLocation(hv, player);

	int health = HvGetHealth(hv, player);

	if (health <= CRITICAL_HEALTH)
	{
		char *play = placeIdToAbbrev(MyLocation);
		Message message = "Critical Health!!!....";
		registerBestPlay(play, message);
		return MyLocation;
	} else 
	{
		return UNKNOWN_PLACE;
	}
}

PlaceId ResearchMove(HunterView hv)
{



}

#endif