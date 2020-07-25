/**
 * TrapView ADT is implemented to utilise getters and have queue implementation.
 */

#ifndef FOD__TRAP_VIEW_H_
#define FOD__TRAP_VIEW_H_

#include <stdbool.h>
#include "Places.h"

typedef struct trapView *TrapView;

/* Getters */
PlaceId *TvGetTrapLocations(TrapView *q, int *numTraps);
PlaceId TvGetVampireLocation(TrapView *q);

/* Queue ADT */
TrapView TvNew();
void TvFree(TrapView *q);
void TvEnqueue(TrapView *q, PlaceId *location, bool isVampire);
TrapView TvDequeue(TrapView *q);
TrapView TvRemove(TrapView *q, PlaceId *location);
bool TvIsEmpty(TrapView q);
void TvShow(TrapView *q);

#endif // FOD__TRAP_VIEW_H_
