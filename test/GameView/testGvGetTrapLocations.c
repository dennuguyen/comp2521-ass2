#include "testGameView.h"

static void testGvGetTrapLocations1();
static void testGvGetTrapLocations2();
static void testGvGetTrapLocations3();
static void testGvGetTrapLocations4();
static void testGvGetTrapLocations5();

void testGvGetTrapLocations()
{
    printf("Testing GvGetTrapLocations...\n");

    testGvGetTrapLocations1();
    testGvGetTrapLocations2();
    testGvGetTrapLocations3();
    testGvGetTrapLocations4();
    testGvGetTrapLocations5();

    printf("GvGetTrapLocations tests passed!\n\n");
}

/**
 * Test initialisation on empty string
 */
static void testGvGetTrapLocations1()
{
    char *trail = "";
    Message messages[] = {};
    GameView gv = GvNew(trail, messages);

    assert(*GvGetTrapLocations(gv) == 0);
    GvFree(gv);
    printf("\tTest 1 passed!\n");
}

/**
 * Test no trap placed yet
 */
static void testGvGetTrapLocations2()
{
    char *trail = "GSW.... SLS....";
    Message messages[] = {};
    GameView gv = GvNew(trail, messages);

    assert(*GvGetTrapLocations(gv) == 0);
    GvFree(gv);
    printf("\tTest 2 passed!\n");
}
 */

/**
 * Test trap not encountered yet
 */
static void testGvGetTrapLocations3()
{
    char *trail = 
        "GSW.... SLS.... HMR.... MLO.... DSJ.V.. "
        "GSW.... SLS.... HMR.... MMN.... DBET... "
        "GSW.... SLS.... HMR.... MLO.... DKLT... "
    Message messages[] = {};
    GameView gv = GvNew(trail, messages);

    assert(GvGetTrapLocations(gv)[0] == BELGRADE);
    assert(GvGetTrapLocations(gv)[1] == KLAUSENBURG);
    GvFree(gv);
    printf("\tTest 3 passed!\n");
}

/**
 * Test no trap after encounter
 */
static void testGvGetTrapLocations4()
{
    char *trail = 
        "GSW.... SLS.... HMR.... MZA.... DSJ.V.. "
        "GSW.... SLS.... HMR.... MJM.... DBET... "
        "GSW.... SLS.... HMR.... MBETD.. DKLT... "

    Message messages[] = {};
    GameView gv = GvNew(trail, messages);
    assert(GvGetTrapLocations(gv)[0] == KLAUSENBURG);
    GvFree(gv);
    printf("\tTest 4 passed!\n");
}

/**
 * Test no trap after malfunction
 */
static void testGvGetTrapLocations5()
{
    char *trail = 
        "GSW.... SLS.... HMR.... MLO.... DSJ.V.. "
        "GSW.... SLS.... HMR.... MMN.... DBET... "
        "GSW.... SLS.... HMR.... MLO.... DKLT... "
        "GSW.... SLS.... HMR.... MMN.... DBCT... "
        "GSW.... SLS.... HMR.... MLO.... DGAT... "
        "GSW.... SLS.... HMR.... MMN.... DCNT... "
        "GSW.... SLS.... HMR.... MLO.... DVRT.V. "
        "GSW.... SLS.... HMR.... MLO.... DSOT.M.";

    Message messages[] = {};
    GameView gv = GvNew(trail, messages);
    assert(GvGetTrapLocations(gv)[0] == KLAUSENBURG);
    assert(GvGetTrapLocations(gv)[1] == BUCHAREST);
    assert(GvGetTrapLocations(gv)[2] == GALATZ);
    assert(GvGetTrapLocations(gv)[3] == CONSTANTA);
    assert(GvGetTrapLocations(gv)[4] == VARNA);
    assert(GvGetTrapLocations(gv)[5] == SOFIA);
    GvFree(gv);
    printf("\tTest 5 passed!\n");
}
