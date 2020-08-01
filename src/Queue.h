/**
 * Template _queue implementation using linked lists.
 * 
 * Author: Dan Nguyen
 */

#ifndef _QUEUE_H_
#define _QUEUE_H_

/* Definitions */
typedef struct _queueNode *_QueueNode;
typedef struct _queue *_Queue;

typedef struct _queueNode
{
    int data;
    struct _queueNode *next;
} _queueNode;

typedef struct _queue
{
    struct _queueNode *head;
    struct _queueNode *tail;
} _queue;

_queue *_QueueNew();
void _QueueFree(_queue *q);
void _Enqueue(_queue *q, int data);
int _Dequeue(_queue *q);
int _QueueIsEmpty(_queue *q);
void _QueueShow(_queue *q);

#endif // _QUEUE_H_