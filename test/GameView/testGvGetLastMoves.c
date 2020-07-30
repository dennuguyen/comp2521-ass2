#include "testGameView.h"

static void testGvGetLastMoves1();
static void testGvGetLastMoves2();
static void testGvGetLastMoves3();

void testGvGetLastMoves()
{
    printf("Testing GvGetLastMoves...\n");

    testGvGetLastMoves1();
    testGvGetLastMoves2();
    testGvGetLastMoves3();

    printf("GvGetLastMoves tests passed!\n\n");
}

/**
 * Test initialisation on empty string
 */
static void testGvGetLastMoves1()
{
    char *trail = "";
    Message messages[] = {};
    GameView gv = GvNew(trail, messages);
    int *numReturnedMoves = 0;
    bool *canFree = 0;
    assert(GvGetLastMoves(gv, PLAYER_LORD_GODALMING, 1, numReturnedMoves, canFree)[0] == 0);
    assert(*numReturnedMoves == 0);
    assert(*canFree == 0);
    assert(GvGetLastMoves(gv, PLAYER_DR_SEWARD, 1, numReturnedMoves, canFree)[0] == 0);
    assert(*numReturnedMoves == 0);
    assert(*canFree == 0);
    assert(GvGetLastMoves(gv, PLAYER_VAN_HELSING, 1, numReturnedMoves, canFree)[0] == 0);
    assert(*numReturnedMoves == 0);
    assert(*canFree == 0);
    assert(GvGetLastMoves(gv, PLAYER_MINA_HARKER, 1, numReturnedMoves, canFree)[0] == 0);
    assert(*numReturnedMoves == 0);
    assert(*canFree == 0);
    assert(GvGetLastMoves(gv, PLAYER_DRACULA, 1, numReturnedMoves, canFree)[0] == 0);
    assert(*numReturnedMoves == 0);
    assert(*canFree == 0);
    GvFree(gv);
    printf("\tTest 1 passed!\n");
}

/**
 * Test numMoves greater than moves made
 */
static void testGvGetLastMoves2()
{
    char *trail = "GSW.... SLS.... HMR.... MHA.... DSJ.V..";
    Message messages[] = {};
    GameView gv = GvNew(trail, messages);
    int *numReturnedMoves = 0;
    bool *canFree = 0;
    assert(GvGetLastMoves(gv, PLAYER_LORD_GODALMING, 2, numReturnedMoves, canFree)[0] == SWANSEA);
    assert(*numReturnedMoves == 1);
    assert(*canFree == 0);

    GvFree(gv);
    printf("\tTest 2 passed!\n");
}


/**
 * Test no trap after malfunction
 */
static void testGvGetLastMoves3()
{
    char *trail = 
        "GSW.... SLS.... HMR.... MHA.... DSJ.V.. "
        "GLO.... SAL.... HCO.... MBR.... DBET... "
        "GED.... SBO.... HLI.... MPR.... DKLT... "
        "GLV.... SNA.... HNU.... MBD.... DCDT... "
        "GIR.... SPA.... HPR.... MKLT... DHIT...";

    Message messages[] = {};
    GameView gv = GvNew(trail, messages);
    int *numReturnedMoves = 0;
    bool *canFree = 0;
    assert(GvGetLastMoves(gv, PLAYER_LORD_GODALMING, 2, numReturnedMoves, canFree)[0] == LIVERPOOL);
    assert(GvGetLastMoves(gv, PLAYER_LORD_GODALMING, 2, numReturnedMoves, canFree)[1] == IRISH_SEA);
    assert(*numReturnedMoves == 2);
    assert(*canFree == 0);

    assert(GvGetLastMoves(gv, PLAYER_DRACULA, 4, numReturnedMoves, canFree)[0] == BELGRADE);
    assert(GvGetLastMoves(gv, PLAYER_DRACULA, 4, numReturnedMoves, canFree)[1] == KLAUSENBURG);
    assert(GvGetLastMoves(gv, PLAYER_DRACULA, 4, numReturnedMoves, canFree)[2] == CASTLE_DRACULA);
    assert(GvGetLastMoves(gv, PLAYER_DRACULA, 4, numReturnedMoves, canFree)[3] == CASTLE_DRACULA);
    assert(*numReturnedMoves == 2);
    assert(*canFree == 0);

    GvFree(gv);
    printf("\tTest 3 passed!\n");
}
