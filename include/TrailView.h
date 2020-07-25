/**
 * TrailView ADT with queue implementation.
 */

#ifndef FOD__TRAP_VIEW_H_
#define FOD__TRAP_VIEW_H_

#include <stdbool.h>

#include "Places.h"

typedef struct trailNode *TrailNode;
typedef struct trailView *TrailView;

/* Queue ADT */
TrailView TvNew();
void TvFree(TrailView q);
void TvEnqueue(TrailView q, PlaceId location, bool isVampire);
TrailNode TvDequeue(TrailView q);
TrailNode TvRemove(TrailView q, PlaceId location);
bool TvIsEmpty(TrailView q);
void TvShow(TrailView q);

/* Getters */
PlaceId *TvGetTrapLocations(TrailView q, int *numTraps);
PlaceId TvGetVampireLocation(TrailView q);

#endif // FOD__TRAP_VIEW_H_
