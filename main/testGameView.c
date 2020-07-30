////////////////////////////////////////////////////////////////////////
// COMP2521 20T2 ... the Fury of Dracula
// testGameView.c: test the GameView ADT
//
// As supplied, these are very simple tests.  You should write more!
// Don't forget to be rigorous and thorough while writing tests.
//
// 2014-07-01	v1.0	Team Dracula <cs2521@cse.unsw.edu.au>
// 2017-12-01	v1.1	Team Dracula <cs2521@cse.unsw.edu.au>
// 2018-12-31	v1.1	Team Dracula <cs2521@cse.unsw.edu.au>
// 2020-07-10	v1.2	Team Dracula <cs2521@cse.unsw.edu.au>
//
////////////////////////////////////////////////////////////////////////

#include "testGameView.h"

int main(void)
{
	// testGvNew();
	// testGvGetRound();
	// testGvGetPlayer();
	// testGvGetScore();
	// testGvGetHealth();
	// testGvGetPlayerLocation();
	// testGvGetVampireLocation();
	// testGvGetTrapLocations();
	// testGvGetMoveHistory();
	testGvGetLastMoves();
	testGvGetLocationHistory();
	testGvGetLastLocations();
	// testGvGetReachable();
	// testGvGetReachableByType();

	// testGv();
	return EXIT_SUCCESS;
}
