////////////////////////////////////////////////////////////////////////
// COMP2521 20T2 ... the Fury of Dracula
// testDraculaView.c: test the DraculaView ADT
//
// As supplied, these are very simple tests.  You should write more!
// Don't forget to be rigorous and thorough while writing tests.
//
// 2014-07-01	v1.0	Team Dracula <cs2521@cse.unsw.edu.au>
// 2017-12-02	v1.1	Team Dracula <cs2521@cse.unsw.edu.au>
// 2018-12-31	v2.0	Team Dracula <cs2521@cse.unsw.edu.au>
// 2020-07-10	v3.0	Team Dracula <cs2521@cse.unsw.edu.au>
//
////////////////////////////////////////////////////////////////////////

#include "testDraculaView.h"

int main(void)
{
	testDvNew();
	// testDvFree();
	testDvGetRound();
	testDvGetScore();
	testDvGetHealth();
	testDvGetPlayerLocation();
	testDvGetVampireLocation();
	// testDvGetTrapLocations();
	testDv();
	return EXIT_SUCCESS;
}
