/**
 * PlayerView ADT with dynamic array implementation.
 * 
 * Declaration of playerView struct is public for ease of implementation of
 * GameView ADT and separation of PvNew and PvFree functions from GameView.c.
 */

#ifndef FOD__PLAYER_VIEW_H_
#define FOD__PLAYER_VIEW_H_

#include <stdbool.h>

#include "Places.h"

#define ARRAY_SIZE 128

typedef struct playerView *PlayerView;

/* Dynamic Array ADT */
PlayerView PvNew(Player player);
void PvFree(PlayerView pv);

/* Getters */
Player PvGetPlayer(PlayerView pv);
int PvGetHealth(PlayerView pv);
PlaceId *PvGetMoves(PlayerView pv, int numMoves, int *numReturnedMoves, bool *canFree);
PlaceId *PvGetLocations(PlayerView pv, int numLocs, int *numReturnedLocs, bool *canFree);
PlaceId PvGetLastKnownDracula(PlayerView pv);

#endif // FOD__PLAYER_VIEW_H_
