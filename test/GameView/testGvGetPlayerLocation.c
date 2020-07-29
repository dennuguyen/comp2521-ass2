#include "testGameView.h"

static void testGvGetPlayerLocation1();
static void testGvGetPlayerLocation2();
static void testGvGetPlayerLocation3();
static void testGvGetPlayerLocation4();
static void testGvGetPlayerLocation5();

void testGvGetPlayerLocation()
{
    printf("Testing GvGetPlayerLocation...\n");

    testGvGetPlayerLocation1();
    testGvGetPlayerLocation2();
    testGvGetPlayerLocation3();
    testGvGetPlayerLocation4();
    testGvGetPlayerLocation5();

    printf("GvGetPlayerLocation tests passed!\n\n");
}

/**
 * Test initialisation on empty string
 */
static void testGvGetPlayerLocation1()
{
    char *trail = "";
    Message messages[] = {};
    GameView gv = GvNew(trail, messages);

    assert(GvGetPlayerLocation(gv, PLAYER_LORD_GODALMING) == NOWHERE);
    assert(GvGetPlayerLocation(gv, PLAYER_DR_SEWARD) == NOWHERE);
    assert(GvGetPlayerLocation(gv, PLAYER_VAN_HELSING) == NOWHERE);
    assert(GvGetPlayerLocation(gv, PLAYER_MINA_HARKER) == NOWHERE);
    assert(GvGetPlayerLocation(gv, PLAYER_DRACULA) == NOWHERE);

    GvFree(gv);
    printf("\tTest 1 passed!\n");
}

/**
 * Test in middle of a round
 */
static void testGvGetPlayerLocation2()
{
    char *trail = "GSW.... SLS....";
    Message messages[] = {};
    GameView gv = GvNew(trail, messages);

    assert(GvGetPlayerLocation(gv, PLAYER_LORD_GODALMING) == SWANSEA);
    assert(GvGetPlayerLocation(gv, PLAYER_DR_SEWARD) == LISBON);
    assert(GvGetPlayerLocation(gv, PLAYER_VAN_HELSING) == NOWHERE);
    assert(GvGetPlayerLocation(gv, PLAYER_MINA_HARKER) == NOWHERE);
    assert(GvGetPlayerLocation(gv, PLAYER_DRACULA) == NOWHERE);

    GvFree(gv);
    printf("\tTest 2 passed!\n");
}

/**
 * Test at end of round
 */
static void testGvGetPlayerLocation3()
{
    char *trail = "GSW.... SLS.... HMR.... MHA.... DSJ.V..";
    Message messages[] = {};
    GameView gv = GvNew(trail, messages);

    assert(GvGetPlayerLocation(gv, PLAYER_LORD_GODALMING) == SWANSEA);
    assert(GvGetPlayerLocation(gv, PLAYER_DR_SEWARD) == LISBON);
    assert(GvGetPlayerLocation(gv, PLAYER_VAN_HELSING) == MARSEILLES);
    assert(GvGetPlayerLocation(gv, PLAYER_MINA_HARKER) == HAMBURG);
    assert(GvGetPlayerLocation(gv, PLAYER_DRACULA) == SARAJEVO);

    GvFree(gv);
    printf("\tTest 3 passed!\n");
}

/**
 * Test small number of rounds
 */
static void testGvGetPlayerLocation4()
{
    char *trail = "GSW.... SLS.... HMR.... MHA.... DSJ.V.. "
                  "GLO.... SAL.... HCO.... MBR.... DBET... "
                  "GED.... SBO.... HLI.... MPR.... DKLT... "
                  "GLV....";
    Message messages[] = {};
    GameView gv = GvNew(trail, messages);

    assert(GvGetPlayerLocation(gv, PLAYER_LORD_GODALMING) == EDINBURGH);
    assert(GvGetPlayerLocation(gv, PLAYER_DR_SEWARD) == BORDEAUX);
    assert(GvGetPlayerLocation(gv, PLAYER_VAN_HELSING) == LEIPZIG);
    assert(GvGetPlayerLocation(gv, PLAYER_MINA_HARKER) == PRAGUE);
    assert(GvGetPlayerLocation(gv, PLAYER_DRACULA) == KLAUSENBURG);

    GvFree(gv);
    printf("\tTest 4 passed!\n");
}

/**
 * Test large number of rounds
 */
static void testGvGetPlayerLocation5()
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

    assert(GvGetPlayerLocation(gv, PLAYER_LORD_GODALMING) == SZEGED);
    assert(GvGetPlayerLocation(gv, PLAYER_DR_SEWARD) == SOFIA);
    assert(GvGetPlayerLocation(gv, PLAYER_VAN_HELSING) == BUCHAREST);
    assert(GvGetPlayerLocation(gv, PLAYER_MINA_HARKER) == SOFIA);
    assert(GvGetPlayerLocation(gv, PLAYER_DRACULA) == SOFIA);

    GvFree(gv);
    printf("\tTest 5 passed!\n");
}
