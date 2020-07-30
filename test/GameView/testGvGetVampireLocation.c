#include "testGameView.h"

static void testGvGetVampireLocation1();
static void testGvGetVampireLocation2();
static void testGvGetVampireLocation3();
static void testGvGetVampireLocation4();
static void testGvGetVampireLocation5();
static void testGvGetVampireLocation6();

void testGvGetVampireLocation()
{
    printf("Testing GvGetVampireLocation...\n");

    testGvGetVampireLocation1();
    testGvGetVampireLocation2();
    testGvGetVampireLocation3();
    testGvGetVampireLocation4();
    testGvGetVampireLocation5();
    testGvGetVampireLocation6();

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
        "GED.... SGE.... HZU.... MCA.... DCF.V.. "
        "GMN.... SGE.... HGE.... MLS.... DTOT...";
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
        "GED.... SGE.... HZU.... MCA.... DCF.V.. "
        "GMN.... SCFVD.. HGE.... MLS.... DTOT...";

    Message messages[] = {};
    GameView gv = GvNew(trail, messages);
    assert(GvGetVampireLocation(gv) == NOWHERE);
    GvFree(gv);
    printf("\tTest 4 passed!\n");
}

/**
 * Test vampire discovered by research
 */
static void testGvGetVampireLocation5()
{
    char *trail = 
        "GSW.... SLS.... HMR.... MLO.... DSJ.V.. "
        "GSW.... SLS.... HMR.... MMN.... DBET... "
        "GSW.... SLS.... HMR.... MLO.... DKLT... "
        "GSW.... SLS.... HMR.... MMN.... DBCT... "
        "GSW.... SLS.... HMR.... MLO.... DGAT... "
        "GSW.... SLS.... HMR.... MMN.... DCNT... "
        "GSW.... SLS.... HMR.... MMN....";

    Message messages[] = {};
    GameView gv = GvNew(trail, messages);
    
    assert(GvGetVampireLocation(gv) == SARAJEVO);
    GvFree(gv);
    printf("\tTest 5 passed!\n");
}

/**
 * Test no vampire after maturing
 */
static void testGvGetVampireLocation6()
{
    char *trail = 
        "GSW.... SLS.... HMR.... MLO.... DSJ.V.. "
        "GSW.... SLS.... HMR.... MMN.... DBET... "
        "GSW.... SLS.... HMR.... MLO.... DKLT... "
        "GSW.... SLS.... HMR.... MMN.... DBIT... "
        "GSW.... SLS.... HMR.... MLO.... DGAT... "
        "GSW.... SLS.... HMR.... MMN.... DCNT... "
        "GSW.... SLS.... HMR.... MLO.... DVRT...";

    Message messages[] = {};
    GameView gv = GvNew(trail, messages);
    
    assert(GvGetVampireLocation(gv) == NOWHERE);
    GvFree(gv);
    printf("\tTest 6 passed!\n");
}
