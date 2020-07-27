#include "testGameView.h"

static void testGvGetScore1();
static void testGvGetScore2();

void testGvGetScore()
{
    testGvGetScore1();
    testGvGetScore2();
}

/**
 * Test initialisation on empty string
 */
static void testGvGetScore1()
{
    char *trail = "";
    Message messages[] = {};
    GameView gv = GvNew(trail, messages);

    assert(GvGetScore(gv) == GAME_START_SCORE);

    GvFree(gv);
    printf("Test passed!\n");
}

/**
 * 
 */
static void testGvGetScore2()
{
}