#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <stack>

using namespace std;

class Maze {

private:

    int rows;
    int cols;

    // Stores top walls
    vector<vector<bool>> northWall;

    // Stores right walls
    vector<vector<bool>> eastWall;

    // Tracks visited cells
    vector<vector<bool>> visited;
    vector<vector<bool>> solutionPath;
    int startRow;
int endRow;

public:

    Maze(int r, int c);

    void generateMaze();

    void displayMaze();
    bool solveMaze(int row, int col);
};

#endif