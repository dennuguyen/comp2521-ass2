#include "testGameView.h"

static void testGvGetRound1();
static void testGvGetRound2();

void testGvGetRound()
{
    testGvGetRound1();
    testGvGetRound2();
}

/**
 * Test initialisation on empty string
 */
static void testGvGetRound1()
{
    char *trail = "";
    Message messages[] = {};
    GameView gv = GvNew(trail, messages);

    assert(GvGetRound(gv) == 0);

    GvFree(gv);
    printf("Test passed!\n");
}

/**
 * 
 */
static void testGvGetRound2()
{
}