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
    int *numReturnedMoves = 0;
    bool *canFree = 0;
    assert(GvGetMoveHistory(gv, PLAYER_LORD_GODALMING, numReturnedMoves, canFree)[0] == 0);
    assert(*numReturnedMoves == 0);
    assert(*canFree == 0);
    assert(GvGetMoveHistory(gv, PLAYER_DR_SEWARD, numReturnedMoves, canFree)[0] == 0);
    assert(*numReturnedMoves == 0);
    assert(*canFree == 0);
    assert(GvGetMoveHistory(gv, PLAYER_VAN_HELSING, numReturnedMoves, canFree)[0] == 0);
    assert(*numReturnedMoves == 0);
    assert(*canFree == 0);
    assert(GvGetMoveHistory(gv, PLAYER_MINA_HARKER, numReturnedMoves, canFree)[0] == 0);
    assert(*numReturnedMoves == 0);
    assert(*canFree == 0);
    assert(GvGetMoveHistory(gv, PLAYER_DRACULA, numReturnedMoves, canFree)[0] == 0);
    assert(*numReturnedMoves == 0);
    assert(*canFree == 0);
    GvFree(gv);
    printf("\tTest 1 passed!\n");
}


/**
 * Test no trap after malfunction
 */
static void testGvGetMoveHistory2()
{
    char *trail = 
        "GSW.... SLS.... HMR.... MHA.... DSJ.V.. "
        "GLO.... SAL.... HCO.... MBR.... DBET... "
        "GED.... SBO.... HLI.... MPR.... DKLT... "
        "GLV.... SNA.... HNU.... MBD.... DCDT... "
        "GIR.... SPA.... HPR.... MKLT... DHIT... ";

    Message messages[] = {};
    GameView gv = GvNew(trail, messages);
    int *numReturnedMoves = 0;
    bool *canFree = 0;

    assert(GvGetMoveHistory(gv, PLAYER_LORD_GODALMING, numReturnedMoves, canFree)[0] == SWANSEA);
    assert(GvGetMoveHistory(gv, PLAYER_LORD_GODALMING, numReturnedMoves, canFree)[1] == LONDON);
    assert(GvGetMoveHistory(gv, PLAYER_LORD_GODALMING, numReturnedMoves, canFree)[2] == EDINBURGH);
    assert(GvGetMoveHistory(gv, PLAYER_LORD_GODALMING, numReturnedMoves, canFree)[3] == LIVERPOOL);
    assert(GvGetMoveHistory(gv, PLAYER_LORD_GODALMING, numReturnedMoves, canFree)[4] == IRISH_SEA);
    assert(*numReturnedMoves == 5);
    assert(*canFree == 0);
    assert(GvGetMoveHistory(gv, PLAYER_DR_SEWARD, numReturnedMoves, canFree)[0] == LISBON);
    assert(GvGetMoveHistory(gv, PLAYER_DR_SEWARD, numReturnedMoves, canFree)[1] == ALICANTE);
    assert(GvGetMoveHistory(gv, PLAYER_DR_SEWARD, numReturnedMoves, canFree)[2] == BORDEAUX);
    assert(GvGetMoveHistory(gv, PLAYER_DR_SEWARD, numReturnedMoves, canFree)[3] == NANTES);
    assert(GvGetMoveHistory(gv, PLAYER_DR_SEWARD, numReturnedMoves, canFree)[4] == PARIS);
    assert(*numReturnedMoves == 5);
    assert(*canFree == 0);
    assert(GvGetMoveHistory(gv, PLAYER_VAN_HELSING, numReturnedMoves, canFree)[0] == MARSEILLES);
    assert(GvGetMoveHistory(gv, PLAYER_VAN_HELSING, numReturnedMoves, canFree)[1] == COLOGNE);
    assert(GvGetMoveHistory(gv, PLAYER_VAN_HELSING, numReturnedMoves, canFree)[2] == LEIPZIG);
    assert(GvGetMoveHistory(gv, PLAYER_VAN_HELSING, numReturnedMoves, canFree)[3] == NUREMBURG);
    assert(GvGetMoveHistory(gv, PLAYER_VAN_HELSING, numReturnedMoves, canFree)[4] == PRAGUE);
    assert(*numReturnedMoves == 5);
    assert(*canFree == 0);
    assert(GvGetMoveHistory(gv, PLAYER_MINA_HARKER, numReturnedMoves, canFree)[0] == HAMBURG);
    assert(GvGetMoveHistory(gv, PLAYER_MINA_HARKER, numReturnedMoves, canFree)[1] == BERLIN);
    assert(GvGetMoveHistory(gv, PLAYER_MINA_HARKER, numReturnedMoves, canFree)[2] == PRAGUE);
    assert(GvGetMoveHistory(gv, PLAYER_MINA_HARKER, numReturnedMoves, canFree)[3] == BUDAPEST);
    assert(GvGetMoveHistory(gv, PLAYER_MINA_HARKER, numReturnedMoves, canFree)[4] == KLAUSENBURG);
    assert(*numReturnedMoves == 5);
    assert(*canFree == 0);
    assert(GvGetMoveHistory(gv, PLAYER_DRACULA, numReturnedMoves, canFree)[0] == SARAJEVO);
    assert(GvGetMoveHistory(gv, PLAYER_DRACULA, numReturnedMoves, canFree)[1] == BELGRADE);
    assert(GvGetMoveHistory(gv, PLAYER_DRACULA, numReturnedMoves, canFree)[2] == KLAUSENBURG);
    assert(GvGetMoveHistory(gv, PLAYER_DRACULA, numReturnedMoves, canFree)[3] == CASTLE_DRACULA);
    assert(GvGetMoveHistory(gv, PLAYER_DRACULA, numReturnedMoves, canFree)[4] == CASTLE_DRACULA);
    assert(*numReturnedMoves == 5);
    assert(*canFree == 0);
    GvFree(gv);
    printf("\tTest 5 passed!\n");
}
