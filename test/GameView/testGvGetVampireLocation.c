#include "testGameView.h"

static void testGvGetVampireLocation1();
static void testGvGetVampireLocation2();
static void testGvGetVampireLocation3();
static void testGvGetVampireLocation4();
static void testGvGetVampireLocation5();

void testGvGetPlayerLocation()
{
    printf("Testing GvGetVampireLocation...\n");

    testGvGetVampireLocation1();
    testGvGetVampireLocation2();
    testGvGetVampireLocation3();
    testGvGetVampireLocation4();
    testGvGetVampireLocation5();

    printf("GvGetVampireLocation tests passed!\n\n");
}

/**
 * Test initialisation on empty string
 */
static void testGvGetVampireLocation1()
{
    char *trail = "";
    Message messages[] = {};
    GameView gv = GvNew(trail, messages);

    assert(GvGetVampireLocation(gv) == NOWHERE);
    GvFree(gv);
    printf("\tTest 1 passed!\n");
}

/**
 * Test no vampire placed yet
 */
static void testGvGetVampireLocation2()
{
    char *trail = "GSW.... SLS....";
    Message messages[] = {};
    GameView gv = GvNew(trail, messages);

    assert(GvGetVampireLocation(gv) == NOWHERE);
    GvFree(gv);
    printf("\tTest 2 passed!\n");
}
 */

/**
 * Test vampire not encountered yet
 */
static void testGvGetVampireLocation3()
{
    char *trail = 
        "GSW.... SLS.... HMR.... MHA.... DSJ.V.. "
        "GLO.... SSJ.... HCO.... MBR.... DBET...";
    Message messages[] = {};
    GameView gv = GvNew(trail, messages);

    assert(GvGetVampireLocation(gv) == CITY_UNKNOWN);
    GvFree(gv);
    printf("\tTest 3 passed!\n");
}

/**
 * Test vampire encountered
 */
static void testGvGetVampireLocation4()
{
    char *trail = 
        "GSW.... SLS.... HMR.... MHA.... DSJ.V.. "
        "GSJVD.. SSJ.... HCO.... MBR.... DBET...";

    Message messages[] = {};
    GameView gv = GvNew(trail, messages);
    assert(GvGetVampireLocation1(gv) == NOWHERE);
    GvFree(gv);
    printf("\tTest 4 passed!\n");
}

/**
 * Test vampire discovered by research
 */
static void testGvGetPlayerLocation5()
{
    char *trail = 
        "GSW.... SLS.... HMR.... MHA.... DSJ.V.. "
        "GLO.... SAL.... HCO.... MBR.... DBET... "
        "GED.... SBO.... HLI.... MPR.... DKLT... "
        "GIR.... SPA.... HPR.... MDU.... DHIT... "
        "GAO.... SST.... HSZ.... MCO.... DGAT... "
        "GMS.... SFL.... HMA.... MSZ.... DCNT... "
        "GMS.... SFL.... HMA.... MSZ....";

    Message messages[] = {};
    GameView gv = GvNew(trail, messages);
    
    assert(GvGetVampireLocation1(gv) == SARAJEVO);
    GvFree(gv);
    printf("\tTest 5 passed!\n");
}

/**
 * Test no vampire after maturing
 */
static void testGvGetPlayerLocation6()
{
    char *trail = 
        "GSW.... SLS.... HMR.... MHA.... DSJ.V.. "
        "GLO.... SAL.... HCO.... MBR.... DBET... "
        "GED.... SBO.... HLI.... MPR.... DKLT... "
        "GIR.... SPA.... HPR.... MDU.... DHIT... "
        "GAO.... SST.... HSZ.... MCO.... DGAT... "
        "GMS.... SFL.... HMA.... MSZ.... DCNT... "
        "GIO.... SIO.... HBD.... MLI.... DECT... "
        "GBD.... SMN.... HMU.... MBC.... DSOT...";

    Message messages[] = {};
    GameView gv = GvNew(trail, messages);
    
    assert(GvGetVampireLocation1(gv) == NOWHERE);
    GvFree(gv);
    printf("\tTest 5 passed!\n");
}
