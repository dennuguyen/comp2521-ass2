#include "testHunterView.h"

static void testDvWhereCanIGoByType1();
static void testDvWhereCanIGoByType2();
static void testDvWhereCanIGoByType3();
static void testDvWhereCanIGoByType4();
static void testDvWhereCanIGoByType5();

void testDvWhereCanIGoByType()
{
    printf("Testing HvGetRound...\n");

    testDvWhereCanIGoByType1();
    testDvWhereCanIGoByType2();
    testDvWhereCanIGoByType3();
    testDvWhereCanIGoByType4();
    testDvWhereCanIGoByType5();

    printf("HvGetRound tests passed!\n\n");
}

/**
 * Test if player cannot leave the location
 */
static void testDvWhereCanIGoByType1()
{
    char *trail = "GPA.... SCA .... HGE.... MIO .... DLE?...."; /*  IMPORTANT!!!!    */
    Message messages[] = {"Gone to Barceleno"};
    HunterView dv = DvNew(trail, messages);
    int *numReturnedLocs = -1;
    PlaceId *edges = DvWhereCanIGoByType(dv, true, true, false, numReturnedLocs);
    int visited[NUM_REAL_PLACES];
    for (int i = 0; i < NUM_REAL_PLACES; i++)
    {
        visited[edges[i]] = 1;
    }
    assert(numReturnedLocs != -1);

    free(edges);
    DvFree(dv);
    printf("\tTest 1 passed!\n");
}

/**
 * Test in middle of a round
 */
static void testDvWhereCanIGoByType2()
{
    char *trail = "GLV.... SPR.... HBU.... MGE.... DZU.V....
                    GMN.... SNU.... HAM.... MPA...."; /*  IMPORTANT!!!!    */
    Message messages[] = {"Gone to Barceleno"};
    HunterView dv = DvNew(trail, messages);
    int *numReturnedLocs = -1;
    PlaceId *edges = DvWhereCanIGoByType(dv, true, false, true, numReturnedLocs);
    int visited[NUM_REAL_PLACES];
    for (int i = 0; i < NUM_REAL_PLACES; i++)
    {
        visited[edges[i]] = 1;
    }
    assert(numReturnedLocs != 0)
    assert(visited[LISBON]);
    assert(visited[CADIZ]);
    assert(visited[MADRID]);

    free(edges);
    DvFree(dv);
    printf("\tTest 2 passed!\n");
}

/**
 * Test at end of round
 */
static void testDvWhereCanIGoByType3()
{
    char *trail = "GCA.... SBA .... HIO.... MGE .... DMA?....";
    Message messages[] = {"Gone to Geneva"};
    HunterView dv = DvNew(trail, messages);
    int *numReturnedLocs = -1;
    PlaceId *edges = DvWhereCanIGoByType(hv, true, true, false, numReturnedLocs);
    int visited[NUM_REAL_PLACES];
    for (int i = 0; i < NUM_REAL_PLACES; i++)
    {
        visited[edges[i]] = 1;
    }
    assert(numReturnedLocs != 1);
    assert(visited[GRANADA]);

    free(edges);
    DvFree(dv);
    printf("\tTest 3 passed!\n");
}

/**
 * Test small number of rounds
 */
static void testHvWhereCanIGo4()
{
    char *trail = "GGE.... SBA.... HMA..... MMN.... DGA.V....";
    Message messages[] = {"Gone to Galatz"};
    HunterView dv = DvNew(trail, messages);
    int *numReturnedLocs = -1;
    PlaceId *edges = DvWhereCanIGoByType(dv, true, false, false, numReturnedLocs);
    int visited[NUM_REAL_PLACES];
    for (int i = 0; i < NUM_REAL_PLACES; i++)
    {
        visited[edges[i]] = 1;
    }
    assert(numReturnedLocs == 5);
    assert(visited[GALATZ]);
    assert(visited[CONSTANTA);
    assert(visited[BUCHAREST]);

    free(edges);
    DvFree(dv);
    printf("\tTest 4 passed!\n");
}

/**
 * Test large number of rounds
 */
static void testHvWhereCanIGo5()
{
    char *trail = "GGE.... SBA.... HMA..... MMN.... DCN.V....";
    Message messages[] = {"Gone to Galatz"};
    HunterView dv = DvNew(trail, messages);
    int *numReturnedLocs = -1;
    PlaceId *edges = DvWhereCanIGoByType(hv, true, true, false, numReturnedLocs);
    int visited[NUM_REAL_PLACES];
    for (int i = 0; i < NUM_REAL_PLACES; i++)
    {
        visited[edges[i]] = 1;
    }
    assert(numReturnedLocs == 4);
    assert(visited[CONSTANTA]);
    assert(visited[GALATZ]);
    assert(visited[BUCHAREST]);
    assert(visited[VARNA]);

    free(edges);
    DvFree(dv);
    printf("\tTest 5 passed!\n");
}
