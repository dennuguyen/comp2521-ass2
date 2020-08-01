#include "testHunterView.h"

static void testHvGetLastKnownDraculaLocation1();
static void testHvGetLastKnownDraculaLocation2();
static void testHvGetLastKnownDraculaLocation3();
static void testHvGetLastKnownDraculaLocation4();

void testHvGetLastKnownDraculaLocation()
{
    printf("Testing HvGetLastKnownDraculaLocation1...\n");

    testHvGetLastKnownDraculaLocation1();
    testHvGetLastKnownDraculaLocation2();
    testHvGetLastKnownDraculaLocation3();
    testHvGetLastKnownDraculaLocation4();

    printf("HvGetLastKnownDraculaLocation1 tests passed!\n\n");
}

/**
 * Test initialisation on empty string
 */
static void testHvGetLastKnownDraculaLocation1()
{
    char *trail = "";
    Message messages[] = {};
    HunterView hv = HvNew(trail, messages);
    int round = 0;

    assert(HvGetLastKnownDraculaLocation(hv, &round) == NOWHERE);
    assert(round == 0);

    HvFree(hv);
    printf("\tTest 1 passed!\n");
}

/**
 * Test string with known Dracula location
 */
static void testHvGetLastKnownDraculaLocation2()
{
    char *trail = "GED.... SGE.... HZU.... MCA.... DCF.V.. "
                  "GMN.... SCFVD.. HGE.... MLS.... DBOT...";
    Message messages[] = {};
    HunterView hv = HvNew(trail, messages);
    int round = 0;

    assert(HvGetLastKnownDraculaLocation(hv, &round) == BORDEAUX);
    assert(round == 1);

    HvFree(hv);
    printf("\tTest 2 passed!\n");
}

/**
 * Test string with unknown Dracula location
 */
static void testHvGetLastKnownDraculaLocation3()
{
    char *trail = "GMN.... SPL.... HAM.... MPA.... DC?.V.. "
                  "GLV.... SLO.... HNS.... MST.... DC?T...";
    Message messages[] = {};
    HunterView hv = HvNew(trail, messages);
    int round = 0;

    assert(HvGetLastKnownDraculaLocation(hv, &round) == NOWHERE);
    assert(round == 0);

    HvFree(hv);
    printf("\tTest 3 passed!\n");
}

/**
 * Test mixed string
 */
static void testHvGetLastKnownDraculaLocation4()
{
    char *trail = "GED.... SGE.... HZU.... MCA.... DCF.V.. "
                  "GMN.... SCFVD.. HGE.... MLS.... DBOT... "
                  "GLO.... SMR.... HCF.... MMA.... DC?T... "
                  "GPL.... SMS.... HMR.... MGR.... DBAT... "
                  "GLO.... SBATD.. HMS.... MMA.... DC?T... "
                  "GPL.... SSJ.... HBA.... MGR.... DC?T... "
                  "GPL.... SSJ.... HBA.... MGR.... DC?T...";
    Message messages[] = {};
    HunterView hv = HvNew(trail, messages);
    int round = 0;

    assert(HvGetLastKnownDraculaLocation(hv, &round) == BARCELONA);
    assert(round == 3);

    HvFree(hv);
    printf("\tTest 4 passed!\n");
}
