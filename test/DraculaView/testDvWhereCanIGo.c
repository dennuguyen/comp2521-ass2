#include "testHunterView.h"

static void testDvWhereCanIGo1();
static void testDvWhereCanIGo2();
static void testDvWhereCanIGo3();
static void testDvWhereCanIGo4();
static void testDvWhereCanIGo5();

void testDvWhereCanIGo()
{
    printf("Testing HvGetRound...\n");

    testDvWhereCanIGo1();
    testDvWhereCanIGo2();
    testDvWhereCanIGo3();
    testDvWhereCanIGo4();
    testDvWhereCanIGo5();

    printf("HvGetRound tests passed!\n\n");
}

/**
 * Testing for Dracula at Le-Havre in Round 1
 */
static void testDvWhereCanIGo1()
{
    char *trail = "GPA.... SCA .... HGE.... MIO .... DLE?...."; /*  IMPORTANT!!!!    */
    Message messages[] = {"Gone to Barceleno"};
    HunterView dv = HvNew(trail, messages);
    int *numReturnedLocs = -1;
    PlaceId *edges = DvWhereCanIGo(dv, numReturnedLocs);
    int visited[NUM_REAL_PLACES];
    for (int i = 0; i < NUM_REAL_PLACES; i++)
    {
        visited[edges[i]] = 1;
    }
    assert(numReturnedLocs != -1);
    assert()
    assert(visited[NANTES]);
    assert(visited[BRUSSELS]);
    assert(!visited[PARIS]);

    free(edges);
    DvFree(dv);
    printf("\tTest 1 passed!\n");
}

/**
 * Testing for Dracula at Munich in Round 2.
 */
static void testDvWhereCanIGo2()
{
    char *trail = "GMN.... SNU.... HAM.... MPA.... DZU.V....
                    GLV.... SPR.... HBU.... MGE.... DMU?...."; /*  IMPORTANT!!!!    */
    Message messages[] = {"Gone to Barceleno"};
    HunterView dv = HvNew(trail, messages);
    int *numReturnedLocs = -1;
    PlaceId *edges = DvWhereCanIGo(dv, numReturnedLocs);
    int visited[NUM_REAL_PLACES];
    for (int i = 0; i < NUM_REAL_PLACES; i++)
    {
        visited[edges[i]] = 1;
    }
    assert(numReturnedLocs != -1);
    assert(numReturnedLocs >= 3);
    assert(visited[ZURICH]);
    assert(visited[MUNICH]);
    assert(!visited[GENEVA]);

    free(edges);
    DvFree(dv);
    printf("\tTest 2 passed!\n");
}

/**
 * Testing for Dracula at Manchester in Round 1
 */
static void testDvWhereCanIGo3()
{
    char *trail = "GCA.... SBA .... HIO.... MGE .... DMA?...."; /*  IMPORTANT!!!!    */
    Message messages[] = {"Gone to Barceleno"};
    HunterView dv = HvNew(trail, messages);
    int *numReturnedLocs = -1;
    PlaceId *edges = DvWhereCanIGo(dv, numReturnedLocs);
    int visited[NUM_REAL_PLACES];
    for (int i = 0; i < NUM_REAL_PLACES; i++)
    {
        visited[edges[i]] = 1;
    }
    assert(numReturnedLocs == 7);
    assert(visited[LISBON]);
    assert(visited[MADRID]);
    assert(!visited[GRANADA]);

    free(edges);
    DvFree(dv);
    printf("\tTest 2 passed!\n");
}

/**
 * Testing for Dracula at Constanta in Round 1
 */
static void testDvWhereCanIGo4()
{
    char *trail = "GGA.... SBA .... HIO.... MGE .... DCN?....";
    Message messages[] = {"Gone to Galatz"};
    HunterView dv = DvNew(trail, messages);
    int *numReturnedLocs = -1;
    PlaceId *edges = DvWhereCanIGo(dv, numReturnedLocs);
    int visited[NUM_REAL_PLACES];
    for (int i = 0; i < NUM_REAL_PLACES; i++)
    {
        visited[edges[i]] = 1;
    }
    assert(numReturnedLocs == 4);
    assert(visited[GALATZ]);
    assert(visited[CONSTANTA);
    assert(visited[VARNA]);
    assert(visited[BUCHAREST]);
    assert(visited[BLACK_SEA]);

    free(edges);
    DvFree(dv);
    printf("\tTest 4 passed!\n");
}

/**
 * Testsing for Dracula at Varna in Round 2
 */
static void testDvWhereCanIGo5()
{
    char *trail = "GSW.... SBA .... HMA.... MGE .... DCN?....
                    GGA.... SBA .... HIO.... MGE .... DVR.V....";
    int *numReturnedLocs = -1;
    PlaceId *edges = DvWhereCanIGo(dv, numReturnedLocs);
    int visited[NUM_REAL_PLACES];
    for (int i = 0; i < NUM_REAL_PLACES; i++)
    {
        visited[edges[i]] = 1;
    }
    assert(numReturnedLocs == 3);
    assert(visited[CONSTANTA]);
    assert(visited[VARNA]);
    assert(visited[SOFIA]);

    free(edges);
    DvFree(dv);
    printf("\tTest 5 passed!\n");
}
