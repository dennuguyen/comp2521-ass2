#include "testHunterView.h"

static void testHvNew1();

void testHvNew()
{
    printf("Testing HvNew...\n");

    testHvNew1();

    printf("HvNew tests passed!\n");
}

/**
 * Test empty string
 */
static void testHvNew1()
{
    char *trail = "";
    Message messages[] = {};
    HunterView hv = HvNew(trail, messages);

    assert(HvGetRound(hv) == 0);
    assert(HvGetPlayer(hv) == PLAYER_LORD_GODALMING);
    assert(HvGetScore(hv) == GAME_START_SCORE);
    assert(HvGetHealth(hv, PLAYER_LORD_GODALMING) == GAME_START_HUNTER_LIFE_POINTS);
    assert(HvGetHealth(hv, PLAYER_DRACULA) == GAME_START_BLOOD_POINTS);
    assert(HvGetPlayerLocation(hv, PLAYER_LORD_GODALMING) == NOWHERE);
    assert(HvGetVampireLocation(hv) == NOWHERE);

    HvFree(hv);
    printf("\tTest passed!\n");
}
