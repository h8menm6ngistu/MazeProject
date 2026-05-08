#include "Maze.h"

int main() {

    Maze maze(10, 10);

    maze.generateMaze();

    maze.solveMaze(0, 0);

    maze.displayMaze();

    return 0;
}