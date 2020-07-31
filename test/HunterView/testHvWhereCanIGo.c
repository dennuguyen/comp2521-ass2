#include "testHunterView.h"

static void testHvWhereCanIGo1();
static void testHvWhereCanIGo2();
static void testHvWhereCanIGo3();
static void testHvWhereCanIGo4();
static void testHvWhereCanIGo5();

void testHvWhereCanIGo()
{
    printf("Testing HvGetRound...\n");

    testHvWhereCanIGo1();
    testHvWhereCanIGo2();
    testHvWhereCanIGo3();
    testHvWhereCanIGo4();
    testHvWhereCanIGo5();

    printf("HvGetRound tests passed!\n\n");
}

/**
 * Test initialisation on empty string
 */
static void testHvWhereCanIGo1()
{
    char *trail = "GPA...."; /*  IMPORTANT!!!!    */
    Message messages[] = {"Gone to Barceleno"};
    HunterView hv = HvNew(trail, messages);
    int *numReturnedLocs = -1;
    PlaceId *edges = HvWhereCanIGo(hv, numReturnedLocs);
    int visited[NUM_REAL_PLACES];
    for (int i = 0; i < NUM_REAL_PLACES; i++)
    {
        visited[edges[i]] = 1;
    }
    assert(numReturnedLocs != -1);
    assert(numReturnedLocs == 8);
    assert(visited[PARIS]);
    assert(visited[BRUSSELS]);
    assert(!visited[SARAGOSSA]);

    free(edges);
    HvFree(hv);
    printf("\tTest 1 passed!\n");
}

/**
 * Test in middle of a round
 */
static void testHvWhereCanIGo2()
{
    char *trail = "GGE... SBA...."; /*  IMPORTANT!!!!    */
    Message messages[] = {"Gone to Barceleno"};
    HunterView hv = HvNew(trail, messages);
    int *numReturnedLocs = -1;
    PlaceId *edges = HvWhereCanIGo(hv, numReturnedLocs);
    int visited[NUM_REAL_PLACES];
    for (int i = 0; i < NUM_REAL_PLACES; i++)
    {
        visited[edges[i]] = 1;
    }
    assert(numReturnedLocs != -1);
    assert(numReturnedLocs == 6);
    assert(visited[BARCELONA]);
    assert(visited[MEDITERRANEAN_SEA]);
    assert(visited[SARAGOSSA]);

    free(edges);
    HvFree(hv);
    printf("\tTest 2 passed!\n");
}

/**
 * Test at end of round
 */
static void testHvWhereCanIGo3()
{
    char *trail = "GPA.... SCA .... HGE....";
    Message messages[] = {"Gone to Geneva"};
    HunterView hv = HvNew(trail, messages);
    int *numReturnedLocs = -1;
    PlaceId *edges = HvWhereCanIGo(hv, numReturnedLocs);
    int visited[NUM_REAL_PLACES];
    for (int i = 0; i < NUM_REAL_PLACES; i++)
    {
        visited[edges[i]] = 1;
    }
    assert(numReturnedLocs >= 7);
    assert(visited[GRANADA]);
    assert(visited[LISBON]);
    assert(visited[MADRID]);

    free(edges);
    HvFree(hv);
    printf("\tTest 3 passed!\n");
}

/**
 * Test small number of rounds
 */
static void testHvWhereCanIGo4()
{
    char *trail = "GGA....";
    Message messages[] = {"Gone to Galatz"};
    HunterView hv = HvNew(trail, messages);
    int *numReturnedLocs = -1;
    PlaceId *edges = HvWhereCanIGo(hv, numReturnedLocs);
    int visited[NUM_REAL_PLACES];
    for (int i = 0; i < NUM_REAL_PLACES; i++)
    {
        visited[edges[i]] = 1;
    }
    assert(numReturnedLocs == 5);
    assert(visited[GALATZ]);
    assert(visited[CONSTANTA);

    free(edges);
    HvFree(hv);
    printf("\tTest 4 passed!\n");
}

/**
 * Test large number of rounds
 */
static void testHvWhereCanIGo5()
{
    char *trail = "GSW....";
    
    int *numReturnedLocs = -1;
    PlaceId *edges = HvWhereCanIGo(hv, numReturnedLocs);
    int visited[NUM_REAL_PLACES];
    for (int i = 0; i < NUM_REAL_PLACES; i++)
    {
        visited[edges[i]] = 1;
    }
    assert(numReturnedLocs >= 1);
    assert(visited[SWANSEA]);
    assert(visited[LONDON]);
    assert(visited[LIVERPOOL]);

    free(edges);
    HvFree(hv);
    printf("\tTest 5 passed!\n");
}
