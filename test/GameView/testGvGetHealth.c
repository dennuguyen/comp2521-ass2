#include "testGameView.h"

static void testGvGetHealth1();
static void testGvGetHealth2();
static void testGvGetHealth3();
static void testGvGetHealth4();
static void testGvGetHealth5();
static void testGvGetHealth6();

void testGvGetHealth()
{
    printf("Testing GvGetHealth...\n");

    testGvGetHealth1();
    testGvGetHealth2();
    testGvGetHealth3();
    testGvGetHealth4();
    testGvGetHealth5();
    testGvGetHealth6();

    printf("GvGetHealth tests passed!\n\n");
}

/**
 * Test initialisation on empty string
 */
static void testGvGetHealth1()
{
    char *trail = "";
    Message messages[] = {};
    GameView gv = GvNew(trail, messages);

    assert(GvGetHealth(gv, PLAYER_LORD_GODALMING) == GAME_START_HUNTER_LIFE_POINTS);
    assert(GvGetHealth(gv, PLAYER_DR_SEWARD) == GAME_START_HUNTER_LIFE_POINTS);
    assert(GvGetHealth(gv, PLAYER_VAN_HELSING) == GAME_START_HUNTER_LIFE_POINTS);
    assert(GvGetHealth(gv, PLAYER_MINA_HARKER) == GAME_START_HUNTER_LIFE_POINTS);
    assert(GvGetHealth(gv, PLAYER_DRACULA) == GAME_START_BLOOD_POINTS);

    GvFree(gv);
    printf("\tTest 1 passed!\n");
}

/**
 * Test middle of round
 */
static void testGvGetHealth2()
{
    char *trail = "GKL.... SKL....";
    Message messages[] = {};
    GameView gv = GvNew(trail, messages);

    assert(GvGetHealth(gv, PLAYER_LORD_GODALMING) == 9);
    assert(GvGetHealth(gv, PLAYER_DR_SEWARD) == 9);
    assert(GvGetHealth(gv, PLAYER_VAN_HELSING) == 9);
    assert(GvGetHealth(gv, PLAYER_MINA_HARKER) == 9);
    assert(GvGetHealth(gv, PLAYER_DRACULA) == 40);

    GvFree(gv);
    printf("\tTest 2 passed!\n");
}

/**
 * Test hunter and trap encounter
 */
static void testGvGetHealth3()
{
    char *trail = "GSW.... SLS.... HMR.... MJM.... DSJ.V.. "
                  "GLO.... SAL.... HCO.... MSZ.... DBET... "
                  "GED.... SBO.... HLI.... MSZ.... DKLT... "
                  "GLV.... SNA.... HNU.... MBET...";
    Message messages[] = {};
    GameView gv = GvNew(trail, messages);

    assert(GvGetHealth(gv, PLAYER_LORD_GODALMING) == 9);
    assert(GvGetHealth(gv, PLAYER_DR_SEWARD) == 9);
    assert(GvGetHealth(gv, PLAYER_VAN_HELSING) == 9);
    assert(GvGetHealth(gv, PLAYER_MINA_HARKER) == 7);
    assert(GvGetHealth(gv, PLAYER_DRACULA) == 40);

    GvFree(gv);
    printf("\tTest 3 passed!\n");
}

/**
 * Test hunter and immature vampire encounter
 */
static void testGvGetHealth4()
{
    char *trail = "GSW.... SLS.... HMR.... MJM.... DSJ.V.. "
                  "GSW.... SLS.... HMR.... MJM.... DBET... "
                  "GSW.... SLS.... HMR.... MJM.... DKLT... "
                  "GSW.... SLS.... HMR.... MJM.... DBCT... "
                  "GSW.... SLS.... HMR.... MJM.... DSOT... "
                  "GSW.... SLS.... HMR.... MSJV... DSAT... "
                  "GSW.... SLS.... HMR.... MJM.... DVAT...";
    Message messages[] = {};
    GameView gv = GvNew(trail, messages);

    assert(GvGetHealth(gv, PLAYER_LORD_GODALMING) == 9);
    assert(GvGetHealth(gv, PLAYER_DR_SEWARD) == 9);
    assert(GvGetHealth(gv, PLAYER_VAN_HELSING) == 9);
    assert(GvGetHealth(gv, PLAYER_MINA_HARKER) == 9);
    assert(GvGetHealth(gv, PLAYER_DRACULA) == 40);

    GvFree(gv);
    printf("\tTest 4 passed!\n");
}

/**
 * Test dracula at sea
 */
static void testGvGetHealth5()
{
    char *trail = "GSW.... SLS.... HMR.... MJM.... DCN.V.. "
                  "GSW.... SLS.... HMR.... MJM.... DBS....";
    Message messages[] = {};
    GameView gv = GvNew(trail, messages);

    assert(GvGetHealth(gv, PLAYER_LORD_GODALMING) == 9);
    assert(GvGetHealth(gv, PLAYER_DR_SEWARD) == 9);
    assert(GvGetHealth(gv, PLAYER_VAN_HELSING) == 9);
    assert(GvGetHealth(gv, PLAYER_MINA_HARKER) == 9);
    assert(GvGetHealth(gv, PLAYER_DRACULA) == 38);

    GvFree(gv);
    printf("\tTest 5 passed!\n");
}

/**
 * Test large number of rounds
 */
static void testGvGetHealth6()
{
    char *trail = "GSW.... SLS.... HMR.... MHA.... DSJ.V.. "
                  "GLO.... SAL.... HCO.... MBR.... DBET... "
                  "GED.... SBO.... HLI.... MPR.... DKLT... "
                  "GLV.... SNA.... HNU.... MBD.... DCDT... "
                  "GIR.... SPA.... HPR.... MKLT... DHIT... "
                  "GAO.... SST.... HSZ.... MCDTTD. DGAT... "
                  "GMS.... SFL.... HKL.... MSZ.... DCNT.V. "
                  "GTS.... SRO.... HBC.... MCNTD.. DBS..M. "
                  "GIO.... SBI.... HCN.... MCN.... DIO.... "
                  "GIO.... SAS.... HBS.... MCN.... DTS.... "
                  "GTS.... SAS.... HIO.... MBS.... DMS.... "
                  "GMS.... SIO.... HTS.... MIO.... DAO..M. "
                  "GAO.... STS.... HMS.... MTS.... DNS.... "
                  "GBB.... SMS.... HAO.... MMS.... DED.V.. "
                  "GNA.... SAO.... HEC.... MAO.... DMNT... "
                  "GBO.... SIR.... HLE.... MEC.... DD2T... "
                  "GSR.... SDU.... HBU.... MPL.... DHIT... "
                  "GSN.... SIR.... HAM.... MLO.... DTPT... "
                  "GAL.... SAO.... HCO.... MEC.... DCDT... "
                  "GMS.... SMS.... HFR.... MLE.... DKLT.V. "
                  "GTS.... STS.... HBR.... MCO.... DGAT.M. "
                  "GIO.... SIO.... HBD.... MLI.... DD3T.M. "
                  "GBS.... SBS.... HKLT... MBR.... DHI..M. "
                  "GCN.... SCN.... HCDTTTD MVI.... DTPT... "
                  "GGAT... SGA.... HSZ.... MBC.... DCDT... "
                  "GCDTTD. SCDD... HKL.... MGA.... DKLT... "
                  "GSZ.... SKLTD.. HKLD... MKLD... DBC.V.. "
                  "GBD.... SBE.... HGA.... MBCVD.. DSOT... "
                  "GSZ.... SSOTD.. HBC.... MSOD...";
    Message messages[] = {};
    GameView gv = GvNew(trail, messages);

    assert(GvGetHealth(gv, PLAYER_DR_SEWARD) == 3);
    assert(GvGetHealth(gv, PLAYER_VAN_HELSING) == 8);
    assert(GvGetHealth(gv, PLAYER_MINA_HARKER) == 0);
    assert(GvGetHealth(gv, PLAYER_DRACULA) == 0);

    GvFree(gv);
    printf("\tTest 6 passed!\n");
}
