# fury-of-dracula

### Important Notice
**You must not modify any of the provided function signatures in the GameView, HunterView and DraculaView ADT interfaces (otherwise you'll fail auto-testing). However, you may augment these ADTs with as many other functions as you like.**

### Glossary
GV = game view\
DV = dracula view\
HV = hunter view

## The View

### C Style Conventions

To mimic the given style of the assignment:
1. ADT in upper "CamelCase" reflect a hidden pointer in its declaration e.g. typedef struct gameView * GameView.
2. ADT in lower "camelCase" do not reflect a hidden pointer in its declaration.
3. Functions in upper "CamelCase" are declared in header files.
4. Functions in lower "camelCase" are statically declared.
5. Variables in "UPPERCASE" are constants.\
If possible, turn on "format on save" if your editor has the feature.

### Code Structure

Gameview.h
- struct gameView \*GameView;
- GvNew();
- GvFree();
- GvGetRound();
- GvGetPlayer();
- GvGetScore();
- GvGetHealth();
- GvGetPlayerLocation();
- GvGetVampireLocation();
- GvGetTrapLocations();
- GvGetMoveHistory();
- GvGetLastMoves();
- GvGetLocationHistory();
- GvGetLastLocations();
- GvGetReachable();
- GvGetReachableByType();

Dracula and hunters do not directly interact with the gameview. They must use their ADT getters which calls the gameview getters.

DraculaView.h
- struct draculaView \*DraculaView;
- DvNew();
- DvFree();
- DvGetRound();
- DvGetScore();
- DvGetHealth();
- DvGetPlayerLocation();
- DvGetVampireLocation();
- DvGetTrapLocations();
- DvGetValidMoves();
- DvWhereCanIGo();
- DvWhereCanIGoByType();
- DvWhereCanTheyGo();
- DvWhereCanTheyGoByType();

HunterView.h
- struct hunterView \*HunterView;
- HvNew();
- HvFree();
- HvGetRound();
- HvGetPlayer();
- HvGetScore();
- HvGetHealth();
- HvGetPlayerLocation();
- HvGetVampireLocation();
- HvGetLastKnownDraculaLocation();
- HvGetShortestPathTo();
- HvWhereCanIGo();
- HvWhereCanIGoByType();
- HvWhereCanTheyGo();
- HvWhereCanTheyGoByType();

## The Hunt

Coming soon...
