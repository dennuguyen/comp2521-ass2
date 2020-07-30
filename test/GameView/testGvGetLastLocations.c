#include "testGameView.h"

static void testGvGetLastLocations1();
static void testGvGetLastLocations2();
static void testGvGetLastLocations3();

void testGvGetLastLocations()
{
    printf("Testing GvGetLastLocations...\n");

    testGvGetLastLocations1();
    testGvGetLastLocations2();
    testGvGetLastLocations3();

    printf("GvGetLastLocations tests passed!\n\n");
}

/**
 * Test initialisation on empty string
 */
static void testGvGetLastLocations1()
{
    char *trail = "";
    Message messages[] = {};
    GameView gv = GvNew(trail, messages);
    int *numReturnedLocations = 0;
    bool *canFree = 0;
    assert(GvGetLastLocations(gv, PLAYER_LORD_GODALMING, 1, numReturnedLocations, canFree)[0] == 0);
    assert(*numReturnedLocations == 0);
    assert(*canFree == 0);
    assert(GvGetLastLocations(gv, PLAYER_DR_SEWARD, 1, numReturnedLocations, canFree)[0] == 0);
    assert(*numReturnedLocations == 0);
    assert(*canFree == 0);
    assert(GvGetLastLocations(gv, PLAYER_VAN_HELSING, 1, numReturnedLocations, canFree)[0] == 0);
    assert(*numReturnedLocations == 0);
    assert(*canFree == 0);
    assert(GvGetLastLocations(gv, PLAYER_MINA_HARKER, 1, numReturnedLocations, canFree)[0] == 0);
    assert(*numReturnedLocations == 0);
    assert(*canFree == 0);
    assert(GvGetLastLocations(gv, PLAYER_DRACULA, 1, numReturnedLocations, canFree)[0] == 0);
    assert(*numReturnedLocations == 0);
    assert(*canFree == 0);
    GvFree(gv);
    printf("\tTest 1 passed!\n");
}

/**
 * Test numLocations greater than Locations made
 */
static void testGvGetLastLocations2()
{
    char *trail = "GSW.... SLS.... HMR.... MHA.... DSJ.V..";
    Message messages[] = {};
    GameView gv = GvNew(trail, messages);
    int *numReturnedLocations = 0;
    bool *canFree = 0;
    assert(GvGetLastLocations(gv, PLAYER_LORD_GODALMING, 2, numReturnedLocations, canFree)[0] == SWANSEA);
    assert(*numReturnedLocations == 1);
    assert(*canFree == 0);
    assert(GvGetLastLocations(gv, PLAYER_DRACULA, 2, numReturnedLocations, canFree)[0] == CITY_UNKNOWN);
    assert(*numReturnedLocations == 1);
    assert(*canFree == 0);

    GvFree(gv);
    printf("\tTest 2 passed!\n");
}


/**
 * Test no trap after malfunction
 */
static void testGvGetLastLocations3()
{
    char *trail = 
        "GSW.... SLS.... HMR.... MHA.... DSJ.V.. "
        "GLO.... SAL.... HCO.... MBR.... DBET... "
        "GED.... SBO.... HLI.... MPR.... DKLT... "
        "GLV.... SNA.... HNU.... MBD.... DCDT... "
        "GIR.... SPA.... HPR.... MKLT... DHIT...";

    Message messages[] = {};
    GameView gv = GvNew(trail, messages);
    int *numReturnedLocations = 0;
    bool *canFree = 0;
    assert(GvGetLastLocations(gv, PLAYER_LORD_GODALMING, 2, numReturnedLocations, canFree)[0] == LIVERPOOL);
    assert(GvGetLastLocations(gv, PLAYER_LORD_GODALMING, 2, numReturnedLocations, canFree)[1] == IRISH_SEA);
    assert(*numReturnedLocations == 2);
    assert(*canFree == 0);

    assert(GvGetLastLocations(gv, PLAYER_DRACULA, 4, numReturnedLocations, canFree)[0] == CITY_UNKNOWN);
    assert(GvGetLastLocations(gv, PLAYER_DRACULA, 4, numReturnedLocations, canFree)[1] == KLAUSENBURG);
    assert(GvGetLastLocations(gv, PLAYER_DRACULA, 4, numReturnedLocations, canFree)[2] == CITY_UNKNOWN);
    assert(GvGetLastLocations(gv, PLAYER_DRACULA, 4, numReturnedLocations, canFree)[3] == CITY_UNKNOWN);
    assert(*numReturnedLocations == 4);
    assert(*canFree == 0);

    GvFree(gv);
    printf("\tTest 3 passed!\n");
}
