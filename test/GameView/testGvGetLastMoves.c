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
    int numReturnedMoves = 0;
    bool canFree = false;

    assert(GvGetLastMoves(gv, PLAYER_LORD_GODALMING, 1, &numReturnedMoves, &canFree)[0] == NOWHERE);
    assert(numReturnedMoves == 0);
    assert(canFree == false);
    assert(GvGetLastMoves(gv, PLAYER_DR_SEWARD, 1, &numReturnedMoves, &canFree)[0] == NOWHERE);
    assert(numReturnedMoves == 0);
    assert(canFree == false);
    assert(GvGetLastMoves(gv, PLAYER_VAN_HELSING, 1, &numReturnedMoves, &canFree)[0] == NOWHERE);
    assert(numReturnedMoves == 0);
    assert(canFree == false);
    assert(GvGetLastMoves(gv, PLAYER_MINA_HARKER, 1, &numReturnedMoves, &canFree)[0] == NOWHERE);
    assert(numReturnedMoves == 0);
    assert(canFree == false);
    assert(GvGetLastMoves(gv, PLAYER_DRACULA, 1, &numReturnedMoves, &canFree)[0] == NOWHERE);
    assert(numReturnedMoves == 0);
    assert(canFree == false);

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
    int numReturnedMoves = 0;
    bool canFree = false;

    assert(GvGetLastMoves(gv, PLAYER_LORD_GODALMING, 2, &numReturnedMoves, &canFree)[0] == SWANSEA);
    assert(numReturnedMoves == 1);
    assert(canFree == false);

    GvFree(gv);
    printf("\tTest 2 passed!\n");
}

/**
 * Test no trap after malfunction
 */
static void testGvGetLastMoves3()
{
    char *trail = "GSW.... SLS.... HMR.... MHA.... DSJ.V.. "
                  "GLO.... SAL.... HCO.... MBR.... DBET... "
                  "GED.... SBO.... HLI.... MPR.... DKLT... "
                  "GLV.... SNA.... HNU.... MBD.... DCDT... "
                  "GIR.... SPA.... HPR.... MKLT... DHIT...";

    Message messages[] = {};
    GameView gv = GvNew(trail, messages);
    int numReturnedMoves = 0;
    bool canFree = false;

    PlaceId *godalmingMoves = GvGetLastMoves(gv, PLAYER_LORD_GODALMING, 2, &numReturnedMoves, &canFree);
    assert(godalmingMoves[0] == LIVERPOOL);
    assert(godalmingMoves[1] == IRISH_SEA);
    assert(numReturnedMoves == 2);
    assert(canFree == false);

    numReturnedMoves = 0;
    canFree = false;

    PlaceId *draculaMoves = GvGetLastMoves(gv, PLAYER_DRACULA, 4, &numReturnedMoves, &canFree);
    assert(draculaMoves[0] == BELGRADE);
    assert(draculaMoves[1] == KLAUSENBURG);
    assert(draculaMoves[2] == CASTLE_DRACULA);
    assert(draculaMoves[3] == HIDE);
    assert(numReturnedMoves == 4);
    assert(canFree == false);

    GvFree(gv);
    printf("\tTest 3 passed!\n");
}
