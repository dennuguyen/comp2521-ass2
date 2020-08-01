########################################################################
# COMP2521 20T2 // the Fury of Dracula // the View
# view/Makefile: build tests for GameView/HunterView/DraculaView
#
# You can modify this if you add additional files
#
# 2018-12-31	v1.0	Team Dracula <cs2521@cse.unsw.edu.au>
# 2020-07-10    v2.0    Team Dracula <cs2521@cse.unsw.edu.au>
#
########################################################################

# Author: Dan Nguyen (z5206032)

CC = gcc
CFLAGS = -Wall -Werror -g
BINS = testGameView testHunterView testDraculaView testMap
DEP = Game.h Map.c Map.h Places.c Places.h testUtils.c testUtils.h
GAME = GameView.c GameView.h
HUNTER = HunterView.c HunterView.h
DRACULA = DraculaView.c DraculaView.h
TEST_GAME = testGameView.c testGameView.h $(wildcard testGv*.c)
TEST_HUNTER = testHunterView.c testHunterView.h $(wildcard testHv*.c)
TEST_DRACULA = testDraculaView.c testDraculaView.h $(wildcard testDv*.c)
MAP = testMap.c

all: $(BINS)

.PHONY: testGameView testHunterView testDraculaView show clean

testGameView:
	$(CC) -o testGameView $(TEST_GAME) $(GAME) $(DEP)

testHunterView:
	$(CC) -o testHunterView $(TEST_HUNTER) $(GAME) $(HUNTER) $(DEP)

testDraculaView:
	$(CC) -o testDraculaView $(TEST_DRACULA) $(GAME) $(DRACULA) $(DEP)

testMap:
	$(CC) -o testMap $(MAP) $(DEP)

show:
	@echo "$(wildcard testGv*.c)"

clean:
	-rm -f ${BINS} *.o core
