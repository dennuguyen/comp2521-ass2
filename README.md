# fury-of-dracula

Assignment Specification: https://webcms3.cse.unsw.edu.au/COMP2521/20T2/resources/49129

Important Notice: You must not modify any of the provided function signatures in the GameView, HunterView and DraculaView ADT interfaces (otherwise you'll fail auto-testing). However, you may augment these ADTs with as many other functions as you like.

### Contributors
**dan-jack-vi-jamie**\
dennuguyen, Dan Nguyen, z5206032, W13B\
vii-le, Vi Le, z5205798, H13B\
jamie-rahme, Jamie Rahme, z5209611, T15A

### Glossary
GV = game view\
DV = dracula view\
HV = hunter view

### Directory Tree
```
./
|__ Makefile            // make, make lib, make exe, make bin, make show, make clean
|
|__ bin/                // contains binaries
|
|__ include/            // contains all header files
|   |__ *.h
|
|__ main/               // contains all .c files that have main()
|   |__ *.c
|
|__ obj/                // contains all .o files
|   |__ exe/            // .o files from main
|   |   |__ *.o
|   |
|   |__ lib/            // .o files from src
|       |__ *.o
|
|__ src/                // contains all other .c files
|   |__ *.c
|
|__ test/               // contains .c files relevant for testing
    |__ GameView/       // .c files for GV tests
    |   |__ *.c
    |
    |__ DraculaView/    // .c files for DV tests
    |   |__ *.c
    |
    |__ HunterView/     // .c files for HV tests
        |__ *.c
```

### C Style Conventions

To mimic the given style of the assignment:
1. ADT in upper ```CamelCase``` reflect a hidden pointer in its declaration e.g. ```typedef struct gameView * GameView.```
2. ADT in lower ```camelCase``` do not reflect a hidden pointer in its declaration.
3. Functions in upper ```CamelCase``` are declared in header files.
4. Functions in lower ```camelCase``` are statically declared.
5. Variables in ```UPPERCASE``` are constants.
6. Variables are in lower ```camelCase``` otherwise.

Turn on "format on save" if your editor has the feature.

## The View

At minimum must complete and submit: GameView.c, DraculaView.c, HunterView.c, testGameView.c, testDraculaView.c, testHunterView.c.

The draculaView, hunterView structs inherit the gameView struct i.e. shares the same memory allocation as gameView. Therefore, using GameView's ADT functions requires a typecast from draculaView and hunterView.

## The Hunt

Coming soon....
