//dan-jack-vi-jamie
// dennuguyen, Dan Nguyen, z5206032, W13B
// vii-le, Vi Le, z5205798, H13B
// jamie-rahme, Jamie Rahme, z5209611, T15A


/**
 * TrailView ADT is implemented to utilise getters and have queue implementation.
 */

#include <stdio.h>

#include "Game.h"
#include "Queue.h"

typedef struct QueueNode
{
    PlaceId location;
    int level;
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
QueueNode NewNode(PlaceId location, int level)
{
    QueueNode new = malloc(sizeof(QueueNode));
    if (new == NULL)
    {
        fprintf(stderr, "ERROR: Could not allocate memory for TrailNode\n");
        exit(1);
    }

    new->location = location;
    new->level = level;
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
void Enqueue(QueueView q, PlaceId location, int level)
{
    if (q == NULL || q->head == NULL)
        return;

    QueueNode head = NewNode(location, level);

    if (q->head == NULL)
        q->head = head;
    if (q->tail != NULL)
        q->tail->next = head;
    q->tail = head;
}

/**
 * Dequere a trail from the queue.
 */
QueueNode Dequeue(QueueView q)
{
    if (q == NULL || q->head == NULL)
        return NULL;

    QueueNode temp = q->head;
    QueueNode node = &(queueNode){.location = temp->location, .level = temp->level};
    q->head = q->head->next;

    if (q->head == NULL)
        q->tail = NULL;

    free(temp);

    return node;
}

// check for no items
int QueueIsEmpty (Queue Q)
{
	return (Q->head == NULL);
}