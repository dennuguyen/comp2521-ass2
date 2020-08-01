#include "testDraculaView.h"

static void testDvNew1();

void testDvNew()
{
    printf("Testing DvNew...\n");

    testDvNew1();

    printf("DvNew tests passed!\n");
}

/**
 * Test empty string
 */
static void testDvNew1()
{
    char *trail = "";
    Message messages[] = {};
    DraculaView dv = DvNew(trail, messages);

    assert(DvGetRound(dv) == 0);
    assert(DvGetScore(dv) == GAME_START_SCORE);
    assert(DvGetHealth(dv, PLAYER_LORD_GODALMING) == GAME_START_HUNTER_LIFE_POINTS);
    assert(DvGetHealth(dv, PLAYER_DRACULA) == GAME_START_BLOOD_POINTS);
    assert(DvGetPlayerLocation(dv, PLAYER_LORD_GODALMING) == NOWHERE);
    assert(DvGetVampireLocation(dv) == NOWHERE);

    DvFree(dv);
    printf("\tTest passed!\n");
}
