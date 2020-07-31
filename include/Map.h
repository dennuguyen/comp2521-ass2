////////////////////////////////////////////////////////////////////////
// COMP2521 20T2 ... The Fury of Dracula
// Map.h: an interface to a Map data type
// You can change this as much as you want!
// If you modify this, you should submit the new version.
//
// 2017-11-30   v1.0    Team Dracula <cs2521@cse.unsw.edu.au>
// 2018-12-31   v2.0    Team Dracula <cs2521@cse.unsw.edu.au>
// 2020-07-10   v3.0    Team Dracula <cs2521@cse.unsw.edu.au>
//
////////////////////////////////////////////////////////////////////////

#include <stdbool.h>
#include <stdlib.h>

#include "Places.h"

#ifndef FOD__MAP_H_
#define FOD__MAP_H_

typedef struct map *Map;
typedef struct connNode *ConnNode;
typedef struct connNode *ConnList;
typedef struct connQueue *ConnQueue;

typedef struct connNode
{
	PlaceId p;			// ALICANTE, etc.
	TransportType type; // ROAD, RAIL, BOAT
	ConnList next;		// link to next node
} connNode;

typedef struct connQueue
{
	ConnList head; // Pointer to head of queue
	ConnList tail; // Pointer to tail of queue
} connQueue;

/**
 * Creates a new map.
 */
Map MapNew(void);

/**
 * Frees all memory allocated for the given map.
 */
void MapFree(Map m);

/**
 * Prints a map to `stdout`.
 */
void MapShow(Map m);

/**
 * Gets the number of places in the map.
 */
int MapNumPlaces(Map m);

/**
 * Gets the number of connections of a particular type.
 */
int MapNumConnections(Map m, TransportType type);

/**
 * Gets a list of connections from the given place.
 * The returned list should NOT be modified or freed.
 */
ConnList MapGetConnections(Map m, PlaceId p);

/**
 * Create a new queue.
 */
ConnQueue QueueNew();

/**
 * Destroy the queue.
 */
void QueueFree(ConnQueue q);

/**
 * Enqueues an edge which consists of the destination and transport type to
 * the ConnQueue.
 */
void Enqueue(ConnQueue q, PlaceId p, TransportType type);

/**
 * Enqueues an edge which consists of the destination and transport type to
 * the ConnQueue.
 */
ConnList Dequeue(ConnQueue q, PlaceId p, TransportType type);

#endif // !defined(FOD__MAP_H_)
