// Queue.h ... interface to Queue ADT

#ifndef QUEUE_H
#define QUEUE_H


typedef struct QueueNode QueueNode;
typedef struct QueueView *Queue;

QueueNode NewNode(PlaceId, int);
Queue QueueNew (void);			// Create new empty queue
void QueueFree (Queue);			// Free memory used by queue
void Enqueue (Queue, PlaceId, int);	// Add item on queue
QueueNode Dequeue (Queue);		// Remove item from queue
int QueueIsEmpty (Queue);		// Check for no items

#endif
