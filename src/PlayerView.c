/**
 * PlayerView ADT.
 */

#include <stdio.h>

#include "Game.h"
#include "PlayerView.h"

PlayerView PvNew(Player player)
{
    PlayerView new = malloc(sizeof(playerView));
    if (new == NULL)
    {
        fprintf(stderr, "ERROR: Could not allocate memory for PlayerView\n");
        exit(EXIT_FAILURE);
    }

    new->player = player;
    new->moveHistory = NULL;
    new->locationHistory = NULL;

    if (player == PLAYER_DRACULA)
        new->health = GAME_START_BLOOD_POINTS;
    else
        new->health = GAME_START_HUNTER_LIFE_POINTS;

    return new;
}

void PvFree(PlayerView pv)
{
    if (pv == NULL)
        return;

    free(pv->moveHistory);
    free(pv->locationHistory);
    free(pv);
}
