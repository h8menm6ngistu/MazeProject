# Maze Generator and Solver

## Overview

This project generates and solves a rectangular maze using Depth First Search (DFS)  paired with stack-based backtracking.The maze is generated randomly while ensuring that every cell is connected by exactly one valid path, creating a proper maze structure.The program also solves the maze automatically and displays the correct path from the entrance to the exit.


## Features

- Random maze generation
- DFS stack-based maze creation
- Recursive maze solving
- Backtracking algorithm
- Entrance and exit generation
- ASCII maze display in terminal


## Data Structures Used

### Wall Representation

The maze stores walls using:
```cpp
vector<vector<bool>> northWall;
vector<vector<bool>> eastWall;# MazeProject
