#include "testGameView.h"

static void testGvGetMoveHistory1();
static void testGvGetMoveHistory2();

void testGvGetMoveHistory()
{
    printf("Testing GvGetMoveHistory...\n");

    testGvGetMoveHistory1();
    testGvGetMoveHistory2();

    printf("GvGetMoveHistory tests passed!\n\n");
}

/**
 * Test initialisation on empty string
 */
static void testGvGetMoveHistory1()
{
    char *trail = "";
    Message messages[] = {};
    GameView gv = GvNew(trail, messages);
    int numReturnedMoves = 0;
    bool canFree = false;

    assert(GvGetMoveHistory(gv, PLAYER_LORD_GODALMING, &numReturnedMoves, &canFree)[0] == NOWHERE);
    assert(numReturnedMoves == 0);
    assert(canFree == false);

    assert(GvGetMoveHistory(gv, PLAYER_DR_SEWARD, &numReturnedMoves, &canFree)[0] == NOWHERE);
    assert(numReturnedMoves == 0);
    assert(canFree == false);

    assert(GvGetMoveHistory(gv, PLAYER_VAN_HELSING, &numReturnedMoves, &canFree)[0] == NOWHERE);
    assert(numReturnedMoves == 0);
    assert(canFree == false);

    assert(GvGetMoveHistory(gv, PLAYER_MINA_HARKER, &numReturnedMoves, &canFree)[0] == NOWHERE);
    assert(numReturnedMoves == 0);
    assert(canFree == false);

    assert(GvGetMoveHistory(gv, PLAYER_DRACULA, &numReturnedMoves, &canFree)[0] == NOWHERE);
    assert(numReturnedMoves == 0);
    assert(canFree == false);

    GvFree(gv);
    printf("\tTest 1 passed!\n");
}

/**
 * Test more rounds
 */
static void testGvGetMoveHistory2()
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

    PlaceId *godalmingMoves = GvGetMoveHistory(gv, PLAYER_LORD_GODALMING, &numReturnedMoves, &canFree);
    assert(godalmingMoves[0] == SWANSEA);
    assert(godalmingMoves[1] == LONDON);
    assert(godalmingMoves[2] == EDINBURGH);
    assert(godalmingMoves[3] == LIVERPOOL);
    assert(godalmingMoves[4] == IRISH_SEA);
    assert(numReturnedMoves == 5);
    assert(canFree == false);

    numReturnedMoves = 0;
    canFree = false;

    PlaceId *sewardMoves = GvGetMoveHistory(gv, PLAYER_DR_SEWARD, &numReturnedMoves, &canFree);
    assert(sewardMoves[0] == LISBON);
    assert(sewardMoves[1] == ALICANTE);
    assert(sewardMoves[2] == BORDEAUX);
    assert(sewardMoves[3] == NANTES);
    assert(sewardMoves[4] == PARIS);
    assert(numReturnedMoves == 5);
    assert(canFree == false);

    numReturnedMoves = 0;
    canFree = false;

    PlaceId *vanHelsingMoves = GvGetMoveHistory(gv, PLAYER_VAN_HELSING, &numReturnedMoves, &canFree);
    assert(vanHelsingMoves[0] == MARSEILLES);
    assert(vanHelsingMoves[1] == COLOGNE);
    assert(vanHelsingMoves[2] == LEIPZIG);
    assert(vanHelsingMoves[3] == NUREMBURG);
    assert(vanHelsingMoves[4] == PRAGUE);
    assert(numReturnedMoves == 5);
    assert(canFree == false);

    numReturnedMoves = 0;
    canFree = false;

    PlaceId *minaMoves = GvGetMoveHistory(gv, PLAYER_MINA_HARKER, &numReturnedMoves, &canFree);
    assert(minaMoves[0] == HAMBURG);
    assert(minaMoves[1] == BERLIN);
    assert(minaMoves[2] == PRAGUE);
    assert(minaMoves[3] == BUDAPEST);
    assert(minaMoves[4] == KLAUSENBURG);
    assert(numReturnedMoves == 5);
    assert(canFree == false);

    numReturnedMoves = 0;
    canFree = false;

    PlaceId *draculaMoves = GvGetMoveHistory(gv, PLAYER_DRACULA, &numReturnedMoves, &canFree);
    assert(draculaMoves[0] == SARAJEVO);
    assert(draculaMoves[1] == BELGRADE);
    assert(draculaMoves[2] == KLAUSENBURG);
    assert(draculaMoves[3] == CASTLE_DRACULA);
    assert(draculaMoves[4] == HIDE);
    assert(numReturnedMoves == 5);
    assert(canFree == false);

    GvFree(gv);
    printf("\tTest 2 passed!\n");
}
