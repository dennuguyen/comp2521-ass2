/**
 * TrailView ADT is implemented to utilise getters and have queue implementation.
 */

#include <stdio.h>

#include "Game.h"
#include "Queue.h"

typedef struct QueueNode
{
    PlaceId location;
    struct QueueNode *next;
} QueueNode;

typedef struct QueueView
{
	QueueNode *head; // ptr to first node
	QueueNode *tail; // ptr to last node
} QueueView;

/**
 * Create TrailNode.
 */
static QueueNode NewNode(PlaceId location)
{
    QueueNode new = malloc(sizeof(QueueNode));
    if (new == NULL)
    {
        fprintf(stderr, "ERROR: Could not allocate memory for TrailNode\n");
        exit(1);
    }

    new->location = location;
    new->next = NULL;

    return new;
}

/**
 * Create new TrailView.
 */
QueueView QueueNew()
{
    QueueView new = malloc(sizeof(QueueView));
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
void QueueFree(QueueView q)
{
    if (q == NULL || q->head == NULL)
        return;

    QueueNode curr = q->head;
    while (curr != NULL)
    {
        QueueNode next = curr->next;
        free(curr);
        curr = next;
    }

    free(q);
}

/**
 * Enqueue a trail to the queue given location and isVampire arguments.
 */
void Enqueue(TrailView q, PlaceId location)
{
    if (q == NULL || q->head == NULL)
        return;

    TrailNode head = NewNode(location);

    if (q->head == NULL)
        q->head = head;
    if (q->tail != NULL)
        q->tail->next = head;
    q->tail = head;
}

/**
 * Dequere a trail from the queue.
 */
QueueNode Dequeue(TrailView q)
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
QueueNode QueueRemove(QueueView q, PlaceId location)
{
    if (q == NULL || q->head == NULL)
        return NULL;

    TrailNode prev = NULL, curr = q->head;
    while (curr->next != NULL)
    {
        if (curr->location == location)
        {
            QueueNode node = &(queueNode){.location = curr->location};
            prev->next = NULL;
            free(curr);
            return node;
        }
        prev = curr;
        curr = curr->next;
    }

    return NULL;
}