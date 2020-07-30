#include "testHunterView.h"

static void testHvGetShortestPathTo1();
static void testHvGetShortestPathTo2();
static void testHvGetShortestPathTo3();
static void testHvGetShortestPathTo4();
static void testHvGetShortestPathTo5();

void testHvGetShortestPathTo()
{
    printf("Testing HvGetRound...\n");

    testHvGetShortestPathTo1();
    testHvGetShortestPathTo2();
    testHvGetShortestPathTo3();
    testHvGetShortestPathTo4();
    testHvGetShortestPathTo5();

    printf("HvGetRound tests passed!\n\n");
}

/**
 * Test initialisation on empty string
 */
static void testHvGetShortestPathTo1()
{
    char *trail = "";
    Message messages[] = {};
    HunterView hv = HvNew(trail, messages);
    int *pathlength;
    PlaceId dest;

    pathlength = -1;
    dest = HvGetPlayerLocation(hv, PLAYER_LORD_GODALMING);
    PlaceId *path = HvGetShortestPathTo(hv, PLAYER_LORD_GODALMING, dest, pathlength))
    assert(pathlength == 0);

    pathlength = -1;
    dest = HvGetPlayerLocation(hv, PLAYER_DR_SEWARD);
    PlaceId *path = HvGetShortestPathTo(hv, PLAYER_DR_SEWARD, dest, pathlength))
    assert(pathlength == 0);

    pathlength = -1;
    dest = HvGetPlayerLocation(hv, PLAYER_VAN_HELSING);
    PlaceId *path = HvGetShortestPathTo(hv, PLAYER_VAN_HELSING, dest, pathlength))
    assert(pathlength == 0);

    pathlength = -1;
    dest = HvGetPlayerLocation(hv, PLAYER_MINA_HARKER);
    PlaceId *path = HvGetShortestPathTo(hv, PLAYER_MINA_HARKER, dest, pathlength))
    assert(pathlength == 0);

    pathlength = -1;
    dest = HvGetPlayerLocation(hv, PLAYER_DRACULA);
    PlaceId *path = HvGetShortestPathTo(hv, PLAYER_DRACULA, dest, pathlength))
    assert(pathlength == 0);

    HvFree(hv);
    printf("\tTest 1 passed!\n");
}

/**
 * Test in middle of a round
 */
static void testHvGetShortestPathTo2()
{
    char *trail = "";
    Message messages[] = {};
    HunterView hv = HvNew(trail, messages);
    int *pathlength;
    PlaceId dest;

    pathlength = -1;
    dest = HvGetPlayerLocation(hv, PLAYER_LORD_GODALMING);
    PlaceId *path = HvGetShortestPathTo(hv, PLAYER_LORD_GODALMING, dest, pathlength))
    assert(pathlength == 0);

    pathlength = -1;
    dest = HvGetPlayerLocation(hv, PLAYER_DR_SEWARD);
    PlaceId *path = HvGetShortestPathTo(hv, PLAYER_DR_SEWARD, dest, pathlength))
    assert(pathlength == 0);

    pathlength = -1;
    dest = HvGetPlayerLocation(hv, PLAYER_VAN_HELSING);
    PlaceId *path = HvGetShortestPathTo(hv, PLAYER_VAN_HELSING, dest, pathlength))
    assert(pathlength == 0);

    pathlength = -1;
    dest = HvGetPlayerLocation(hv, PLAYER_MINA_HARKER);
    PlaceId *path = HvGetShortestPathTo(hv, PLAYER_MINA_HARKER, dest, pathlength))
    assert(pathlength == 0);

    pathlength = -1;
    dest = HvGetPlayerLocation(hv, PLAYER_DRACULA);
    PlaceId *path = HvGetShortestPathTo(hv, PLAYER_DRACULA, dest, pathlength))
    assert(pathlength == 0);

    HvFree(hv);
    printf("\tTest 2 passed!\n");
}

    /**
 * Test initialisation on empty string
 */
static void testHvGetShortestPathTo3()
{
    char *trail = "";
    Message messages[] = {};
    HunterView hv = HvNew(trail, messages);
    int *pathlength;
    PlaceId dest;

    pathlength = -1;
    dest = HvGetPlayerLocation(hv, PLAYER_LORD_GODALMING);
    PlaceId *path = HvGetShortestPathTo(hv, PLAYER_LORD_GODALMING, dest, pathlength))
    assert(pathlength == 0);

    pathlength = -1;
    dest = HvGetPlayerLocation(hv, PLAYER_DR_SEWARD);
    PlaceId *path = HvGetShortestPathTo(hv, PLAYER_DR_SEWARD, dest, pathlength))
    assert(pathlength == 0);

    pathlength = -1;
    dest = HvGetPlayerLocation(hv, PLAYER_VAN_HELSING);
    PlaceId *path = HvGetShortestPathTo(hv, PLAYER_VAN_HELSING, dest, pathlength))
    assert(pathlength == 0);

    pathlength = -1;
    dest = HvGetPlayerLocation(hv, PLAYER_MINA_HARKER);
    PlaceId *path = HvGetShortestPathTo(hv, PLAYER_MINA_HARKER, dest, pathlength))
    assert(pathlength == 0);

    pathlength = -1;
    dest = HvGetPlayerLocation(hv, PLAYER_DRACULA);
    PlaceId *path = HvGetShortestPathTo(hv, PLAYER_DRACULA, dest, pathlength))
    assert(pathlength == 0);

    HvFree(hv);
    printf("\tTest 3 passed!\n");
}

/**
 * Test at end of round
 */
static void testHvGetShortestPathTo4()
{
    char *trail = "";
    Message messages[] = {};
    HunterView hv = HvNew(trail, messages);
    int *pathlength;
    PlaceId dest;

    pathlength = -1;
    dest = HvGetPlayerLocation(hv, PLAYER_LORD_GODALMING);
    PlaceId *path = HvGetShortestPathTo(hv, PLAYER_LORD_GODALMING, dest, pathlength))
    assert(pathlength == 0);

    pathlength = -1;
    dest = HvGetPlayerLocation(hv, PLAYER_DR_SEWARD);
    PlaceId *path = HvGetShortestPathTo(hv, PLAYER_DR_SEWARD, dest, pathlength))
    assert(pathlength == 0);

    pathlength = -1;
    dest = HvGetPlayerLocation(hv, PLAYER_VAN_HELSING);
    PlaceId *path = HvGetShortestPathTo(hv, PLAYER_VAN_HELSING, dest, pathlength))
    assert(pathlength == 0);

    pathlength = -1;
    dest = HvGetPlayerLocation(hv, PLAYER_MINA_HARKER);
    PlaceId *path = HvGetShortestPathTo(hv, PLAYER_MINA_HARKER, dest, pathlength))
    assert(pathlength == 0);

    pathlength = -1;
    dest = HvGetPlayerLocation(hv, PLAYER_DRACULA);
    PlaceId *path = HvGetShortestPathTo(hv, PLAYER_DRACULA, dest, pathlength))
    assert(pathlength == 0);

    HvFree(hv);
    printf("\tTest 4 passed!\n");
}

/**
 * Test small number of rounds
 */
static void testHvGetShortestPathTo5()
{
    char *trail = "";
    Message messages[] = {};
    HunterView hv = HvNew(trail, messages);
    int *pathlength;
    PlaceId dest;

    pathlength = -1;
    dest = HvGetPlayerLocation(hv, PLAYER_LORD_GODALMING);
    PlaceId *path = HvGetShortestPathTo(hv, PLAYER_LORD_GODALMING, dest, pathlength))
    assert(pathlength == 0);

    pathlength = -1;
    dest = HvGetPlayerLocation(hv, PLAYER_DR_SEWARD);
    PlaceId *path = HvGetShortestPathTo(hv, PLAYER_DR_SEWARD, dest, pathlength))
    assert(pathlength == 0);

    pathlength = -1;
    dest = HvGetPlayerLocation(hv, PLAYER_VAN_HELSING);
    PlaceId *path = HvGetShortestPathTo(hv, PLAYER_VAN_HELSING, dest, pathlength))
    assert(pathlength == 0);

    pathlength = -1;
    dest = HvGetPlayerLocation(hv, PLAYER_MINA_HARKER);
    PlaceId *path = HvGetShortestPathTo(hv, PLAYER_MINA_HARKER, dest, pathlength))
    assert(pathlength == 0);

    pathlength = -1;
    dest = HvGetPlayerLocation(hv, PLAYER_DRACULA);
    PlaceId *path = HvGetShortestPathTo(hv, PLAYER_DRACULA, dest, pathlength))
    assert(pathlength == 0);

    HvFree(hv);
    printf("\tTest 5 passed!\n");
}