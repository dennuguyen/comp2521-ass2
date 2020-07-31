#include "testGameView.h"

static void testGvGetReachableByType1();
static void testGvGetReachableByType2();
static void testGvGetReachableByType3();
static void testGvGetReachableByType4();
static void testGvGetReachableByType5();

void testGvGetReachableByType()
{
    printf("Testing HvGetRound...\n");

    testGvGetReachableByType1();
    testGvGetReachableByType2();
    testGvGetReachableByType3();
    testGvGetReachableByType4();
    testGvGetReachableByType5();

    printf("HvGetRound tests passed!\n\n");
}

/**
 * Testing for Lord Godalming at Paris without restrictions in Round 1.
 */
static void testGvGetReachableByType1()
{
    char *trail = "GPA...."; /*  IMPORTANT!!!!    */
    Message messages[] = {"Gone to Barceleno"};
    GameView gv = GvNew(trail, messages);
    int *numReturnedLocs = -1;
    Round round = GvGetRound(gv);
    PlaceId from = GvGetPlayerLocation(gv, PLAYER_LORD_GODALMING); 
    PlaceId *edges = GvGetReachableByType(hv, PLAYER_LORD_GODALMING, round, from, true, true, true, numReturnedLocs);
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
    GvFree(gv);
    printf("\tTest 1 passed!\n");
}

/**
 * Testing for Dr. Seward at Barcelona without boat in Round 1. 
 */
static void testGvGetReachableByType2()
{
    char *trail = "GGE... SBA...."; /*  IMPORTANT!!!!    */
    Message messages[] = {"Gone to Barceleno"};
    GameView gv = GvNew(trail, messages);
    int *numReturnedLocs = -1;
    Round round = GvGetRound(gv);
    PlaceId from = GvGetPlayerLocation(gv, PLAYER_DR_SEWARD);
    PlaceId *edges = GvGetReachableByType(hv, PLAYER_LORD_GODALMING, round, from, true, true, false, numReturnedLocs);
    int visited[NUM_REAL_PLACES];
    for (int i = 0; i < NUM_REAL_PLACES; i++)
    {
        visited[edges[i]] = 1;
    }
    assert(numReturnedLocs != -1);
    assert(numReturnedLocs == 4);
    assert(visited[BARCELONA]);
    assert(visited[SARAGOSSA]);

    free(edges);
    GvFree(gv);
    printf("\tTest 2 passed!\n");
}

/**
 * Testing for Van Helsing at Geneva in Round 1.
 */
static void testGvGetReachableByType3()
{
    char *trail = "GPA.... SCA .... HCA....";
    Message messages[] = {"Gone to Geneva"};
    GameView gv = GvNew(trail, messages);
    int *numReturnedLocs = -1;
    Round round = GvGetRound(gv);
    PlaceId from = GvGetPlayerLocation(gv, PLAYER_VAN_HELSING);
    PlaceId *edges = GvGetReachableByType(gv, PLAYER_VAN_HELSING, round, from, false, false, false numReturnedLocs);
    int visited[NUM_REAL_PLACES];
    for (int i = 0; i < NUM_REAL_PLACES; i++)
    {
        visited[edges[i]] = 1;
    }
    assert(numReturnedLocs == 1);
    assert(visited[CADIZ]);

    free(edges);
    GvFree(gv);
    printf("\tTest 3 passed!\n");
}

/**
 * Testing for Lord Godaling at Galatz in Round 1
 */
static void testGvGetReachable4()
{
    char *trail = "GGA....";
    Message messages[] = {"Gone to Galatz"};
    GameView gv = GvNew(trail, messages);
    int *numReturnedLocs = -1;
    Round round = GvGetRound(gv);
    PlaceId from = GvGetPlayerLocation(gv, PLAYER_LORD_GODALMING);
    PlaceId *edges = GvGetReachable(gv, PLAYER_LORD_GODALMING, round, from, numReturnedLocs);
    int visited[NUM_REAL_PLACES];
    for (int i = 0; i < NUM_REAL_PLACES; i++)
    {
        visited[edges[i]] = 1;
    }
    assert(numReturnedLocs == 5);
    assert(visited[GALATZ]);
    assert(visited[CONSTANTA);

    free(edges);
    GvFree(gv);
    printf("\tTest 4 passed!\n");
}

/**
 * Testing for Lord Godaling at Berlin in Round 2.
 */
static void testGvGetReachableByType5()
{
    char *trail = "GHA.... SGE.... HSW.... MIO.... DGA.V..
                    GBR....";
    Message messages[] = {"Gone to Berlin"};
    GameView gv = GvNew(trail, messages);
    int *numReturnedLocs = -1;
    Round round = GvGetRound(gv);
    PlaceId from = GvGetPlayerLocation(gv, PLAYER_LORD_GODALMING);
    PlaceId *edges = GvGetReachableByType(gv, PLAYER_LORD_GODALMING, round, from, false, false, true, numReturnedLocs);
    int *numReturnedLocs = -1;
    PlaceId *edges = GvGetReachable(hv, numReturnedLocs);
    int visited[NUM_REAL_PLACES];
    for (int i = 0; i < NUM_REAL_PLACES; i++)
    {
        visited[edges[i]] = 1;
    }
    assert(numReturnedLocs == 1);
    assert(visited[BERLIN]);

    free(edges);
    HvFree(hv);
    printf("\tTest 5 passed!\n");
}
