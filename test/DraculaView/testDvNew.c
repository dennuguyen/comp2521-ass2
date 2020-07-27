#include "testDraculaView.h"

static void testDvNew1();
static void testDvNew2();

void testDvNew()
{
    testDvNew1();
    testDvNew2();
}

/**
 * Test initialisation on empty string
 */
static void testDvNew1()
{
    char *trail = "";
    Message messages[] = {};
    DraculaView dv = DvNew(trail, messages);

    assert(DvGetRound(dv) == 0);
    assert(DvGetPlayer(dv) == PLAYER_LORD_GODALMING);
    assert(DvGetScore(dv) == GAME_START_SCORE);
    assert(DvGetHealth(dv, PLAYER_LORD_GODALMING) == GAME_START_HUNTER_LIFE_POINTS);
    assert(DvGetHealth(dv, PLAYER_DRACULA) == GAME_START_BLOOD_POINTS);
    assert(DvGetPlayerLocation(dv, PLAYER_LORD_GODALMING) == NOWHERE);
    // assert(DvGetVampireLocation(dv) == NOWHERE);

    printf("\tTest passed!\n");
}

/**
 * Test initialisation on empty string
 */
static void testDvNew2()
{
}