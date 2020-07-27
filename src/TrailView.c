/**
 * TrailView ADT is implemented to utilise getters and have queue implementation.
 */

#include <stdio.h>

#include "Game.h"
#include "TrailView.h"

typedef struct trailNode
{
    PlaceId location;
    bool isVampire;
    bool isEncountered;
    bool isResearched;
    TrailNode next;
} trailNode;

typedef struct trailView
{
    TrailNode head;
    TrailNode tail;
} trailView;

/**
 * Create TrailNode.
 */
static TrailNode TvNewNode(PlaceId location, bool isVampire)
{
    TrailNode new = malloc(sizeof(trailNode));
    if (new == NULL)
    {
        fprintf(stderr, "ERROR: Could not allocate memory for TrailNode\n");
        exit(1);
    }

    new->location = location;
    new->isVampire = isVampire;
    new->next = NULL;

    return new;
}

/**
 * Create new TrailView.
 */
TrailView TvNew()
{
    TrailView new = malloc(sizeof(trailView));
    if (new == NULL)
    {
        fprintf(stderr, "ERROR: could not allocate memory for TrailView\n");
        exit(1);
    }

    new->head = new->tail = NULL;

    return new;
}

/**
 * Free TrailView and TrapNodes.
 */
void TvFree(TrailView q)
{
    if (q == NULL || q->head == NULL)
        return;

    TrailNode curr = q->head;
    while (curr != NULL)
    {
        TrailNode next = curr->next;
        free(curr);
        curr = next;
    }

    free(q);
}

/**
 * Enqueue a trail to the queue given location and isVampire arguments.
 */
void TvEnqueue(TrailView q, PlaceId location, bool isVampire)
{
    if (q == NULL || q->head == NULL)
        return;

    TrailNode head = TvNewNode(location, isVampire);

    if (q->head == NULL)
        q->head = head;
    if (q->tail != NULL)
        q->tail->next = head;
    q->tail = head;
}

/**
 * Dequere a trail from the queue.
 */
TrailNode TvDequeue(TrailView q)
{
    if (q == NULL || q->head == NULL)
        return NULL;

    TrailNode temp = q->head;
    TrailNode node = &(trailNode){.location = temp->location, .isVampire = temp->isVampire};
    q->head = q->head->next;

    if (q->head == NULL)
        q->tail = NULL;

    free(temp);

    return node;
}

/**
 * Removes a trail from the queue. If there exists multiple traps with the same
 * location, the oldest trail is removed.
 */
TrailNode TvRemove(TrailView q, PlaceId location)
{
    if (q == NULL || q->head == NULL)
        return NULL;

    TrailNode prev = NULL, curr = q->head;
    while (curr->next != NULL)
    {
        if (curr->location == location)
        {
            TrailNode node = &(trailNode){.location = curr->location, .isVampire = curr->isVampire};
            prev->next = NULL;
            free(curr);
            return node;
        }
        prev = curr;
        curr = curr->next;
    }

    return NULL;
}

/**
 * Check if TrailView is empty.
 */
bool TvIsEmpty(TrailView q)
{
    return q->head == NULL;
}

/**
 * Show the queue.
 */
void TvShow(TrailView q)
{
    if (q == NULL || q->head == NULL)
        return;

    printf("[");

    TrailNode curr = q->head;
    while (curr != NULL)
    {
        if (curr->next == NULL)
            printf("{%d, %d}", curr->location, curr->isVampire);
        else
            printf("{%d, %d}, ", curr->location, curr->isVampire);
        curr = curr->next;
    }

    printf("]");
}

/**
 * Get the trail locations from queue. This excludes the vampire location.
 */
PlaceId *TvGetTrailLocations(TrailView q, int *numTraps)
{
    *numTraps = 0;
    PlaceId *trapArray = malloc(TRAIL_SIZE * sizeof(int));

    if (q == NULL || q->head == NULL)
    {
        trapArray[0] = NOWHERE;
        return trapArray;
    }

    TrailNode curr = q->head;
    for (int i = 0; curr != NULL; i++)
    {
        if (!curr->isVampire)
            trapArray[i] = curr->location;

        numTraps++; // increment number of traps
        curr = curr->next;
    }

    return trapArray;
}

/**
 * Get the vampire location from queue.
 */
PlaceId TvGetVampireLocation(TrailView q)
{
    if (q == NULL || q->head == NULL)
        return NOWHERE;

    TrailNode curr = q->head;
    while (curr != NULL)
    {
        if (curr->isVampire == true && placeIsReal(curr->location))
            return curr->location;
        curr = curr->next;
    }

    return NOWHERE;
}
