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
 * Test initialisation on empty string.
 */
static void testGvGetLastLocations1()
{
    char *trail = "";
    Message messages[] = {};
    GameView gv = GvNew(trail, messages);
    int numReturnedLocations = 0;
    bool canFree = false;

    assert(GvGetLastLocations(gv, PLAYER_LORD_GODALMING, 1, &numReturnedLocations, &canFree)[0] == NOWHERE);
    assert(numReturnedLocations == 0);
    assert(canFree == false);
    assert(GvGetLastLocations(gv, PLAYER_DR_SEWARD, 1, &numReturnedLocations, &canFree)[0] == NOWHERE);
    assert(numReturnedLocations == 0);
    assert(canFree == false);
    assert(GvGetLastLocations(gv, PLAYER_VAN_HELSING, 1, &numReturnedLocations, &canFree)[0] == NOWHERE);
    assert(numReturnedLocations == 0);
    assert(canFree == false);
    assert(GvGetLastLocations(gv, PLAYER_MINA_HARKER, 1, &numReturnedLocations, &canFree)[0] == NOWHERE);
    assert(numReturnedLocations == 0);
    assert(canFree == false);
    assert(GvGetLastLocations(gv, PLAYER_DRACULA, 1, &numReturnedLocations, &canFree)[0] == NOWHERE);
    assert(numReturnedLocations == 0);
    assert(canFree == false);

    GvFree(gv);
    printf("\tTest 1 passed!\n");
}

/**
 * Test numLocations greater than Locations made.
 */
static void testGvGetLastLocations2()
{
    char *trail = "GSW.... SLS.... HMR.... MHA.... DSJ.V..";
    Message messages[] = {};
    GameView gv = GvNew(trail, messages);
    int numReturnedLocations = 0;
    bool canFree = false;

    assert(GvGetLastLocations(gv, PLAYER_LORD_GODALMING, 2, &numReturnedLocations, &canFree)[0] == SWANSEA);
    assert(numReturnedLocations == 1);
    assert(canFree == false);

    numReturnedLocations = 0;
    canFree = false;

    assert(GvGetLastLocations(gv, PLAYER_DRACULA, 2, &numReturnedLocations, &canFree)[0] == SARAJEVO);
    assert(numReturnedLocations == 1);
    assert(canFree == false);

    GvFree(gv);
    printf("\tTest 2 passed!\n");
}

/**
 * Test getting two locations.
 */
static void testGvGetLastLocations3()
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

    PlaceId *godalmingLocations = GvGetLastLocations(gv, PLAYER_LORD_GODALMING, 2, &numReturnedLocations, &canFree);
    assert(godalmingLocations[0] == LIVERPOOL);
    assert(godalmingLocations[1] == IRISH_SEA);
    assert(numReturnedLocations == 2);
    assert(canFree == false);

    PlaceId *draculaLocations = GvGetLastLocations(gv, PLAYER_DRACULA, 2, &numReturnedLocations, &canFree);
    assert(draculaLocations[0] == CASTLE_DRACULA);
    assert(draculaLocations[1] == CASTLE_DRACULA);
    assert(numReturnedLocations == 2);
    assert(canFree == false);

    GvFree(gv);
    printf("\tTest 3 passed!\n");
}
