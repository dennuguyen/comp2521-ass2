#include "testHunterView.h"

static void testHvWhereCanTheyGo1();
static void testHvWhereCanTheyGo2();
static void testHvWhereCanTheyGo3();
static void testHvWhereCanTheyGo4();
static void testHvWhereCanTheyGo5();

void testHvWhereCanTheyGo()
{
    printf("Testing HvGetRound...\n");

    testHvWhereCanTheyGo1();
    testHvWhereCanTheyGo2();
    testHvWhereCanTheyGo3();
    testHvWhereCanTheyGo4();
    testHvWhereCanTheyGo5();

    printf("HvGetRound tests passed!\n\n");
}

/**
 * Test if string will not be empty
 */
static void testHvWhereCanTheyGo1()
{
    char *trail = "GGE.... SGE.... HGE.... MGE...."; /*  IMPORTANT!!!!    */
    Message messages[] = {"I DO NOT KNOW WHAT TO TYPE IN HERE!"};
    HunterView hv = HvNew(trail, messages);
    int *numReturnedLocs = -1;
    PlaerId player = HvGetPlayer(hv);
    PlaceId *edges = HvWhereCanTheyGo(hv, PLAYER_MINA_HARKER, numReturnedLocs);
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
static void testHvWhereCanTheyGo2()
{
    char *trail = "GBA...."; /*  IMPORTANT!!!!    */
    Message messages[] = {"Gone to Barceleno"};
    HunterView hv = HvNew(trail, messages);
    int *numReturnedLocs = -1;
    PlaerId player = HvGetPlayer(hv);
    PlaceId *edges = HvWhereCanTheyGo(hv, PLAYER_LORD_GODALMING, numReturnedLocs);
    int visited[NUM_REAL_PLACES];
    for (int i = 0; i < NUM_REAL_PLACES; i++)
    {
        visited[edges[i]] = 1;
    }
    assert(numReturnedLocs != -1); 
    assert(visited[SARAGOSSA]);

    free(edges);
    HvFree(hv);
    printf("\tTest 2 passed!\n");
}

/**
 * Test at end of round
 */
static void testHvWhereCanTheyGo3()
{
    char *trail = "GGE.... SBA.... HGE....";
    Message messages[] = {"Gone to Geneva"};
    HunterView hv = HvNew(trail, messages);
    int *numReturnedLocs = -1;
    PlaerId player = HvGetPlayer(hv);
    PlaceId *edges = HvWhereCanTheyGo(hv, PLAYER_VAN_HELSING, numReturnedLocs);
    int visited[NUM_REAL_PLACES];
    for (int i = 0; i < NUM_REAL_PLACES; i++)
    {
        visited[edges[i]] = 1;
    }
    assert(visited[GENEVA]);
    assert(visited[ZURICH);
    assert(visited[MILAN]);
    assert(visited[PARIS]);

    free(edges);
    HvFree(hv);
    printf("\tTest 3 passed!\n");
}

/**
 * Test small number of rounds
 */
static void testHvWhereCanTheyGo4()
{
    char *trail = "GGA.... SBA.... HIO.... MGA....";
    Message messages[] = {"Gone to Galatz"};
    HunterView hv = HvNew(trail, messages);
    int *numReturnedLocs = -1
    PlaceId *edges = HvWhereCanTheyGo(hv, PLAYER_MINA_HARKER, numReturnedLocs);
    int visited[NUM_REAL_PLACES];
    for (int i = 0; i < NUM_REAL_PLACES; i++)
    {
        visited[edges[i]] = 1;
    }
    assert(visited[GALATZ]);
    assert(visited[CONSTANTA);

    free(edges);
    HvFree(hv);
    printf("\tTest 4 passed!\n");
}

/**
 * Test large number of rounds
 */
static void testHvWhereCanTheyGo5()
{
    char *trail = "GSW....";
    
    int *numReturnedLocs = -1
    PlaceId *edges = HvWhereCanIGo(hv, PLAYER_LORD_GODALMING, numReturnedLocs);
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
