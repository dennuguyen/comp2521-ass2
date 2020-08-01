#include <stdio.h>
#include <stdlib.h>

#include "Queue.h"

_queue *_QueueNew()
{
    _queue *q = malloc(sizeof(_queue));
    if (q == NULL)
    {
        fprintf(stderr, "ERROR: failed to malloc _queue.\n");
        exit(EXIT_FAILURE);
    }
    q->head = q->tail = NULL;
    return q;
}

void _QueueFree(_queue *q)
{
    if (q == NULL || q->head == NULL)
        return;

    _queueNode *curr = q->head;
    while (curr)
    {
        _queueNode *next = curr->next;
        free(curr);
        curr = NULL;
        curr = next;
    }
    free(q);
    q = NULL;
}

void _Enqueue(_queue *q, int data)
{
    _queueNode *n = malloc(sizeof(_queueNode));
    if (n == NULL)
    {
        fprintf(stderr, "ERROR: failed to malloc _queueNode *.\n");
        exit(EXIT_FAILURE);
    }
    n->data = data;
    n->next = NULL;
    if (q->head == NULL)
        q->head = n;
    if (q->tail != NULL)
        q->tail->next = n;
    q->tail = n;
}

int _Dequeue(_queue *q)
{
    int t = q->head->data;
    _queueNode *tmp = q->head;
    q->head = q->head->next;
    if (q->head == NULL)
        q->tail = NULL;
    free(tmp);
    return t;
}

int _QueueIsEmpty(_queue *q)
{
    return q->head == NULL;
}

void _QueueShow(_queue *q)
{
    if (q == NULL || q->head == NULL)
        return;

    printf("[");
    for (_queueNode *curr = q->head; curr != NULL; curr = curr->next)
    {
        if (curr->next == NULL)
            printf("%d", curr->data);
        else
            printf("%d, ", curr->data);
    }
    printf("]");
}
