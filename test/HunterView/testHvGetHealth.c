#include "testHunterView.h"

static void testHvGetHealth1();
static void testHvGetHealth2();
static void testHvGetHealth3();
static void testHvGetHealth4();
static void testHvGetHealth5();
static void testHvGetHealth6();

void testHvGetHealth()
{
    printf("Testing HvGetHealth...\n");

    testHvGetHealth1();
    testHvGetHealth2();
    testHvGetHealth3();
    testHvGetHealth4();
    testHvGetHealth5();
    testHvGetHealth6();

    printf("HvGetHealth tests passed!\n\n");
}

/**
 * Test initialisation on empty string
 */
static void testHvGetHealth1()
{
    char *trail = "";
    Message messages[] = {};
    HunterView hv = HvNew(trail, messages);

    assert(HvGetHealth(hv, PLAYER_LORD_GODALMING) == GAME_START_HUNTER_LIFE_POINTS);
    assert(HvGetHealth(hv, PLAYER_DR_SEWARD) == GAME_START_HUNTER_LIFE_POINTS);
    assert(HvGetHealth(hv, PLAYER_VAN_HELSING) == GAME_START_HUNTER_LIFE_POINTS);
    assert(HvGetHealth(hv, PLAYER_MINA_HARKER) == GAME_START_HUNTER_LIFE_POINTS);
    assert(HvGetHealth(hv, PLAYER_DRACULA) == GAME_START_BLOOD_POINTS);

    HvFree(hv);
    printf("\tTest 1 passed!\n");
}

/**
 * Test hunter and dracula encounter
 */
static void testHvGetHealth2()
{
    char *trail = "GKL.... SKL....";
    Message messages[] = {};
    HunterView hv = HvNew(trail, messages);

    assert(HvGetHealth(hv, PLAYER_LORD_GODALMING) == 5);
    assert(HvGetHealth(hv, PLAYER_DR_SEWARD) == 5);
    assert(HvGetHealth(hv, PLAYER_VAN_HELSING) == 9);
    assert(HvGetHealth(hv, PLAYER_MINA_HARKER) == 9);
    assert(HvGetHealth(hv, PLAYER_DRACULA) == 30);

    HvFree(hv);
    printf("\tTest 2 passed!\n");
}

/**
 * Test hunter and trap encounter
 */
static void testHvGetHealth3()
{
    char *trail = "GSW.... SLS.... HMR.... MHA.... DSJ.V.. "
                  "GLO.... SAL.... HCO.... MBR.... DBET... "
                  "GED.... SBO.... HLI.... MPR.... DKLT... "
                  "GLV.... SNA.... HNU.... MBD.... DCDT... "
                  "GIR.... SPA.... HPR.... MKLT...";
    Message messages[] = {};
    HunterView hv = HvNew(trail, messages);

    assert(HvGetHealth(hv, PLAYER_LORD_GODALMING) == 9);
    assert(HvGetHealth(hv, PLAYER_DR_SEWARD) == 9);
    assert(HvGetHealth(hv, PLAYER_VAN_HELSING) == 9);
    assert(HvGetHealth(hv, PLAYER_MINA_HARKER) == 7);
    assert(HvGetHealth(hv, PLAYER_DRACULA) == 40);

    HvFree(hv);
    printf("\tTest 3 passed!\n");
}

/**
 * Test hunter and immature vampire encounter
 */
static void testHvGetHealth4()
{
    char *trail = "GSW.... SLS.... HMR.... MJM.... DSJ.V.. "
                  "GSW.... SLS.... HMR.... MJM.... DBET... "
                  "GSW.... SLS.... HMR.... MJM.... DKLT... "
                  "GSW.... SLS.... HMR.... MJM.... DBCT... "
                  "GSW.... SLS.... HMR.... MJM.... DSOT... "
                  "GSW.... SLS.... HMR.... MSJV... DSAT... "
                  "GSW.... SLS.... HMR.... MJM.... DVAT... ";
    Message messages[] = {};
    HunterView hv = HvNew(trail, messages);

    assert(HvGetHealth(hv, PLAYER_LORD_GODALMING) == 9);
    assert(HvGetHealth(hv, PLAYER_DR_SEWARD) == 9);
    assert(HvGetHealth(hv, PLAYER_VAN_HELSING) == 9);
    assert(HvGetHealth(hv, PLAYER_MINA_HARKER) == 9);
    assert(HvGetHealth(hv, PLAYER_DRACULA) == 40);

    HvFree(hv);
    printf("\tTest 4 passed!\n");
}

/**
 * Test dracula at sea
 */
static void testHvGetHealth5()
{
    char *trail = "GSW.... SLS.... HMR.... MJM.... DCN.V.. "
                  "GSW.... SLS.... HMR.... MJM.... DBS....";
    Message messages[] = {};
    HunterView hv = HvNew(trail, messages);

    assert(HvGetHealth(hv, PLAYER_LORD_GODALMING) == 9);
    assert(HvGetHealth(hv, PLAYER_DR_SEWARD) == 9);
    assert(HvGetHealth(hv, PLAYER_VAN_HELSING) == 9);
    assert(HvGetHealth(hv, PLAYER_MINA_HARKER) == 9);
    assert(HvGetHealth(hv, PLAYER_DRACULA) == 38);

    HvFree(hv);
    printf("\tTest 5 passed!\n");
}

/**
 * Test large number of rounds
 */
static void testHvGetHealth6()
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

    assert(HvGetHealth(hv, PLAYER_LORD_GODALMING) == 9);
    assert(HvGetHealth(hv, PLAYER_DR_SEWARD) == 3);
    assert(HvGetHealth(hv, PLAYER_VAN_HELSING) == 8);
    assert(HvGetHealth(hv, PLAYER_MINA_HARKER) == 0);
    assert(HvGetHealth(hv, PLAYER_DRACULA) == 0);

    HvFree(hv);
    printf("\tTest 6 passed!\n");
}
