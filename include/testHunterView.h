#ifndef FOD__TEST_HUNTER_VIEW_H_
#define FOD__TEST_HUNTER_VIEW_H_

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HunterView.h"
#include "Game.h"
#include "Places.h"
#include "testUtils.h"

// Unit Testing
void testHvNew();
void testHvFree();
void testHvGetRound();
void testHvGetPlayer();
void testHvGetScore();
void testHvGetHealth();
void testHvGetPlayerLocation();
void testHvWhereCanIGo();
void testHvWhereCanIGoByType();
void testHvWhereCanTheyGo();
void testHvWhereCanTheyGoByType();

// Integration Testing
void testHv();

#endif // FOD__TEST_HUNTER_VIEW_H_