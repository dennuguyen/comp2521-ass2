#include "testGameView.h"

static void testGvNew1();
static void testGvNew2();

void testGvNew()
{
    testGvNew1();
    testGvNew2();
}

/**
 * Test initialisation on empty string
 */
static void testGvNew1()
{
    char *trail = "";
    Message messages[] = {};
    GameView gv = GvNew(trail, messages);

    assert(GvGetRound(gv) == 0);
    assert(GvGetPlayer(gv) == PLAYER_LORD_GODALMING);
    assert(GvGetScore(gv) == GAME_START_SCORE);
    assert(GvGetHealth(gv, PLAYER_LORD_GODALMING) == GAME_START_HUNTER_LIFE_POINTS);
    assert(GvGetHealth(gv, PLAYER_DRACULA) == GAME_START_BLOOD_POINTS);
    assert(GvGetPlayerLocation(gv, PLAYER_LORD_GODALMING) == NOWHERE);
    // assert(GvGetVampireLocation(gv) == NOWHERE);

    printf("\tTest passed!\n");
}

/**
 * Test initialisation on empty string
 */
static void testGvNew2()
{
}