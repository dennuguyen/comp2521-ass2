#include "testDraculaView.h"

static void testDvGetHealth1();
static void testDvGetHealth2();
static void testDvGetHealth3();
static void testDvGetHealth4();
static void testDvGetHealth5();
static void testDvGetHealth6();

void testDvGetHealth()
{
    printf("Testing DvGetHealth...\n");

    testDvGetHealth1();
    testDvGetHealth2();
    testDvGetHealth3();
    testDvGetHealth4();
    testDvGetHealth5();
    testDvGetHealth6();

    printf("DvGetHealth tests passed!\n\n");
}

/**
 * Test initialisation on empty string
 */
static void testDvGetHealth1()
{
    char *trail = "";
    Message messages[] = {};
    DraculaView dv = DvNew(trail, messages);

    assert(DvGetHealth(dv, PLAYER_LORD_GODALMING) == GAME_START_HUNTER_LIFE_POINTS);
    assert(DvGetHealth(dv, PLAYER_DR_SEWARD) == GAME_START_HUNTER_LIFE_POINTS);
    assert(DvGetHealth(dv, PLAYER_VAN_HELSING) == GAME_START_HUNTER_LIFE_POINTS);
    assert(DvGetHealth(dv, PLAYER_MINA_HARKER) == GAME_START_HUNTER_LIFE_POINTS);
    assert(DvGetHealth(dv, PLAYER_DRACULA) == GAME_START_BLOOD_POINTS);

    DvFree(dv);
    printf("\tTest 1 passed!\n");
}

/**
 * Test hunter and dracula encounter
 */
static void testDvGetHealth2()
{
    char *trail = "GKL.... SKL....";
    Message messages[] = {};
    DraculaView dv = DvNew(trail, messages);

    assert(DvGetHealth(dv, PLAYER_LORD_GODALMING) == 5);
    assert(DvGetHealth(dv, PLAYER_DR_SEWARD) == 5);
    assert(DvGetHealth(dv, PLAYER_VAN_HELSING) == 9);
    assert(DvGetHealth(dv, PLAYER_MINA_HARKER) == 9);
    assert(DvGetHealth(dv, PLAYER_DRACULA) == 30);

    DvFree(dv);
    printf("\tTest 2 passed!\n");
}

/**
 * Test hunter and trap encounter
 */
static void testDvGetHealth3()
{
    char *trail = "GSW.... SLS.... HMR.... MHA.... DSJ.V.."
                  "GLO.... SAL.... HCO.... MBR.... DBET..."
                  "GED.... SBO.... HLI.... MPR.... DKLT..."
                  "GLV.... SNA.... HNU.... MBD.... DCDT..."
                  "GIR.... SPA.... HPR.... MKLT...";
    Message messages[] = {};
    DraculaView dv = DvNew(trail, messages);

    assert(DvGetHealth(dv, PLAYER_LORD_GODALMING) == 9);
    assert(DvGetHealth(dv, PLAYER_DR_SEWARD) == 9);
    assert(DvGetHealth(dv, PLAYER_VAN_HELSING) == 9);
    assert(DvGetHealth(dv, PLAYER_MINA_HARKER) == 7);
    assert(DvGetHealth(dv, PLAYER_DRACULA) == 40);

    DvFree(dv);
    printf("\tTest 3 passed!\n");
}

/**
 * Test hunter and immature vampire encounter
 */
static void testDvGetHealth4()
{
    char *trail = "GSW.... SLS.... HMR.... MJM.... DSJ.V.."
                  "GSW.... SLS.... HMR.... MJM.... DBET..."
                  "GSW.... SLS.... HMR.... MJM.... DKLT..."
                  "GSW.... SLS.... HMR.... MJM.... DBCT..."
                  "GSW.... SLS.... HMR.... MJM.... DSOT..."
                  "GSW.... SLS.... HMR.... MSJV... DSAT..."
                  "GSW.... SLS.... HMR.... MJM.... DVAT...";
    Message messages[] = {};
    DraculaView dv = DvNew(trail, messages);

    assert(DvGetHealth(dv, PLAYER_LORD_GODALMING) == 9);
    assert(DvGetHealth(dv, PLAYER_DR_SEWARD) == 9);
    assert(DvGetHealth(dv, PLAYER_VAN_HELSING) == 9);
    assert(DvGetHealth(dv, PLAYER_MINA_HARKER) == 9);
    assert(DvGetHealth(dv, PLAYER_DRACULA) == 40);

    DvFree(dv);
    printf("\tTest 4 passed!\n");
}

/**
 * Test dracula at sea
 */
static void testDvGetHealth5()
{
    char *trail = "GSW.... SLS.... HMR.... MJM.... DCN.V.."
                  "GSW.... SLS.... HMR.... MJM.... DBS....";
    Message messages[] = {};
    DraculaView dv = DvNew(trail, messages);

    assert(DvGetHealth(dv, PLAYER_LORD_GODALMING) == 9);
    assert(DvGetHealth(dv, PLAYER_DR_SEWARD) == 9);
    assert(DvGetHealth(dv, PLAYER_VAN_HELSING) == 9);
    assert(DvGetHealth(dv, PLAYER_MINA_HARKER) == 9);
    assert(DvGetHealth(dv, PLAYER_DRACULA) == 38);

    DvFree(dv);
    printf("\tTest 5 passed!\n");
}

/**
 * Test large number of rounds
 */
static void testDvGetHealth6()
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
    DraculaView dv = DvNew(trail, messages);

    assert(DvGetHealth(dv, PLAYER_LORD_GODALMING) == 9);
    assert(DvGetHealth(dv, PLAYER_DR_SEWARD) == 3);
    assert(DvGetHealth(dv, PLAYER_VAN_HELSING) == 8);
    assert(DvGetHealth(dv, PLAYER_MINA_HARKER) == 0);
    assert(DvGetHealth(dv, PLAYER_DRACULA) == 0);

    DvFree(dv);
    printf("\tTest 6 passed!\n");
}
