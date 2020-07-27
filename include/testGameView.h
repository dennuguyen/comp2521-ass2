#ifndef FOD__TEST_GAME_VIEW_H_
#define FOD__TEST_GAME_VIEW_H_

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Game.h"
#include "GameView.h"
#include "Places.h"
#include "testUtils.h"

// Unit Testing
void testGvNew();
void testGvFree();
void testGvGetRound();
void testGvGetPlayer();
void testGvGetScore();
void testGvGetHealth();

// Integration Testing
void testGv();

#endif // FOD__TEST_GAME_VIEW_H_