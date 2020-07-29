#include "testGameView.h"

static void testGvGetScore1();
static void testGvGetScore2();
static void testGvGetScore3();
static void testGvGetScore4();
static void testGvGetScore5();

void testGvGetScore()
{
    printf("Testing GvGetScore...\n");

    testGvGetScore1();
    testGvGetScore2();
    testGvGetScore3();
    testGvGetScore4();
    testGvGetScore5();

    printf("GvGetScore tests passed!\n\n");
}

/**
 * Test initialisation on empty string
 */
static void testGvGetScore1()
{
    char *trail = "";
    Message messages[] = {};
    GameView gv = GvNew(trail, messages);

    assert(GvGetScore(gv) == GAME_START_SCORE);

    GvFree(gv);
    printf("\tTest 1 passed!\n");
}

/**
 * Test in middle of a round
 */
static void testGvGetScore2()
{
    char *trail = "GSW.... SLS....";
    Message messages[] = {};
    GameView gv = GvNew(trail, messages);

    assert(GvGetScore(gv) == GAME_START_SCORE);

    GvFree(gv);
    printf("\tTest 2 passed!\n");
}

/**
 * Test at end of round
 */
static void testGvGetScore3()
{
    char *trail = "GSW.... SLS.... HMR.... MHA.... DSJ.V..";
    Message messages[] = {};
    GameView gv = GvNew(trail, messages);

    assert(GvGetScore(gv) == GAME_START_SCORE - SCORE_LOSS_DRACULA_TURN);

    GvFree(gv);
    printf("\tTest 3 passed!\n");
}

/**
 * Test small number of rounds
 */
static void testGvGetScore4()
{
    char *trail = "GSW.... SLS.... HMR.... MHA.... DSJ.V.. "
                  "GLO.... SAL.... HCO.... MBR.... DBET... "
                  "GED.... SBO.... HLI.... MPR.... DKLT... "
                  "GLV....";
    Message messages[] = {};
    GameView gv = GvNew(trail, messages);

    assert(GvGetScore(gv) == 363);

    GvFree(gv);
    printf("\tTest 4 passed!\n");
}

/**
 * Test large number of rounds
 */
static void testGvGetScore5()
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

    assert(GvGetScore(gv) == 282);

    GvFree(gv);
    printf("\tTest 5 passed!\n");
}
