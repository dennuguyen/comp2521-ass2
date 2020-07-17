# fury-of-dracula

Assignment Specification: https://webcms3.cse.unsw.edu.au/COMP2521/20T2/resources/49129

Important Notice: You must not modify any of the provided function signatures in the GameView, HunterView and DraculaView ADT interfaces (otherwise you'll fail auto-testing). However, you may augment these ADTs with as many other functions as you like.

### Glossary
GV = game view\
DV = dracula view\
HV = hunter view

## The View

At minimum must complete and submit: GameView.c, DraculaView.c, HunterView.c, testGameView.c, testDraculaView.c, testHunterView.c.

We can modify the existing headerfiles and add new ADTs e.g. Queue.c and Queue.h which will be submitted if added/changed.

Dracula and hunters do not directly interact with the gameview. They must use their ADT getters which calls the gameview getters.

### C Style Conventions

To mimic the given style of the assignment:
1. ADT in upper "CamelCase" reflect a hidden pointer in its declaration e.g. typedef struct gameView * GameView.
2. ADT in lower "camelCase" do not reflect a hidden pointer in its declaration.
3. Functions in upper "CamelCase" are declared in header files.
4. Functions in lower "camelCase" are statically declared.
5. Variables in "UPPERCASE" are constants.

Turn on "format on save" if your editor has the feature.

## The Hunt

Coming soon...
