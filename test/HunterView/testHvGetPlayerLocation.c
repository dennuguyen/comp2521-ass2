#include "testHunterView.h"

static void testHvGetPlayerLocation1();
static void testHvGetPlayerLocation2();
static void testHvGetPlayerLocation3();
static void testHvGetPlayerLocation4();
static void testHvGetPlayerLocation5();
static void testHvGetPlayerLocation6();

void testHvGetPlayerLocation()
{
    printf("Testing HvGetPlayerLocation...\n");

    testHvGetPlayerLocation1();
    testHvGetPlayerLocation2();
    testHvGetPlayerLocation3();
    testHvGetPlayerLocation4();
    testHvGetPlayerLocation5();
    testHvGetPlayerLocation6();

    printf("HvGetPlayerLocation tests passed!\n\n");
}

/**
 * Test initialisation on empty string
 */
static void testHvGetPlayerLocation1()
{
    char *trail = "";
    Message messages[] = {};
    HunterView hv = HvNew(trail, messages);

    assert(HvGetPlayerLocation(hv, PLAYER_LORD_GODALMING) == NOWHERE);
    assert(HvGetPlayerLocation(hv, PLAYER_DR_SEWARD) == NOWHERE);
    assert(HvGetPlayerLocation(hv, PLAYER_VAN_HELSING) == NOWHERE);
    assert(HvGetPlayerLocation(hv, PLAYER_MINA_HARKER) == NOWHERE);
    assert(HvGetPlayerLocation(hv, PLAYER_DRACULA) == NOWHERE);

    HvFree(hv);
    printf("\tTest 1 passed!\n");
}

/**
 * Test in middle of a round
 */
static void testHvGetPlayerLocation2()
{
    char *trail = "GSW.... SLS....";
    Message messages[] = {};
    HunterView hv = HvNew(trail, messages);

    assert(HvGetPlayerLocation(hv, PLAYER_LORD_GODALMING) == SWANSEA);
    assert(HvGetPlayerLocation(hv, PLAYER_DR_SEWARD) == LISBON);
    assert(HvGetPlayerLocation(hv, PLAYER_VAN_HELSING) == NOWHERE);
    assert(HvGetPlayerLocation(hv, PLAYER_MINA_HARKER) == NOWHERE);
    assert(HvGetPlayerLocation(hv, PLAYER_DRACULA) == NOWHERE);

    HvFree(hv);
    printf("\tTest 2 passed!\n");
}

/**
 * Test at end of round
 */
static void testHvGetPlayerLocation3()
{
    char *trail = "GSW.... SLS.... HMR.... MHA.... DSJ.V..";
    Message messages[] = {};
    HunterView hv = HvNew(trail, messages);

    assert(HvGetPlayerLocation(hv, PLAYER_LORD_GODALMING) == SWANSEA);
    assert(HvGetPlayerLocation(hv, PLAYER_DR_SEWARD) == LISBON);
    assert(HvGetPlayerLocation(hv, PLAYER_VAN_HELSING) == MARSEILLES);
    assert(HvGetPlayerLocation(hv, PLAYER_MINA_HARKER) == HAMBURG);
    assert(HvGetPlayerLocation(hv, PLAYER_DRACULA) == SARAJEVO);

    HvFree(hv);
    printf("\tTest 3 passed!\n");
}

/**
 * Test city unknown
 */
static void testHvGetPlayerLocation4()
{
    char *trail = "GSW.... SLS.... HMR.... MHA.... DSJ.V.. GLO.... SAL.... "
                  "HCO.... MBR.... DBET... GED.... SBO.... HLI.... MPR.... "
                  "DKLT... GLV....";
    Message messages[] = {};
    HunterView hv = HvNew(trail, messages);

    assert(HvGetPlayerLocation(hv, PLAYER_LORD_GODALMING) == EDINBURGH);
    assert(HvGetPlayerLocation(hv, PLAYER_DR_SEWARD) == BORDEAUX);
    assert(HvGetPlayerLocation(hv, PLAYER_VAN_HELSING) == LEIPZIG);
    assert(HvGetPlayerLocation(hv, PLAYER_MINA_HARKER) == PRAGUE);
    assert(HvGetPlayerLocation(hv, PLAYER_DRACULA) == CITY_UNKNOWN);

    HvFree(hv);
    printf("\tTest 4 passed!\n");
}

/**
 * Test sea unknown
 */
static void testHvGetPlayerLocation5()
{
    char *trail = "GSW.... SLS.... HMR.... MHA.... DSJ.V.. GLO.... SAL.... "
                  "HCO.... MBR.... DBET... GED.... SBO.... HLI.... MPR.... "
                  "DKLT... GLV.... SNA.... HNU.... MBD.... DCDT... GIR.... "
                  "SPA.... HPR.... MKLT... DHIT... GAO.... SST.... HSZ.... "
                  "MCDTTD. DGAT... GMS.... SFL.... HKL.... MSZ.... DCNT.V. "
                  "GTS.... SRO.... HBC.... MCNTD.. DBS..M.";
    Message messages[] = {};
    HunterView hv = HvNew(trail, messages);

    assert(HvGetPlayerLocation(hv, PLAYER_LORD_GODALMING) == TYRRHENIAN_SEA);
    assert(HvGetPlayerLocation(hv, PLAYER_DR_SEWARD) == ROME);
    assert(HvGetPlayerLocation(hv, PLAYER_VAN_HELSING) == BUCHAREST);
    assert(HvGetPlayerLocation(hv, PLAYER_MINA_HARKER) == CONSTANTA);
    assert(HvGetPlayerLocation(hv, PLAYER_DRACULA) == SEA_UNKNOWN);

    HvFree(hv);
    printf("\tTest 5 passed!\n");
}

/**
 * Test large number of rounds
 */
static void testHvGetPlayerLocation6()
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
    HunterView hv = HvNew(trail, messages);

    assert(HvGetPlayerLocation(hv, PLAYER_LORD_GODALMING) == SZEGED);
    assert(HvGetPlayerLocation(hv, PLAYER_DR_SEWARD) == SOFIA);
    assert(HvGetPlayerLocation(hv, PLAYER_VAN_HELSING) == BUCHAREST);
    assert(HvGetPlayerLocation(hv, PLAYER_MINA_HARKER) == SOFIA);
    assert(HvGetPlayerLocation(hv, PLAYER_DRACULA) == SOFIA);

    HvFree(hv);
    printf("\tTest 6 passed!\n");
}
