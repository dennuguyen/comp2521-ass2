#include "testDraculaView.h"

static void testDvGetScore1();
static void testDvGetScore2();
static void testDvGetScore3();
static void testDvGetScore4();
static void testDvGetScore5();

void testDvGetScore()
{
    printf("Testing DvGetScore...\n");

    testDvGetScore1();
    testDvGetScore2();
    testDvGetScore3();
    testDvGetScore4();
    testDvGetScore5();

    printf("DvGetScore tests passed!\n\n");
}

/**
 * Test initialisation on empty string
 */
static void testDvGetScore1()
{
    char *trail = "";
    Message messages[] = {};
    DraculaView dv = DvNew(trail, messages);

    assert(DvGetScore(dv) == GAME_START_SCORE);

    DvFree(dv);
    printf("\tTest 1 passed!\n");
}

/**
 * Test in middle of a round
 */
static void testDvGetScore2()
{
    char *trail = "GSW.... SLS....";
    Message messages[] = {};
    DraculaView dv = DvNew(trail, messages);

    assert(DvGetScore(dv) == GAME_START_SCORE);

    DvFree(dv);
    printf("\tTest 2 passed!\n");
}

/**
 * Test at end of round
 */
static void testDvGetScore3()
{
    char *trail = "GSW.... SLS.... HMR.... MHA.... DSJ.V..";
    Message messages[] = {};
    DraculaView dv = DvNew(trail, messages);

    assert(DvGetScore(dv) == GAME_START_SCORE);

    DvFree(dv);
    printf("\tTest 3 passed!\n");
}

/**
 * Test small number of rounds
 */
static void testDvGetScore4()
{
    char *trail = "GSW.... SLS.... HMR.... MHA.... DSJ.V.. GLO.... SAL.... "
                  "HCO.... MBR.... DBET... GED.... SBO.... HLI.... MPR.... "
                  "DKLT... GLV....";
    Message messages[] = {};
    DraculaView dv = DvNew(trail, messages);

    assert(DvGetScore(dv) == 363);

    DvFree(dv);
    printf("\tTest 4 passed!\n");
}

/**
 * Test large number of rounds
 */
static void testDvGetScore5()
{
    char *trail = "GSW.... SLS.... HMR.... MHA.... DSJ.V.. GLO.... SAL.... "
                  "HCO.... MBR.... DBET... GED.... SBO.... HLI.... MPR.... "
                  "DKLT... GLV.... SNA.... HNU.... MBD.... DCDT... GIR.... "
                  "SPA.... HPR.... MKLT... DHIT... GAO.... SST.... HSZ.... "
                  "MCDTTD. DGAT... GMS.... SFL.... HKL.... MSZ.... DCNT.V. "
                  "GTS.... SRO.... HBC.... MCNTD.. DBS..M. GIO.... SBI.... "
                  "HCN.... MCN.... DIO.... GIO.... SAS.... HBS.... MCN.... "
                  "DTS.... GTS.... SAS.... HIO.... MBS.... DMS.... GMS.... "
                  "SIO.... HTS.... MIO.... DAO..M. GAO.... STS.... HMS.... "
                  "MTS.... DNS.... GBB.... SMS.... HAO.... MMS.... DED.V.. "
                  "GNA.... SAO.... HEC.... MAO.... DMNT... GBO.... SIR.... "
                  "HLE.... MEC.... DD2T... GSR.... SDU.... HBU.... MPL.... "
                  "DHIT... GSN.... SIR.... HAM.... MLO.... DTPT... GAL.... "
                  "SAO.... HCO.... MEC.... DCDT... GMS.... SMS.... HFR.... "
                  "MLE.... DKLT.V. GTS.... STS.... HBR.... MCO.... DGAT.M. "
                  "GIO.... SIO.... HBD.... MLI.... DD3T.M. GBS.... SBS.... "
                  "HKLT... MBR.... DHI..M. GCN.... SCN.... HCDTTTD MVI.... "
                  "DTPT... GGAT... SGA.... HSZ.... MBC.... DCDT... GCDTTD. "
                  "SCDD... HKL.... MGA.... DKLT... GSZ.... SKLTD.. HKLD... "
                  "MKLD... DBC.V.. GBD.... SBE.... HGA.... MBCVD.. DSOT... "
                  "GSZ.... SSOTD.. HBC.... MSOD...";
    Message messages[] = {};
    DraculaView dv = DvNew(trail, messages);

    assert(DvGetScore(dv) == 282);

    DvFree(dv);
    printf("\tTest 5 passed!\n");
}