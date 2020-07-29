#include "testDraculaView.h"

static void testDvGetPlayerLocation1();
static void testDvGetPlayerLocation2();
static void testDvGetPlayerLocation3();
static void testDvGetPlayerLocation4();
static void testDvGetPlayerLocation5();

void testDvGetPlayerLocation()
{
    printf("Testing DvGetPlayerLocation...\n");

    testDvGetPlayerLocation1();
    testDvGetPlayerLocation2();
    testDvGetPlayerLocation3();
    testDvGetPlayerLocation4();
    testDvGetPlayerLocation5();

    printf("DvGetPlayerLocation tests passed!\n\n");
}

/**
 * Test initialisation on empty string
 */
static void testDvGetPlayerLocation1()
{
    char *trail = "";
    Message messages[] = {};
    DraculaView dv = DvNew(trail, messages);

    assert(DvGetPlayerLocation(dv, PLAYER_LORD_GODALMING) == NOWHERE);
    assert(DvGetPlayerLocation(dv, PLAYER_DR_SEWARD) == NOWHERE);
    assert(DvGetPlayerLocation(dv, PLAYER_VAN_HELSING) == NOWHERE);
    assert(DvGetPlayerLocation(dv, PLAYER_MINA_HARKER) == NOWHERE);
    assert(DvGetPlayerLocation(dv, PLAYER_DRACULA) == NOWHERE);

    DvFree(dv);
    printf("\tTest 1 passed!\n");
}

/**
 * Test in middle of a round
 */
static void testDvGetPlayerLocation2()
{
    char *trail = "GSW.... SLS....";
    Message messages[] = {};
    DraculaView dv = DvNew(trail, messages);

    assert(DvGetPlayerLocation(dv, PLAYER_LORD_GODALMING) == SWANSEA);
    assert(DvGetPlayerLocation(dv, PLAYER_DR_SEWARD) == LISBON);
    assert(DvGetPlayerLocation(dv, PLAYER_VAN_HELSING) == NOWHERE);
    assert(DvGetPlayerLocation(dv, PLAYER_MINA_HARKER) == NOWHERE);
    assert(DvGetPlayerLocation(dv, PLAYER_DRACULA) == NOWHERE);

    DvFree(dv);
    printf("\tTest 2 passed!\n");
}

/**
 * Test at end of round
 */
static void testDvGetPlayerLocation3()
{
    char *trail = "GSW.... SLS.... HMR.... MHA.... DSJ.V..";
    Message messages[] = {};
    DraculaView dv = DvNew(trail, messages);

    assert(DvGetPlayerLocation(dv, PLAYER_LORD_GODALMING) == SWANSEA);
    assert(DvGetPlayerLocation(dv, PLAYER_DR_SEWARD) == LISBON);
    assert(DvGetPlayerLocation(dv, PLAYER_VAN_HELSING) == MARSEILLES);
    assert(DvGetPlayerLocation(dv, PLAYER_MINA_HARKER) == HAMBURG);
    assert(DvGetPlayerLocation(dv, PLAYER_DRACULA) == SARAJEVO);

    DvFree(dv);
    printf("\tTest 3 passed!\n");
}

/**
 * Test small number of rounds
 */
static void testDvGetPlayerLocation4()
{
    char *trail = "GSW.... SLS.... HMR.... MHA.... DSJ.V.. "
                  "GLO.... SAL.... HCO.... MBR.... DBET... "
                  "GED.... SBO.... HLI.... MPR.... DKLT... "
                  "GLV....";
    Message messages[] = {};
    DraculaView dv = DvNew(trail, messages);

    assert(DvGetPlayerLocation(dv, PLAYER_LORD_GODALMING) == EDINBURGH);
    assert(DvGetPlayerLocation(dv, PLAYER_DR_SEWARD) == BORDEAUX);
    assert(DvGetPlayerLocation(dv, PLAYER_VAN_HELSING) == LEIPZIG);
    assert(DvGetPlayerLocation(dv, PLAYER_MINA_HARKER) == PRAGUE);
    assert(DvGetPlayerLocation(dv, PLAYER_DRACULA) == KLAUSENBURG);

    DvFree(dv);
    printf("\tTest 4 passed!\n");
}

/**
 * Test large number of rounds
 */
static void testDvGetPlayerLocation5()
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
    DraculaView dv = DvNew(trail, messages);

    assert(DvGetPlayerLocation(dv, PLAYER_LORD_GODALMING) == SZEGED);
    assert(DvGetPlayerLocation(dv, PLAYER_DR_SEWARD) == SOFIA);
    assert(DvGetPlayerLocation(dv, PLAYER_VAN_HELSING) == BUCHAREST);
    assert(DvGetPlayerLocation(dv, PLAYER_MINA_HARKER) == SOFIA);
    assert(DvGetPlayerLocation(dv, PLAYER_DRACULA) == SOFIA);

    DvFree(dv);
    printf("\tTest 5 passed!\n");
}
