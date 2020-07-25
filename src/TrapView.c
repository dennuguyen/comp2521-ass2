/**
 * TrapView ADT is implemented to utilise getters and have queue implementation.
 */

#include <stdio.h>

#include "Game.h"
#include "TrapView.h"

typedef struct trapNode
{
    PlaceId location;
    bool isVampire;
    TrapNode next;
} trapNode;

typedef struct trapView
{
    TrapNode head;
    TrapNode tail;
} trapView;

static TrapNode TvNewNode(PlaceId location, bool isVampire)
{
    TrapNode new = malloc(sizeof(trapNode));
    if (new == NULL)
    {
        fprintf(stderr, "ERROR: Could not allocate memory for TrapNode\n");
        exit(1);
    }

    new->location = location;
    new->isVampire = isVampire;
    new->next = NULL;

    return new;
}

/**
 * Create queue.
 */
TrapView TvNew()
{
    TrapView new = malloc(sizeof(trapView));
    if (new == NULL)
    {
        fprintf(stderr, "ERROR: could not allocate memory for TrapView\n");
        exit(1);
    }

    new->head = new->tail = NULL;

    return new;
}

/**
 * Free queue.
 */
void TvFree(TrapView q)
{
    if (q == NULL || q->head == NULL)
        return;

    TrapNode curr = q->head;
    while (curr != NULL)
    {
        TrapNode next = curr->next;
        free(curr);
        curr = next;
    }

    free(q);
}

/**
 * Enqueue a trap to the queue given location and isVampire arguments.
 */
void TvEnqueue(TrapView q, PlaceId location, bool isVampire)
{
    if (q == NULL || q->head == NULL)
        return;

    TrapNode head = TvNewNode(location, isVampire);

    if (q->head == NULL)
        q->head = head;
    if (q->tail != NULL)
        q->tail->next = head;
    q->tail = head;
}

/**
 * Dequere a trap from the queue.
 */
TrapNode TvDequeue(TrapView q)
{
    if (q == NULL || q->head == NULL)
        return NULL;

    TrapNode temp = q->head;
    TrapNode node = &(trapNode){.location = temp->location, .isVampire = temp->isVampire};
    q->head = q->head->next;

    if (q->head == NULL)
        q->tail = NULL;

    free(temp);

    return node;
}

/**
 * Removes a trap from the queue. If there exists multiple traps with the same
 * location, the oldest trap is removed.
 */
TrapNode TvRemove(TrapView q, PlaceId location)
{
    if (q == NULL || q->head == NULL)
        return NULL;

    TrapNode prev = NULL, curr = q->head;
    while (curr->next != NULL)
    {
        if (curr->location == location)
        {
            TrapNode node = &(trapNode){.location = curr->location, .isVampire = curr->isVampire};
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
 * Check if TrapView is empty.
 */
bool TvIsEmpty(TrapView q)
{
    return q->head == NULL;
}

/**
 * Show the queue.
 */
void TvShow(TrapView q)
{
    if (q == NULL || q->head == NULL)
        return;

    printf("[");

    TrapNode curr = q->head;
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
 * Get the trap locations from queue. This excludes the vampire location.
 */
PlaceId *TvGetTrapLocations(TrapView q, int *numTraps)
{
    *numTraps = 1;
    PlaceId *trapArray = malloc(TRAIL_SIZE * sizeof(int));

    if (q == NULL || q->head == NULL)
    {
        trapArray[0] = NOWHERE;
        return trapArray;
    }

    TrapNode curr = q->head;
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
PlaceId TvGetVampireLocation(TrapView q)
{
    if (q == NULL || q->head == NULL)
        return NOWHERE;

    TrapNode curr = q->head;
    while (curr != NULL)
    {
        if (curr->isVampire == true && placeIsReal(curr->location))
            return curr->location;
        curr = curr->next;
    }

    return NOWHERE;
}
