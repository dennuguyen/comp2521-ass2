# fury-of-dracula

Assignment Specification: https://webcms3.cse.unsw.edu.au/COMP2521/20T2/resources/49129

### Contributors
**dan-jack-vi-jamie**\
dennuguyen, Dan Nguyen, z5206032, W13B\
vii-le, Vi Le, z5205798, H13B\
jamie-rahme, Jamie Rahme, z5209611, T15A

### Glossary
GV = game view\
DV = dracula view\
HV = hunter view

### C Style Conventions

To mimic the given style of the assignment:
1. ADT in upper ```CamelCase``` reflect a hidden pointer in its declaration e.g. ```typedef struct gameView * GameView.```
2. ADT in lower ```camelCase``` do not reflect a hidden pointer in its declaration.
3. Functions in upper ```CamelCase``` are declared in header files.
4. Functions in lower ```camelCase``` are statically declared.
5. Variables in ```UPPERCASE``` are constants.
6. Variables are in lower ```camelCase``` otherwise.

## The Hunt

### Framework of what we have to do:

The most optimised solution would be to simulate future possible states then select the move on the path to that state where the objective of the player is considered. The objective for Dracula would be to keep the score as low as possible and the objective for the hunters would be to keep the score as high as possible.

In searching for future possible states, heuristics should be applied to ignore states that would obviously not beneficial to the player's objective. Therefore increasing the amount of time allowed to search for a more optimal game move.

The pathway for the future states need to be stored into some tree. An optimised tree for this assignment would allow fast insertions and traversal.

In summary, the hunters and Dracula's objectives, heuristics and a data structure to store future game states needs to be identified.