#include "testHunterView.h"

static void testHvGetRound1();
static void testHvGetRound2();
static void testHvGetRound3();
static void testHvGetRound4();
static void testHvGetRound5();

void testHvGetRound()
{
    printf("Testing HvGetRound...\n");

    testHvGetRound1();
    testHvGetRound2();
    testHvGetRound3();
    testHvGetRound4();
    testHvGetRound5();

    printf("HvGetRound tests passed!\n\n");
}

/**
 * Test initialisation on empty string
 */
static void testHvGetRound1()
{
    char *trail = "";
    Message messages[] = {};
    HunterView hv = HvNew(trail, messages);

    assert(HvGetRound(hv) == 0);

    HvFree(hv);
    printf("\tTest 1 passed!\n");
}

/**
 * Test in middle of a round
 */
static void testHvGetRound2()
{
    char *trail = "GSW.... SLS....";
    Message messages[] = {};
    HunterView hv = HvNew(trail, messages);

    assert(HvGetRound(hv) == 0);

    HvFree(hv);
    printf("\tTest 2 passed!\n");
}

/**
 * Test at end of round
 */
static void testHvGetRound3()
{
    char *trail = "GSW.... SLS.... HMR.... MHA.... DSJ.V..";
    Message messages[] = {};
    HunterView hv = HvNew(trail, messages);

    assert(HvGetRound(hv) == 0);

    HvFree(hv);
    printf("\tTest 3 passed!\n");
}

/**
 * Test small number of rounds
 */
static void testHvGetRound4()
{
    char *trail = "GSW.... SLS.... HMR.... MHA.... DSJ.V.. GLO.... SAL...."
                  "HCO.... MBR.... DBET... GED.... SBO.... HLI.... MPR...."
                  "DKLT... GLV....";
    Message messages[] = {};
    HunterView hv = HvNew(trail, messages);

    assert(HvGetRound(hv) == 3);

    HvFree(hv);
    printf("\tTest 4 passed!\n");
}

/**
 * Test large number of rounds
 */
static void testHvGetRound5()
{
    char *trail = "GSW.... SLS.... HMR.... MHA.... DSJ.V.. GLO.... SAL...."
                  "HCO.... MBR.... DBET... GED.... SBO.... HLI.... MPR...."
                  "DKLT... GLV.... SNA.... HNU.... MBD.... DCDT... GIR...."
                  "SPA.... HPR.... MKLT... DHIT... GAO.... SST.... HSZ...."
                  "MCDTTD. DGAT... GMS.... SFL.... HKL.... MSZ.... DCNT.V."
                  "GTS.... SRO.... HBC.... MCNTD.. DBS..M. GIO.... SBI...."
                  "HCN.... MCN.... DIO.... GIO.... SAS.... HBS.... MCN...."
                  "DTS.... GTS.... SAS.... HIO.... MBS.... DMS.... GMS...."
                  "SIO.... HTS.... MIO.... DAO..M. GAO.... STS.... HMS...."
                  "MTS.... DNS.... GBB.... SMS.... HAO.... MMS.... DED.V.."
                  "GNA.... SAO.... HEC.... MAO.... DMNT... GBO.... SIR...."
                  "HLE.... MEC.... DD2T... GSR.... SDU.... HBU.... MPL...."
                  "DHIT... GSN.... SIR.... HAM.... MLO.... DTPT... GAL...."
                  "SAO.... HCO.... MEC.... DCDT... GMS.... SMS.... HFR...."
                  "MLE.... DKLT.V. GTS.... STS.... HBR.... MCO.... DGAT.M."
                  "GIO.... SIO.... HBD.... MLI.... DD3T.M. GBS.... SBS...."
                  "HKLT... MBR.... DHI..M. GCN.... SCN.... HCDTTTD MVI...."
                  "DTPT... GGAT... SGA.... HSZ.... MBC.... DCDT... GCDTTD."
                  "SCDD... HKL.... MGA.... DKLT... GSZ.... SKLTD.. HKLD..."
                  "MKLD... DBC.V.. GBD.... SBE.... HGA.... MBCVD.. DSOT..."
                  "GSZ.... SSOTD.. HBC.... MSOD...";
    Message messages[] = {};
    HunterView hv = HvNew(trail, messages);

    assert(HvGetRound(hv) == 28);

    HvFree(hv);
    printf("\tTest 5 passed!\n");
}
