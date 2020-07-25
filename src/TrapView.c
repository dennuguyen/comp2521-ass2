/**
 * TrapView ADT is implemented to utilise getters and have queue implementation.
 */

#include <stdio.h>

#include "TrapView.h"

typedef struct trapView
{
    PlaceId location;
    bool isVampire;
    TrapView next;
} trapView;

/**
 * Get the trap locations from queue.
 * 
 * Example Usage: PlaceId *locations = TvGetTrapLocations(&q, numTraps);
 */
PlaceId *TvGetTrapLocations(TrapView *q, int *numTraps)
{
    *numTraps = 0;

    PlaceId *trapArray = malloc(6 * sizeof(int));
    TrapView curr = *q;
    for (int i = 0; curr != NULL; i++)
    {
        if (!curr->isVampire)
            trapArray[i] = curr->location;
        *numTraps++; // increment number of traps
    }
    return trapArray;
}

/**
 * Get the vampire location from queue.
 * 
 * Example Usage: PlaceId location = TvGetVampireLocation(&q);
 */
PlaceId TvGetVampireLocation(TrapView *q)
{
    if (*q == NULL)
        return;

    TrapView curr = *q;
    while (curr != NULL)
    {
        if (curr->isVampire == true && placeIsReal(curr->location))
            return curr->location;
        curr = curr->next;
    }

    return NOWHERE;
}

/**
 * Create a new queue.
 * 
 * Example Usage: TrapView q = TvNew();
 */
TrapView TvNew()
{
    return NULL;
}

/**
 * Free queue.
 * 
 * Example Usage: TvFree(&q);
 */
void TvFree(TrapView *q)
{
    if (*q == NULL)
        return;
    QueueFree(&((*q)->next));
    free(*q);
    *q = NULL;
}

/**
 * Push a trap into the queue. TvEnqueue takes a queue, location and isVampire
 * arguments.
 * 
 * Example Usage: TvEnqueue(&q, 2, true);
 */
void TvEnqueue(TrapView *q, PlaceId *location, bool isVampire)
{
    TrapView head = malloc(sizeof(trapView));

    if (head == NULL)
    {
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(1);
    }

    head->location = location;
    head->isVampire = isVampire;
    head->next = *q;
    *q = head;
}

/**
 * Pops a trap from the queue.
 * 
 * Example Usage: TrapView popped = TvDequeue(&q);
 */
TrapView TvDequeue(TrapView *q)
{
    if (*q == NULL)
        return NULL;

    TrapView prev = NULL, curr = *q;
    while (curr->next != NULL)
    {
        prev = curr;
        curr = curr->next;
    }

    TrapView temp = curr;
    if (prev == NULL)
        TvFree(q);
    else
    {
        prev->next = NULL;
        free(curr);
    }

    return temp;
}

/**
 * Removes a trap from the queue. If there exists multiple traps with the same
 * location, the oldest trap is removed.
 * 
 * Example Usage: TrapView removed = TvRemove(&q, 2);
 */
TrapView TvRemove(TrapView *q, PlaceId *location)
{
    if (*q == NULL)
        return;

    TrapView prev = NULL, curr = *q;
    while (curr->next != NULL)
    {
        if (curr->location == location)
        {
            TrapView temp = curr;
            prev->next = NULL;
            free(curr);
            return temp;
        }
        prev = curr;
        curr = curr->next;
    }

    return NULL;
}

/**
 * Check if queue is empty
 * 
 * Example Usage: bool flag = TvIsEmpty(q);
 */
bool TvIsEmpty(TrapView q)
{
    return q == NULL;
}

/**
 * Show the queue.
 * 
 * Example Usage: TvShow(&q);
 */
void TvShow(TrapView *q)
{
    if (*q == NULL)
        return;

    printf("[");

    TrapView curr = *q;
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
