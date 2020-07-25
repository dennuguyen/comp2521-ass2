/**
 * PlayerView ADT.
 * 
 * Declaration of playerView struct is public for ease of implementation of
 * GameView ADT and separation of PvNew and PvFree functions from GameView.c.
 */

#ifndef FOD__PLAYER_VIEW_H_
#define FOD__PLAYER_VIEW_H_

#include <stdbool.h>

#include "Places.h"

typedef struct playerView *PlayerView;

typedef struct playerView
{
    Player player;
    int health;
    PlaceId *moveHistory;
    PlaceId *locationHistory;
    PlaceId lastKnownDraculaLocation;
} playerView;

PlayerView PvNew(Player player);
void PvFree(PlayerView pv);

#endif // FOD__PLAYER_VIEW_H_
