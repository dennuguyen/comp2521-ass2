#include "testGameView.h"

static void testGvNew1();

void testGvNew()
{
    printf("Testing GvNew...\n");

    testGvNew1();

    printf("GvNew tests passed!\n");
}

/**
 * Test empty string
 */
static void testGvNew1()
{
    char *trail = "";
    Message messages[] = {};
    GameView gv = GvNew(trail, messages);
    int numTraps = 0;
    int numReturned;
    bool canFree = false;

    assert(GvGetRound(gv) == 0);
    assert(GvGetPlayer(gv) == PLAYER_LORD_GODALMING);
    assert(GvGetScore(gv) == GAME_START_SCORE);
    assert(GvGetHealth(gv, PLAYER_LORD_GODALMING) == GAME_START_HUNTER_LIFE_POINTS);
    assert(GvGetHealth(gv, PLAYER_DRACULA) == GAME_START_BLOOD_POINTS);
    assert(GvGetPlayerLocation(gv, PLAYER_LORD_GODALMING) == NOWHERE);
    assert(GvGetVampireLocation(gv) == NOWHERE);

    PlaceId *traps = GvGetTrapLocations(gv, &numTraps);
    assert(traps[0] == NOWHERE);
    assert(numTraps == 0);
    free(traps);

    assert(GvGetMoveHistory(gv, PLAYER_DRACULA, &numReturned, &canFree)[0] == NOWHERE);
    assert(numReturned == 0);
    assert(canFree == false);

    assert(GvGetLastMoves(gv, PLAYER_DRACULA, 2, &numReturned, &canFree)[0] == NOWHERE);
    assert(numReturned == 0);
    assert(canFree == false);

    assert(GvGetLocationHistory(gv, PLAYER_DRACULA, &numReturned, &canFree)[0] == NOWHERE);
    assert(numReturned == 0);
    assert(canFree == false);

    assert(GvGetLastLocations(gv, PLAYER_DRACULA, 2, &numReturned, &canFree)[0] == NOWHERE);
    assert(numReturned == 0);
    assert(canFree == false);

    GvFree(gv);
    printf("\tTest passed!\n");
}
