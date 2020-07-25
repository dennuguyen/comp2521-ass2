/**
 * PlayerView ADT.
 */

#include <stdio.h>

#include "Game.h"
#include "PlayerView.h"

typedef struct array *Array;

typedef struct array
{
    PlaceId *history;
    size_t used;
    size_t size;
} array;

typedef struct playerView
{
    Player player;
    int health;
    Array moveHistory;
    PlaceId lastKnownDraculaLocation;
} playerView;

/**
 * Create new Array.
 */
static Array PvNewArray(size_t size)
{
    Array new = malloc(sizeof(array));
    if (new == NULL)
    {
        fprintf(stderr, "ERROR: Could not allocate memory for Array\n");
        exit(EXIT_FAILURE);
    }

    new->history = malloc(size * sizeof(PlaceId));
    if (new->history == NULL)
    {
        fprintf(stderr, "ERROR: Could not allocate memory for PlaceId* history\n");
        exit(EXIT_FAILURE);
    }

    new->history[0] = NOWHERE;
    new->used = 0;
    new->size = size;

    return new;
}

/**
 * Insert a place into an Array.
 */
// static void PvInsertArray(Array arr, PlaceId place)
// {
//     if (arr->used == arr->size)
//     {
//         arr->size += ARRAY_SIZE;
//         arr->history = realloc(arr->history, arr->size * sizeof(PlaceId));
//     }

//     arr->history[arr->used++] = place;
// }

/**
 * Create new PlayerView.
 */
PlayerView PvNew(Player player)
{
    PlayerView new = malloc(sizeof(playerView));
    if (new == NULL)
    {
        fprintf(stderr, "ERROR: Could not allocate memory for PlayerView\n");
        exit(EXIT_FAILURE);
    }

    new->player = player;
    new->moveHistory = PvNewArray(ARRAY_SIZE);

    if (player == PLAYER_DRACULA)
        new->health = GAME_START_BLOOD_POINTS;
    else
        new->health = GAME_START_HUNTER_LIFE_POINTS;

    return new;
}

/**
 * Free PlayerView and Array.
 */
void PvFree(PlayerView pv)
{
    if (pv == NULL)
        return;

    free(pv->moveHistory->history);
    free(pv->moveHistory);
    free(pv);
}

/**
 * Returns Player.
 */
Player PvGetPlayer(PlayerView pv)
{
    return pv->player;
}

/**
 * Returns health.
 */
int PvGetHealth(PlayerView pv)
{
    return pv->health;
}

/**
 * Return last numMoves moves.
 */
PlaceId *PvGetMoves(PlayerView pv, int numMoves, int *numReturnedMoves, bool *canFree)
{
}

/**
 * Return last numLoc locations.
 */
PlaceId *PvGetLocations(PlayerView pv, int numLocs, int *numReturnedLocs, bool *canFree)
{
}

/**
 * Return last known dracula location.
 */
PlaceId PvGetLastKnownDracula(PlayerView pv)
{
    return pv->lastKnownDraculaLocation;
}
