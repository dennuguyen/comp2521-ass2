#ifndef FOD__TEST_DRACULA_VIEW_H_
#define FOD__TEST_DRACULA_VIEW_H_

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DraculaView.h"
#include "Game.h"
#include "Places.h"
#include "testUtils.h"

// Unit Testing
void testDvNew();
void testDvFree();
void testDvGetRound();
void testDvGetScore();
void testDvGetHealth();
void testDvGetPlayerLocation();
void testDvGetVampireLocation();
void testDvGetTrapLocations();
void testDvWhereCanIGo();
void testDvWhereCanIGoByType();
void testDvWhereCanTheyGo();
void testDvWhereCanTheyGoByType();

// Integration Testing
void testDv();

#endif // FOD__TEST_DRACULA_VIEW_H_