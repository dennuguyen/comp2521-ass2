#include "testHunterView.h"

static void testHvWhereCanTheyGoByType1();
static void testHvWhereCanTheyGoByType2();
static void testHvWhereCanTheyGoByType3();
static void testHvWhereCanTheyGoByType4();
static void testHvWhereCanTheyGoByType5();

void testHvWhereCanTheyGoByType()
{
    printf("Testing HvGetRound...\n");

    testHvWhereCanTheyGoByType1();
    testHvWhereCanTheyGoByType2();
    testHvWhereCanTheyGoByType3();
    testHvWhereCanTheyGoByType4();
    testHvWhereCanTheyGoByType5();

    printf("HvGetRound tests passed!\n\n");
}

/**
 * Test if string will not be empty
 */
static void testHvWhereCanTheyGoByType1()
{
    char *trail = "GGE.... SGE.... HGE.... MGE...."; /*  IMPORTANT!!!!    */
    Message messages[] = {"I DO NOT KNOW WHAT TO TYPE IN HERE!"};
    HunterView hv = HvNew(trail, messages);
    int *numReturnedLocs = -1;
    PlaerId player = HvGetPlayer(hv);
    PlaceId *edges = HvWhereCanTheyGoByType(hv, PLAYER_MINA_HARKER, true, true, true, numReturnedLocs);
    int visited[NUM_REAL_PLACES];
    for (int i = 0; i < NUM_REAL_PLACES; i++)
    {
        visited[edges[i]] = 1;
    }
    assert(numReturnedLocs != -1);
    asser(visited[MILAN] != 1);

    free(edges);
    HvFree(hv);
    printf("\tTest 1 passed!\n");
}

/**
 * Test in middle of a round
 */
static void testHvWhereCanTheyGoByType2()
{
    char *trail = "GBA...."; /*  IMPORTANT!!!!    */
    Message messages[] = {"Gone to Barceleno"};
    HunterView hv = HvNew(trail, messages);
    int *numReturnedLocs = -1;
    PlaerId player = HvGetPlayer(hv);
    PlaceId *edges = HvWhereCanTheyGo(hv, PLAYER_LORD_GODALMING, false, false, true, numReturnedLocs);
    int visited[NUM_REAL_PLACES];
    for (int i = 0; i < NUM_REAL_PLACES; i++)
    {
        visited[edges[i]] = 1;
    }
    assert(numReturnedLocs == 2); 
    assert(visited[MEDITERRANEAN_SEA]);
    assert(visited[BARCELONA]);

    free(edges);
    HvFree(hv);
    printf("\tTest 2 passed!\n");
}

/**
 * Test at end of round
 */
static void testHvWhereCanTheyGoByType3()
{
    char *trail = "GGE.... SBA.... HGE....";
    Message messages[] = {"Gone to Geneva"};
    HunterView hv = HvNew(trail, messages);
    int *numReturnedLocs = -1;
    PlaerId player = HvGetPlayer(hv);
    PlaceId *edges = HvWhereCanTheyGoByType(hv, PLAYER_VAN_HELSING, true, false, true, numReturnedLocs);
    int visited[NUM_REAL_PLACES];
    for (int i = 0; i < NUM_REAL_PLACES; i++)
    {
        visited[edges[i]] = 1;
    }
    assert(visited[GENEVA]);
    assert(visited[ZURICH]);
    assert(visited[MARSEILLES]);
    assert(visited[PARIS]);

    free(edges);
    HvFree(hv);
    printf("\tTest 3 passed!\n");
}

/**
 * Test small number of rounds
 */
static void testHvWhereCanTheyGoByType4()
{
    char *trail = "GGA.... SBA.... HIO.... MGA....";
    Message messages[] = {"Gone to Galatz"};
    HunterView hv = HvNew(trail, messages);
    int *numReturnedLocs = -1;
    PlaceId *edges = HvWhereCanTheyGoByType(hv, PLAYER_VAN_HELSING, false, false, true, numReturnedLocs);
    int visited[NUM_REAL_PLACES];
    for (int i = 0; i < NUM_REAL_PLACES; i++)
    {
        visited[edges[i]] = 1;
    }
    assert(visited[IONIAN_SEA]);
    assert(visited[VALONA]);
    assert(visited[ATHENS]);

    free(edges);
    HvFree(hv);
    printf("\tTest 4 passed!\n");
}

/**
 * Test large number of rounds
 */
static void testHvWhereCanTheyGoByType5()
{
    char *trail = "GSW....";
    Message messages[] = {"Gone to Galatz"};
    HunterView hv = HvNew(trail, messages);
    int *numReturnedLocs = -1;
    PlaceId *edges = HvWhereCanIGoByType(hv, PLAYER_LORD_GODALMING, true, true, true, numReturnedLocs);
    int visited[NUM_REAL_PLACES];
    for (int i = 0; i < NUM_REAL_PLACES; i++)
    {
        visited[edges[i]] = 1;
    }
    assert(numReturnedLocs != 1);
    assert(visited[SWANSEA]);
    assert(visited[LONDON]);
    assert(visited[LIVERPOOL]);

    free(edges);
    HvFree(hv);
    printf("\tTest 5 passed!\n");
}
