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
 * Test if player cannot leave the location
 */
static void testHvGetShortestPathTo1()
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
    assert(numReturnedLocs == 1);
    asser(visited[BARCELONA]);

    free(edges);
    HvFree(hv);
    printf("\tTest 1 passed!\n");
}

/**
 * Test for Van Helsing at Lisbon in Round 1.
 */
static void testHvGetShortestPathTo2()
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
    assert(numReturnedLocs == 4);
    assert(visited[LISBON]);
    assert(visited[CADIZ]);
    assert(visited[MADRID]);
    asser(visisted[SANTANDER]);

    free(edges);
    HvFree(hv);
    printf("\tTest 2 passed!\n");
}

/**
 * Testing for Lord Godaling at Geneva in Round 2.
 */
static void testHvGetShortestPathTo3()
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
    assert(numReturnedLocs >= 0);
    assert(visited[GENEVA]);

    free(edges);
    HvFree(hv);
    printf("\tTest 3 passed!\n");
}

/**
 * Testing for Lord Godaling at Galway in Round 1.
 */
static void testHvGetShortestPathTo4()
{
    char *trail = "GGW.... ";
    Message messages[] = {"Gone to Galway"};
    HunterView hv = HvNew(trail, messages);
    int *numReturnedLocs = -1;
    PlaceId *edges = HvWhereCanIGo(hv, true, true, false, numReturnedLocs);
    int visited[NUM_REAL_PLACES];
    for (int i = 0; i < NUM_REAL_PLACES; i++)
    {
        visited[edges[i]] = 1;
    }
    asser(numReturnedLocs == 2);
    assert(visited[GALWAY]);
    assert(visited[DUBLIN]);

    free(edges);
    HvFree(hv);
    printf("\tTest 4 passed!\n");
}

/**
 * Testing for Dr. Seward at Munich in Round 1.
 */
static void testHvGetShortestPathTo5()
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
    assert(numReturnedLocs == 8);
    assert(visited[MUNICH]);
    assert(visited[VIENNA]);
    assert(visited[NUREMBURG]);
    assert(visited[VENICE]);
    assert(visited[MILAN]);
    assert(visited[ZAGREB]);

    free(edges);
    HvFree(hv);
    printf("\tTest 5 passed!\n");
}