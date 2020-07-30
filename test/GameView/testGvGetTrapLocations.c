#include "testGameView.h"

static void testGvGetTrapLocations1();
static void testGvGetTrapLocations2();
static void testGvGetTrapLocations3();
static void testGvGetTrapLocations4();
static void testGvGetTrapLocations5();
static void testGvGetTrapLocations6();

void testGvGetTrapLocations()
{
    printf("Testing GvGetTrapLocations...\n");

    testGvGetTrapLocations1();
    testGvGetTrapLocations2();
    testGvGetTrapLocations3();
    testGvGetTrapLocations4();
    testGvGetTrapLocations5();
    testGvGetTrapLocations6();

    printf("GvGetTrapLocations tests passed!\n\n");
}

/**
 * Test initialisation on empty string
 */
static void testGvGetTrapLocations1()
{
    char *trail = "";
    Message messages[] = {};
    GameView gv = GvNew(trail, messages);

    int numTraps = 0;
    PlaceId *traps = GvGetTrapLocations(gv, &numTraps);
    assert(numTraps == 0);
    sortPlaces(traps, numTraps);
    assert(traps[0] == NOWHERE);
    free(traps);

    GvFree(gv);
    printf("\tTest 1 passed!\n");
}

/**
 * Test no trap placed yet
 */
static void testGvGetTrapLocations2()
{
    char *trail = "GSW.... SLS....";
    Message messages[] = {};
    GameView gv = GvNew(trail, messages);

    int numTraps = 0;
    PlaceId *traps = GvGetTrapLocations(gv, &numTraps);
    assert(numTraps == 0);
    sortPlaces(traps, numTraps);
    assert(traps[0] == NOWHERE);
    free(traps);

    GvFree(gv);
    printf("\tTest 2 passed!\n");
}

/**
 * Test trap not encountered yet
 */
static void testGvGetTrapLocations3()
{
    char *trail = "GSW.... SLS.... HMR.... MLO.... DSJ.V.. "
                  "GSW.... SLS.... HMR.... MMN.... DBET... "
                  "GSW.... SLS.... HMR.... MLO.... DKLT...";

    Message messages[] = {};
    GameView gv = GvNew(trail, messages);

    int numTraps = 0;
    PlaceId *traps = GvGetTrapLocations(gv, &numTraps);
    assert(numTraps == 2);
    sortPlaces(traps, numTraps);
    assert(traps[0] == BELGRADE);
    assert(traps[1] == KLAUSENBURG);
    free(traps);

    GvFree(gv);
    printf("\tTest 3 passed!\n");
}

/**
 * Test trap encounter
 */
static void testGvGetTrapLocations4()
{
    char *trail = "GSW.... SLS.... HMR.... MZA.... DSJ.V.. "
                  "GSW.... SLS.... HMR.... MJM.... DBET... "
                  "GSW.... SLS.... HMR.... MBETD.. DKLT...";

    Message messages[] = {};
    GameView gv = GvNew(trail, messages);

    int numTraps = 0;
    PlaceId *traps = GvGetTrapLocations(gv, &numTraps);
    assert(numTraps == 1);
    sortPlaces(traps, numTraps);
    assert(traps[0] == KLAUSENBURG);
    free(traps);

    GvFree(gv);
    printf("\tTest 4 passed!\n");
}

/**
 * Test trap malfunction
 */
static void testGvGetTrapLocations5()
{
    char *trail = "GSW.... SLS.... HMR.... MLO.... DSJ.V.. "
                  "GSW.... SLS.... HMR.... MMN.... DBET... "
                  "GSW.... SLS.... HMR.... MLO.... DKLT... "
                  "GSW.... SLS.... HMR.... MMN.... DBCT... "
                  "GSW.... SLS.... HMR.... MLO.... DGAT... "
                  "GSW.... SLS.... HMR.... MMN.... DCNT... "
                  "GSW.... SLS.... HMR.... MLO.... DVRT.V. "
                  "GSW.... SLS.... HMR.... MLO.... DSOT.M.";

    Message messages[] = {};
    GameView gv = GvNew(trail, messages);

    int numTraps = 0;
    PlaceId *traps = GvGetTrapLocations(gv, &numTraps);
    assert(numTraps == 6);
    sortPlaces(traps, numTraps);
    assert(traps[0] == BUCHAREST);
    assert(traps[1] == CONSTANTA);
    assert(traps[2] == GALATZ);
    assert(traps[3] == KLAUSENBURG);
    assert(traps[4] == SOFIA);
    assert(traps[5] == VARNA);
    free(traps);

    GvFree(gv);
    printf("\tTest 5 passed!\n");
}

/**
 * Test long game
 */
static void testGvGetTrapLocations6()
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

    int numTraps = 0;
    PlaceId *traps = GvGetTrapLocations(gv, &numTraps);
    printf("numTraps: %d\n", numTraps);
    for (int i = 0; i < 6; i++)
        printf("%s\n", placeIdToName(traps[i]));
    assert(numTraps == 5);
    sortPlaces(traps, numTraps);
    assert(traps[0] == BUCHAREST);
    assert(traps[1] == CASTLE_DRACULA);
    assert(traps[3] == KLAUSENBURG);
    assert(traps[4] == SOFIA);
    free(traps);

    GvFree(gv);
    printf("\tTest 6 passed!\n");
}