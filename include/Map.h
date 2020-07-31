////////////////////////////////////////////////////////////////////////
// COMP2521 20T2 ... The Fury of Dracula
// Map.h: an interface to a Map data type
// You can change this as much as you want!
// If you modify this, you should submit the new version.
//
// dan-jack-vi-jamie
// dennuguyen, Dan Nguyen, z5206032, W13B
// vii-le, Vi Le, z5205798, H13B
// jamie-rahme, Jamie Rahme, z5209611, T15A
//
////////////////////////////////////////////////////////////////////////

#include <stdbool.h>
#include <stdlib.h>

#include "Places.h"

#ifndef FOD__MAP_H_
#define FOD__MAP_H_

typedef struct connNode *ConnList;
struct connNode
{
	PlaceId p;			// ALICANTE, etc.
	TransportType type; // ROAD, RAIL, BOAT
	ConnList next;		// link to next node
};

// Map representation is hidden
typedef struct map *Map;

/** Creates a new map. */
Map MapNew(void);

/** Frees all memory allocated for the given map. */
void MapFree(Map m);

/** Prints a map to `stdout`. */
void MapShow(Map m);

/** Gets the number of places in the map. */
int MapNumPlaces(Map m);

/** Gets the number of connections of a particular type. */
int MapNumConnections(Map m, TransportType type);

/**
 *  Gets a list of connections from the given place.
 *  The returned list should NOT be modified or freed.
 */
ConnList MapGetConnections(Map m, PlaceId p);

/**
 *  Checks if the PlaceId 'v' exists in the ConnList by 
 * a specific type of transport 'type'.
*/
bool connListContains(ConnList l, PlaceId v, TransportType type);

#endif // !defined(FOD__MAP_H_)

