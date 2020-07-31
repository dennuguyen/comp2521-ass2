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
    int numReturnedLocations = 0;
    bool canFree = false;

    assert(GvGetLocationHistory(gv, PLAYER_LORD_GODALMING, &numReturnedLocations, &canFree)[0] == NOWHERE);
    assert(numReturnedLocations == 0);
    assert(canFree == false);
    assert(GvGetLocationHistory(gv, PLAYER_DR_SEWARD, &numReturnedLocations, &canFree)[0] == NOWHERE);
    assert(numReturnedLocations == 0);
    assert(canFree == false);
    assert(GvGetLocationHistory(gv, PLAYER_VAN_HELSING, &numReturnedLocations, &canFree)[0] == NOWHERE);
    assert(numReturnedLocations == 0);
    assert(canFree == false);
    assert(GvGetLocationHistory(gv, PLAYER_MINA_HARKER, &numReturnedLocations, &canFree)[0] == NOWHERE);
    assert(numReturnedLocations == 0);
    assert(canFree == false);
    assert(GvGetLocationHistory(gv, PLAYER_DRACULA, &numReturnedLocations, &canFree)[0] == NOWHERE);
    assert(numReturnedLocations == 0);
    assert(canFree == false);

    GvFree(gv);
    printf("\tTest 1 passed!\n");
}

/**
 * Test no trap after malfunction
 */
static void testGvGetLocationHistory2()
{
    char *trail = "GSW.... SLS.... HMR.... MHA.... DSJ.V.. "
                  "GLO.... SAL.... HCO.... MBR.... DBET... "
                  "GED.... SBO.... HLI.... MPR.... DKLT... "
                  "GLV.... SNA.... HNU.... MBD.... DCDT... "
                  "GIR.... SPA.... HPR.... MKLT... DHIT...";

    Message messages[] = {};
    GameView gv = GvNew(trail, messages);
    int numReturnedLocations = 0;
    bool canFree = false;

    PlaceId *godalmingLocations = GvGetLocationHistory(gv, PLAYER_LORD_GODALMING, &numReturnedLocations, &canFree);
    assert(godalmingLocations[0] == SWANSEA);
    assert(godalmingLocations[1] == LONDON);
    assert(godalmingLocations[2] == EDINBURGH);
    assert(godalmingLocations[3] == LIVERPOOL);
    assert(godalmingLocations[4] == IRISH_SEA);
    assert(numReturnedLocations == 5);
    assert(canFree == false);

    numReturnedLocations = 0;
    canFree = false;

    PlaceId *sewardLocations = GvGetLocationHistory(gv, PLAYER_DR_SEWARD, &numReturnedLocations, &canFree);
    assert(sewardLocations[0] == LISBON);
    assert(sewardLocations[1] == ALICANTE);
    assert(sewardLocations[2] == BORDEAUX);
    assert(sewardLocations[3] == NANTES);
    assert(sewardLocations[4] == PARIS);
    assert(numReturnedLocations == 5);
    assert(canFree == false);

    numReturnedLocations = 0;
    canFree = false;

    PlaceId *vanHelsingLocations = GvGetLocationHistory(gv, PLAYER_VAN_HELSING, &numReturnedLocations, &canFree);
    assert(vanHelsingLocations[0] == MARSEILLES);
    assert(vanHelsingLocations[1] == COLOGNE);
    assert(vanHelsingLocations[2] == LEIPZIG);
    assert(vanHelsingLocations[3] == NUREMBURG);
    assert(vanHelsingLocations[4] == PRAGUE);
    assert(numReturnedLocations == 5);
    assert(canFree == false);

    numReturnedLocations = 0;
    canFree = false;

    PlaceId *minaLocations = GvGetLocationHistory(gv, PLAYER_MINA_HARKER, &numReturnedLocations, &canFree);
    assert(minaLocations[0] == HAMBURG);
    assert(minaLocations[1] == BERLIN);
    assert(minaLocations[2] == PRAGUE);
    assert(minaLocations[3] == BUDAPEST);
    assert(minaLocations[4] == KLAUSENBURG);
    assert(numReturnedLocations == 5);
    assert(canFree == false);

    numReturnedLocations = 0;
    canFree = false;

    PlaceId *draculaLocations = GvGetLocationHistory(gv, PLAYER_DRACULA, &numReturnedLocations, &canFree);
    assert(draculaLocations[0] == SARAJEVO);
    assert(draculaLocations[1] == BELGRADE);
    assert(draculaLocations[2] == KLAUSENBURG);
    assert(draculaLocations[3] == CASTLE_DRACULA);
    assert(draculaLocations[4] == CASTLE_DRACULA);
    assert(numReturnedLocations == 5);
    assert(canFree == false);

    GvFree(gv);
    printf("\tTest 5 passed!\n");
}
