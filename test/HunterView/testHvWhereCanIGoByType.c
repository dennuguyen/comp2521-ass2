#include "testHunterView.h"

static void testHvWhereCanIGoByType1();
static void testHvWhereCanIGoByType2();
static void testHvWhereCanIGoByType3();
static void testHvWhereCanIGoByType4();
static void testHvWhereCanIGoByType5();

void testHvWhereCanIGoByType()
{
    printf("Testing HvGetRound...\n");

    testHvWhereCanIGoByType1();
    testHvWhereCanIGoByType2();
    testHvWhereCanIGoByType3();
    testHvWhereCanIGoByType4();
    testHvWhereCanIGoByType5();

    printf("HvGetRound tests passed!\n\n");
}

/**
 * Test if player cannot leave the location
 */
static void testHvWhereCanIGoByType1()
{
    char *trail = "GPA...."; /*  IMPORTANT!!!!    */
    Message messages[] = {"Gone to Barceleno"};
    HunterView hv = HvNew(trail, messages);
    int *numReturnedLocs = -1;
    PlaceId *edges = HvWhereCanIGoByType(hv, false, false, false, numReturnedLocs);
    int visited[NUM_REAL_PLACES];
    for (int i = 0; i < NUM_REAL_PLACES; i++)
    {
        visited[edges[i]] = 1;
    }
    assert(numReturnedLocs != -1);

    free(edges);
    HvFree(hv);
    printf("\tTest 1 passed!\n");
}

/**
 * Test in middle of a round
 */
static void testHvWhereCanIGoByType2()
{
    char *trail = "GGO.... SIO.... HLS...."; /*  IMPORTANT!!!!    */
    Message messages[] = {"Gone to Barceleno"};
    HunterView hv = HvNew(trail, messages);
    int *numReturnedLocs = -1;
    PlaceId *edges = HvWhereCanIGo(hv, true, false, false, numReturnedLocs);
    int visited[NUM_REAL_PLACES];
    for (int i = 0; i < NUM_REAL_PLACES; i++)
    {
        visited[edges[i]] = 1;
    }
    assert(numReturnedLocs == 3)
    assert(visited[LISBON]);
    assert(visited[CADIZ]);
    assert(visited[MADRID]);

    free(edges);
    HvFree(hv);
    printf("\tTest 2 passed!\n");
}

/**
 * Test at end of round
 */
static void testHvWhereCanIGoByType3()
{
    char *trail = "GGE....";
    Message messages[] = {"Gone to Geneva"};
    HunterView hv = HvNew(trail, messages);
    int *numReturnedLocs = -1;
    PlaceId *edges = HvWhereCanIGo(hv, false, true, true, numReturnedLocs);
    int visited[NUM_REAL_PLACES];
    for (int i = 0; i < NUM_REAL_PLACES; i++)
    {
        visited[edges[i]] = 1;
    }
    assert(numReturnedLocs != -1);
    assert(visited[MILAN]);

    free(edges);
    HvFree(hv);
    printf("\tTest 3 passed!\n");
}

/**
 * Test small number of rounds
 */
static void testHvWhereCanIGoByType4()
{
    char *trail = "GGA....";
    Message messages[] = {"Gone to Galatz"};
    HunterView hv = HvNew(trail, messages);
    int *numReturnedLocs = -1;
    PlaceId *edges = HvWhereCanIGo(hv, true, false, false, numReturnedLocs);
    int visited[NUM_REAL_PLACES];
    for (int i = 0; i < NUM_REAL_PLACES; i++)
    {
        visited[edges[i]] = 1;
    }
    asser(numReturnedLocs == 5);
    assert(visited[GALATZ]);
    assert(visited[CONSTANTA);

    free(edges);
    HvFree(hv);
    printf("\tTest 4 passed!\n");
}

/**
 * Test large number of rounds
 */
static void testHvWhereCanIGoByType5()
{
    char *trail = "GSW.... SMU....";
    
    int *numReturnedLocs = -1;
    PlaceId *edges = HvWhereCanIGo(hv, true, true, true, numReturnedLocs);
    int visited[NUM_REAL_PLACES];
    for (int i = 0; i < NUM_REAL_PLACES; i++)
    {
        visited[edges[i]] = 1;
    }
    assert(numReturnedLocs != -1);
    assert(visited[MUNICH]);
    assert(visited[VIENNA]);
    assert(visited[NUREMBURG]);

    free(edges);
    HvFree(hv);
    printf("\tTest 5 passed!\n");
}
