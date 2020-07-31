#include "testHunterView.h"

static void testDvWhereCanTheyGo1();
static void testDvWhereCanTheyGo2();
static void testDvWhereCanTheyGo3();
static void testDvWhereCanTheyGo4();
static void testDvWhereCanTheyGo5();

void testDvWhereCanTheyGo()
{
    printf("Testing HvGetRound...\n");

    testDvWhereCanTheyGo1();
    testDvWhereCanTheyGo2();
    testDvWhereCanTheyGo3();
    testDvWhereCanTheyGo4();
    testDvWhereCanTheyGo5();

    printf("HvGetRound tests passed!\n\n");
}

/**
 * Test initialisation on empty string
 */
static void testDvWhereCanTheyGo1()
{
    char *trail = "GPA.... SCA.... HBU.... MIO.... DLE?...."; /*  IMPORTANT!!!!    */
    Message messages[] = {"Gone to Barceleno"};
    HunterView dv = HvNew(trail, messages);
    int *numReturnedLocs = -1;
    PlaceId *edges = DvWhereCanTheyGo(dv, PLAYER_VAN_HELSING, numReturnedLocs);
    int visited[NUM_REAL_PLACES];
    for (int i = 0; i < NUM_REAL_PLACES; i++)
    {
        visited[edges[i]] = 1;
    }
    assert(numReturnedLocs >= 5)
    assert(visited[LE_HAVRE]);
    assert(visited[BRUSSELS]);
    assert(!visited[PARIS]);

    free(edges);
    DvFree(dv);
    printf("\tTest 1 passed!\n");
}

/**
 * Test in middle of a round
 */
static void testDvWhereCanTheyGo2()
{
    char *trail = "GMN.... SNU.... HAM.... MPA.... DZU.V...."; /*  IMPORTANT!!!!    */
    Message messages[] = {"Gone to Barceleno"};
    HunterView dv = HvNew(trail, messages);
    int *numReturnedLocs = -1;
    PlaceId *edges = DvWhereCanTheyGo(dv, PLAYER_MINA_HARKER, numReturnedLocs);
    int visited[NUM_REAL_PLACES];
    for (int i = 0; i < NUM_REAL_PLACES; i++)
    {
        visited[edges[i]] = 1;
    }
    assert(numReturnedLocs != -1)
    assert(visited[PARIS]);
    assert(visited[CLERMONT_FERRAND]);
    assert(!visited[NANTES]);

    free(edges);
    DvFree(dv);
    printf("\tTest 2 passed!\n");
}

/**
 * Test at end of round
 */
static void testDvWhereCanTheyGo3()
{
    char *trail = "GCA.... SBA.... HIO.... MGE.... DMA?...."; /*  IMPORTANT!!!!    */
    Message messages[] = {"Gone to Barceleno"};
    HunterView dv = HvNew(trail, messages);
    int *numReturnedLocs = -1;
    PlaceId *edges = DvWhereCanTheyGo(dv, PLAYER_LORD_GODALMING, numReturnedLocs);
    int visited[NUM_REAL_PLACES];
    for (int i = 0; i < NUM_REAL_PLACES; i++)
    {
        visited[edges[i]] = 1;
    }
    assert(numReturnedLocs != -1)
    assert(visited[LISBON]);
    assert(visited[MADRID]);
    assert(visited[GRANADA]);
    assert(visited[ALICANTE]);
    assert(visited[CADIZ]);

    free(edges);
    DvFree(dv);
    printf("\tTest 2 passed!\n");
}

/**
 * Test small number of rounds
 */
static void testDvWhereCanTheyGo4()
{
    char *trail = "GTO.... SBA.... HIO.... MGE.... DCN?....";
    Message messages[] = {"Gone to Galatz"};
    HunterView dv = DvNew(trail, messages);
    int *numReturnedLocs = -1;
    PlaceId *edges = DvWhereCanTheyGo(dv, PLAYER_LORD_GODALMING, numReturnedLocs);
    int visited[NUM_REAL_PLACES];
    for (int i = 0; i < NUM_REAL_PLACES; i++)
    {
        visited[edges[i]] = 1;
    }
    assert(numReturnedLocs == 6);
    assert(visited[TOULOUSE]);
    assert(visited[BARCELONA);
    assert(visited[BORDEAUX]);
    assert(visited[MARSEILLES]);
    assert(visited[SARAGOSSA]);
    assert(visited[CLERMONT_FERRAND]);

    free(edges);
    DvFree(dv);
    printf("\tTest 4 passed!\n");
}

/**
 * Test large number of rounds
 */
static void testDvWhereCanTheyGo5()
{
    char *trail = "GSW.... SBA.... HMA.... MGE.... DCN?....
                    GGA.... SBA.... HIO.... MGE.... DVR.V....";
    int *numReturnedLocs = -1;
    PlaceId *edges = DvWhereCanTheyGo(dv, PLAYER_DRACULA, numReturnedLocs);
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
