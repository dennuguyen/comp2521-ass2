#include "testHunterView.h"

static void testDvWhereCanTheyGoByType1();
static void testDvWhereCanTheyGoByType2();
static void testDvWhereCanTheyGoByType3();
static void testDvWhereCanTheyGoByType4();
static void testDvWhereCanTheyGoByType5();

void testDvWhereCanTheyGoByType()
{
    printf("Testing HvGetRound...\n");

    testDvWhereCanTheyGoByType1();
    testDvWhereCanTheyGoByType2();
    testDvWhereCanTheyGoByType3();
    testDvWhereCanTheyGoByType4();
    testDvWhereCanTheyGoByType5();

    printf("HvGetRound tests passed!\n\n");
}

/**
 * Test if player cannot leave the location
 */
static void testDvWhereCanTheyGoByType1()
{
    char *trail = "GPA.... SCA.... HGE.... MIO...."; /*  IMPORTANT!!!!    */
    Message messages[] = {"Gone to Barceleno"};
    HunterView dv = DvNew(trail, messages);
    int *numReturnedLocs = -1;
    PlaceId *edges = DvWhereCanTheyGoByType(dv, PLAYER_DRACULA, true, true, false, numReturnedLocs);
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
static void testDvWhereCanTheyGoByType2()
{
    char *trail = "GLV.... SPR.... HBU.... MGE.... DZU.V....
                    GMN.... SNU.... HAM.... MPA...."; /*  IMPORTANT!!!!    */
    Message messages[] = {"Gone to Barceleno"};
    HunterView dv = DvNew(trail, messages);
    int *numReturnedLocs = -1;
    PlaceId *edges = DvWhereCanTheyGoByType(dv, PLAYER_VAN_HELSING, true, false, true, numReturnedLocs);
    int visited[NUM_REAL_PLACES];
    for (int i = 0; i < NUM_REAL_PLACES; i++)
    {
        visited[edges[i]] = 1;
    }
    assert(numReturnedLocs != 2)
    assert(visited[AMSTERDAM]);
    assert(visited[COLOGNE]);
    assert(visited[BRUSSELS]);

    free(edges);
    DvFree(dv);
    printf("\tTest 2 passed!\n");
}

/**
 * Test at end of round
 */
static void testDvWhereCanTheyGoByType3()
{
    char *trail = "GCA.... SBA.... HIO.... MGE.... DMA?....";
    Message messages[] = {"Gone to Geneva"};
    HunterView dv = DvNew(trail, messages);
    int *numReturnedLocs = -1;
    PlaceId *edges = DvWhereCanTheyGoByType(hv, PLAYER_MINA_HARKER, true, true, false, numReturnedLocs);
    int visited[NUM_REAL_PLACES];
    for (int i = 0; i < NUM_REAL_PLACES; i++)
    {
        visited[edges[i]] = 1;
    }
    assert(numReturnedLocs != 1);
    assert(visited[GENEVA]);
    assert(visited[ZURICH]);
    assert(visited[MILAN]);

    free(edges);
    DvFree(dv);
    printf("\tTest 3 passed!\n");
}

/**
 * Test small number of rounds
 */
static void testDvWhereCanTheyGo4()
{
    char *trail = "GGE.... SBA.... HMA..... MMN.... DGA.V....";
    Message messages[] = {"Gone to Galatz"};
    HunterView dv = DvNew(trail, messages);
    int *numReturnedLocs = -1;
    PlaceId *edges = DvWhereCanTheyGoByType(dv, PLAYER_DRACULA, true, false, false, numReturnedLocs);
    int visited[NUM_REAL_PLACES];
    for (int i = 0; i < NUM_REAL_PLACES; i++)
    {
        visited[edges[i]] = 1;
    }
    assert(numReturnedLocs == 5);
    assert(visited[GALATZ]);
    assert(visited[CONSTANTA);
    assert(visited[BUCHAREST]);
    assert(visited[KLAUSENBURG]);

    free(edges);
    DvFree(dv);
    printf("\tTest 4 passed!\n");
}

/**
 * Test large number of rounds
 */
static void testHvWhereCanTheyGo5()
{
    char *trail = "GGE.... SBA.... HMA..... MMN.... DCN.V....";
    Message messages[] = {"Gone to Galatz"};
    HunterView dv = DvNew(trail, messages);
    int *numReturnedLocs = -1;
    PlaceId *edges = DvWhereCanIGoByType(hv, PLAYER_MINA_HARKER, true, false, true, numReturnedLocs);
    int visited[NUM_REAL_PLACES];
    for (int i = 0; i < NUM_REAL_PLACES; i++)
    {
        visited[edges[i]] = 1;
    }
    assert(numReturnedLocs == 4);
    assert(visited[MANCHESTER]);
    assert(visited[EDINBURGH]);
    assert(visited[LIVERPOOL]);
    assert(visited[LONDON]);

    free(edges);
    DvFree(dv);
    printf("\tTest 5 passed!\n");
}
