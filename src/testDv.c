#include "testDraculaView.h"

static void testDv1();
static void testDv2();
static void testDv3();
static void testDv4();
static void testDv5();

void testDv()
{
    testDv1();
    testDv2();
    testDv3();
    testDv4();
    testDv5();
}

static void testDv1()
{
    printf("Test for basic functions, just before Dracula's first move\n");

    char *trail =
        "GST.... SAO.... HZU.... MBB....";

    Message messages[] = {
        "Hello", "Goodbye", "Stuff", "..."};

    DraculaView dv = DvNew(trail, messages);

    assert(DvGetRound(dv) == 0);
    assert(DvGetScore(dv) == GAME_START_SCORE);
    assert(DvGetHealth(dv, PLAYER_DRACULA) == GAME_START_BLOOD_POINTS);
    assert(DvGetPlayerLocation(dv, PLAYER_LORD_GODALMING) == STRASBOURG);
    assert(DvGetPlayerLocation(dv, PLAYER_DR_SEWARD) == ATLANTIC_OCEAN);
    assert(DvGetPlayerLocation(dv, PLAYER_VAN_HELSING) == ZURICH);
    assert(DvGetPlayerLocation(dv, PLAYER_MINA_HARKER) == BAY_OF_BISCAY);
    assert(DvGetPlayerLocation(dv, PLAYER_DRACULA) == NOWHERE);
    assert(DvGetVampireLocation(dv) == NOWHERE);
    int numTraps = -1;
    PlaceId *traps = DvGetTrapLocations(dv, &numTraps);
    assert(numTraps == 0);
    free(traps);

    printf("Test passed!\n");
    DvFree(dv);
}

static void testDv2()
{
    printf("Test for encountering Dracula\n");

    char *trail =
        "GST.... SAO.... HCD.... MAO.... DGE.V.. "
        "GGEVD.. SAO.... HCD.... MAO....";

    Message messages[] = {
        "Hello", "Goodbye", "Stuff", "...", "Mwahahah",
        "Aha!", "", "", ""};

    DraculaView dv = DvNew(trail, messages);

    assert(DvGetRound(dv) == 1);
    assert(DvGetScore(dv) == GAME_START_SCORE - SCORE_LOSS_DRACULA_TURN);
    assert(DvGetHealth(dv, PLAYER_LORD_GODALMING) == 5);
    assert(DvGetHealth(dv, PLAYER_DRACULA) == 30);
    assert(DvGetPlayerLocation(dv, PLAYER_LORD_GODALMING) == GENEVA);
    assert(DvGetPlayerLocation(dv, PLAYER_DRACULA) == GENEVA);
    assert(DvGetVampireLocation(dv) == NOWHERE);

    printf("Test passed!\n");
    DvFree(dv);
}

static void testDv3()
{
    printf("Test for Dracula leaving minions 1\n");

    char *trail =
        "GGE.... SGE.... HGE.... MGE.... DED.V.. "
        "GST.... SST.... HST.... MST.... DMNT... "
        "GST.... SST.... HST.... MST.... DLOT... "
        "GST.... SST.... HST.... MST.... DHIT... "
        "GST.... SST.... HST.... MST....";

    Message messages[24] = {};
    DraculaView dv = DvNew(trail, messages);

    assert(DvGetRound(dv) == 4);
    assert(DvGetVampireLocation(dv) == EDINBURGH);
    int numTraps = -1;
    PlaceId *traps = DvGetTrapLocations(dv, &numTraps);
    assert(numTraps == 3);
    sortPlaces(traps, numTraps);
    assert(traps[0] == LONDON);
    assert(traps[1] == LONDON);
    assert(traps[2] == MANCHESTER);
    free(traps);

    printf("Test passed!\n");
    DvFree(dv);
}

static void testDv4()
{
    printf("Test for Dracula's valid moves 1\n");

    char *trail =
        "GGE.... SGE.... HGE.... MGE.... DCD.V.. "
        "GGE.... SGE.... HGE.... MGE....";

    Message messages[9] = {};
    DraculaView dv = DvNew(trail, messages);

    int numMoves = -1;
    PlaceId *moves = DvGetValidMoves(dv, &numMoves);

    assert(numMoves == 4);
    sortPlaces(moves, numMoves);
    assert(moves[0] == GALATZ);
    assert(moves[1] == KLAUSENBURG);
    assert(moves[2] == HIDE);
    assert(moves[3] == DOUBLE_BACK_1);
    free(moves);

    printf("Test passed!\n");
    DvFree(dv);
}

static void testDv5()
{
    printf("Test for DvWhereCanIGo 1\n");

    char *trail =
        "GGE.... SGE.... HGE.... MGE.... DKL.V.. "
        "GGE.... SGE.... HGE.... MGE.... DD1T... "
        "GGE.... SGE.... HGE.... MGE.... DBCT... "
        "GGE.... SGE.... HGE.... MGE.... DHIT... "
        "GGE.... SGE.... HGE.... MGE....";

    Message messages[24] = {};
    DraculaView dv = DvNew(trail, messages);

    int numLocs = -1;
    PlaceId *locs = DvWhereCanIGo(dv, &numLocs);
    assert(numLocs == 4);
    sortPlaces(locs, numLocs);
    assert(locs[0] == BELGRADE);
    assert(locs[1] == CONSTANTA);
    assert(locs[2] == GALATZ);
    assert(locs[3] == SOFIA);
    free(locs);

    printf("Test passed!\n");
    DvFree(dv);
}
