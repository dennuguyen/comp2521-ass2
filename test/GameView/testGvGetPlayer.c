#include "testGameView.h"

static void testGvGetPlayer1();
static void testGvGetPlayer2();
static void testGvGetPlayer3();
static void testGvGetPlayer4();
static void testGvGetPlayer5();

void testGvGetPlayer()
{
    printf("Testing GvGetPlayer...\n");

    testGvGetPlayer1();
    testGvGetPlayer2();
    testGvGetPlayer3();
    testGvGetPlayer4();
    testGvGetPlayer5();

    printf("GvGetPlayer tests passed!\n\n");
}

/**
 * Test initialisation on empty string
 */
static void testGvGetPlayer1()
{
    char *trail = "";
    Message messages[] = {};
    GameView gv = GvNew(trail, messages);

    assert(GvGetPlayer(gv) == PLAYER_LORD_GODALMING);

    GvFree(gv);
    printf("\tTest 1 passed!\n");
}

/**
 * Test in middle of a round
 */
static void testGvGetPlayer2()
{
    char *trail = "GSW.... SLS....";
    Message messages[] = {};
    GameView gv = GvNew(trail, messages);

    assert(GvGetPlayer(gv) == PLAYER_VAN_HELSING);

    GvFree(gv);
    printf("\tTest 2 passed!\n");
}

/**
 * Test at end of round
 */
static void testGvGetPlayer3()
{
    char *trail = "GSW.... SLS.... HMR.... MHA.... DSJ.V..";
    Message messages[] = {};
    GameView gv = GvNew(trail, messages);

    assert(GvGetPlayer(gv) == PLAYER_LORD_GODALMING);

    GvFree(gv);
    printf("\tTest 3 passed!\n");
}

/**
 * Test small number of rounds
 */
static void testGvGetPlayer4()
{
    char *trail = "GSW.... SLS.... HMR.... MHA.... DSJ.V.. "
                  "GLO.... SAL.... HCO.... MBR.... DBET... "
                  "GED.... SBO.... HLI.... MPR.... DKLT... "
                  "GLV....";
    Message messages[] = {};
    GameView gv = GvNew(trail, messages);

    assert(GvGetPlayer(gv) == PLAYER_DR_SEWARD);

    GvFree(gv);
    printf("\tTest 4 passed!\n");
}

/**
 * Test large number of rounds
 */
static void testGvGetPlayer5()
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

    assert(GvGetPlayer(gv) == PLAYER_DRACULA);

    GvFree(gv);
    printf("\tTest 5 passed!\n");
}
