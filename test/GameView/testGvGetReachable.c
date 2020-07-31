#include "testGameView.h"

static void testGvGetReachable1();
static void testGvGetReachable2();
static void testGvGetReachable3();
static void testGvGetReachable4();
static void testGvGetReachable5();

void testGvGetReachable()
{
    printf("Testing HvGetRound...\n");

    testGvGetReachable1();
    testGvGetReachable2();
    testGvGetReachable3();
    testGvGetReachable4();
    testGvGetReachable5();

    printf("HvGetRound tests passed!\n\n");
}

/**
 * Testing for Lord Godalming at Paris in Round 1.
 */
static void testGvGetReachable1()
{
    char *trail = "GPA...."; /*  IMPORTANT!!!!    */
    Message messages[] = {"Gone to Barceleno"};
    GameView gv = GvNew(trail, messages);
    int *numReturnedLocs = -1;
    Round round = GvGetRound(gv);
    PlaceId from = GvGetPlayerLocation(gv, PLAYER_LORD_GODALMING); 
    PlaceId *edges = GvGetReachable(hv, PLAYER_LORD_GODALMING, round, from, numReturnedLocs);
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
 * Testing for Dr. Seward at Barcelona in Round 1. 
 */
static void testGvGetReachable2()
{
    char *trail = "GGE... SBA...."; /*  IMPORTANT!!!!    */
    Message messages[] = {"Gone to Barceleno"};
    GameView gv = GvNew(trail, messages);
    int *numReturnedLocs = -1;
    Round round = GvGetRound(gv);
    PlaceId from = GvGetPlayerLocation(gv, PLAYER_DR_SEWARD);
    PlaceId *edges = GvGetReachable(gv, PLAYER_DR_SEWARD, round, from, numReturnedLocs);
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
    GvFree(gv);
    printf("\tTest 2 passed!\n");
}

/**
 * Testing for Van Helsing at Geneva in Round 1.
 */
static void testGvGetReachable3()
{
    char *trail = "GPA.... SCA .... HGE....";
    Message messages[] = {"Gone to Geneva"};
    GameView gv = GvNew(trail, messages);
    int *numReturnedLocs = -1;
    Round round = GvGetRound(gv);
    PlaceId from = GvGetPlayerLocation(gv, PLAYER_VAN_HELSING);
    PlaceId *edges = GvGetReachable(gv, PLAYER_VAN_HELSING, round, from, numReturnedLocs);
    int visited[NUM_REAL_PLACES];
    for (int i = 0; i < NUM_REAL_PLACES; i++)
    {
        visited[edges[i]] = 1;
    }
    assert(numReturnedLocs <= 11);
    assert(numReturnedLocs != -1);
    assert(numReturnedLocs > 0);
    assert(!visited[GRANADA]);
    assert(!visited[LISBON]);
    assert(!visited[MADRID]);
    assert(visite[GENEVA]);

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
 * Testing for Lord Godaling at Swansea in Round 1.
 */
static void testGvGetReachable5()
{
    char *trail = "GSW....";
    Message messages[] = {"Gone to Galatz"};
    GameView gv = GvNew(trail, messages);
    int *numReturnedLocs = -1;
    Round round = GvGetRound(gv);
    PlaceId from = GvGetPlayerLocation(gv, PLAYER_LORD_GODALMING);
    PlaceId *edges = GvGetReachable(gv, PLAYER_LORD_GODALMING, round, from, numReturnedLocs);
    int *numReturnedLocs = -1;
    PlaceId *edges = GvGetReachable(hv, numReturnedLocs);
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
