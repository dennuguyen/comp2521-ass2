#include "testGameView.h"

static void testGvGetLocationHistory1();
static void testGvGetLocationHistory2();

void testGvGetLocationHistory()
{
    printf("Testing GvGetLocationHistory...\n");

    testGvGetLocationHistory1();
    testGvGetLocationHistory2();

    printf("GvGetLocationHistory tests passed!\n\n");
}

/**
 * Test initialisation on empty string
 */
static void testGvGetLocationHistory1()
{
    char *trail = "";
    Message messages[] = {};
    GameView gv = GvNew(trail, messages);
    int *numReturnedMoves = 0;
    bool *canFree = 0;
    assert(GvGetLocationHistory(gv, PLAYER_LORD_GODALMING, numReturnedMoves, canFree)[0] == 0);
    assert(*numReturnedMoves == 0);
    assert(*canFree == 0);
    assert(GvGetLocationHistory(gv, PLAYER_DR_SEWARD, numReturnedMoves, canFree)[0] == 0);
    assert(*numReturnedMoves == 0);
    assert(*canFree == 0);
    assert(GvGetLocationHistory(gv, PLAYER_VAN_HELSING, numReturnedMoves, canFree)[0] == 0);
    assert(*numReturnedMoves == 0);
    assert(*canFree == 0);
    assert(GvGetLocationHistory(gv, PLAYER_MINA_HARKER, numReturnedMoves, canFree)[0] == 0);
    assert(*numReturnedMoves == 0);
    assert(*canFree == 0);
    assert(GvGetLocationHistory(gv, PLAYER_DRACULA, numReturnedMoves, canFree)[0] == 0);
    assert(*numReturnedMoves == 0);
    assert(*canFree == 0);
    GvFree(gv);
    printf("\tTest 1 passed!\n");
}


/**
 * Test no trap after malfunction
 */
static void testGvGetLocationHistory2()
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

    assert(GvGetLocationHistory(gv, PLAYER_LORD_GODALMING, numReturnedMoves, canFree)[0] == SWANSEA);
    assert(GvGetLocationHistory(gv, PLAYER_LORD_GODALMING, numReturnedMoves, canFree)[1] == LONDON);
    assert(GvGetLocationHistory(gv, PLAYER_LORD_GODALMING, numReturnedMoves, canFree)[2] == EDINBURGH);
    assert(GvGetLocationHistory(gv, PLAYER_LORD_GODALMING, numReturnedMoves, canFree)[3] == LIVERPOOL);
    assert(GvGetLocationHistory(gv, PLAYER_LORD_GODALMING, numReturnedMoves, canFree)[4] == IRISH_SEA);
    assert(*numReturnedMoves == 5);
    assert(*canFree == 0);
    assert(GvGetLocationHistory(gv, PLAYER_DR_SEWARD, numReturnedMoves, canFree)[0] == LISBON);
    assert(GvGetLocationHistory(gv, PLAYER_DR_SEWARD, numReturnedMoves, canFree)[1] == ALICANTE);
    assert(GvGetLocationHistory(gv, PLAYER_DR_SEWARD, numReturnedMoves, canFree)[2] == BORDEAUX);
    assert(GvGetLocationHistory(gv, PLAYER_DR_SEWARD, numReturnedMoves, canFree)[3] == NANTES);
    assert(GvGetLocationHistory(gv, PLAYER_DR_SEWARD, numReturnedMoves, canFree)[4] == PARIS);
    assert(*numReturnedMoves == 5);
    assert(*canFree == 0);
    assert(GvGetLocationHistory(gv, PLAYER_VAN_HELSING, numReturnedMoves, canFree)[0] == MARSEILLES);
    assert(GvGetLocationHistory(gv, PLAYER_VAN_HELSING, numReturnedMoves, canFree)[1] == COLOGNE);
    assert(GvGetLocationHistory(gv, PLAYER_VAN_HELSING, numReturnedMoves, canFree)[2] == LEIPZIG);
    assert(GvGetLocationHistory(gv, PLAYER_VAN_HELSING, numReturnedMoves, canFree)[3] == NUREMBURG);
    assert(GvGetLocationHistory(gv, PLAYER_VAN_HELSING, numReturnedMoves, canFree)[4] == PRAGUE);
    assert(*numReturnedMoves == 5);
    assert(*canFree == 0);
    assert(GvGetLocationHistory(gv, PLAYER_MINA_HARKER, numReturnedMoves, canFree)[0] == HAMBURG);
    assert(GvGetLocationHistory(gv, PLAYER_MINA_HARKER, numReturnedMoves, canFree)[1] == BERLIN);
    assert(GvGetLocationHistory(gv, PLAYER_MINA_HARKER, numReturnedMoves, canFree)[2] == PRAGUE);
    assert(GvGetLocationHistory(gv, PLAYER_MINA_HARKER, numReturnedMoves, canFree)[3] == BUDAPEST);
    assert(GvGetLocationHistory(gv, PLAYER_MINA_HARKER, numReturnedMoves, canFree)[4] == KLAUSENBURG);
    assert(*numReturnedMoves == 5);
    assert(*canFree == 0);
    assert(GvGetLocationHistory(gv, PLAYER_DRACULA, numReturnedMoves, canFree)[0] == CITY_UNKNOWN);
    assert(GvGetLocationHistory(gv, PLAYER_DRACULA, numReturnedMoves, canFree)[1] == CITY_UNKNOWN);
    assert(GvGetLocationHistory(gv, PLAYER_DRACULA, numReturnedMoves, canFree)[2] == KLAUSENBURG);
    assert(GvGetLocationHistory(gv, PLAYER_DRACULA, numReturnedMoves, canFree)[3] == CITY_UNKNOWN);
    assert(GvGetLocationHistory(gv, PLAYER_DRACULA, numReturnedMoves, canFree)[4] == CITY_UNKNOWN);
    assert(*numReturnedMoves == 5);
    assert(*canFree == 0);
    GvFree(gv);
    printf("\tTest 5 passed!\n");
}
