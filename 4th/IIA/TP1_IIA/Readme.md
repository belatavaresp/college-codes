# Problem Description: 8-Puzzle Solver

## Task
The goal of this assignment is to implement and compare different search methods presented during the course, applying them to an 8-Puzzle toy problem. The 8-Puzzle consists of a 3x3 frame containing a set of numbered tiles from 1 to 8 and an empty space. The purpose of the game is to position the tiles in a specific order (Figure 1) by sliding them within the frame. It is known that the problem of finding a solution with the minimum number of steps in the general case, called N-Puzzle, is NP-Hard [1].

## Input and Output Format
To facilitate grading, your program should be named TP1 and read parameters from the command line. The first parameter should be the algorithm to be used (B, I, U, A, G, H), followed by the input configuration (the 8-puzzle's 3 lines in sequence, using the number 0 to represent the empty space). Optionally, a last parameter (PRINT) indicating whether intermediate steps to the solution should be printed.

For example, to solve an example problem using A*, your input should be:
```
% TP1 A 7 2 4 5 0 6 8 3 1
```

The output should only be the number of steps to the solution. If the PRINT option is used, you should print the number of steps and then all intermediate states until the solution. For example, for the input with a solution size of 2 from the file npuzzle.pdf, it should be printed:
```
% TP1 B 1 2 3 4 0 5 7 8 6 PRINT
2
1 2 3
4 5
7 8 6
1 2 3
4 5
7 8 6
1 2 3
4 5 6
7 8
```