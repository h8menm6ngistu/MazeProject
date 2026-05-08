#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <stack>

using namespace std;

class Maze {

private:

    int rows;
    int cols;

    vector<vector<bool>> northWall;

    vector<vector<bool>> eastWall;

    vector<vector<bool>> visited;
    vector<vector<bool>> solutionPath;
vector<vector<bool>> deadEnd;
    int startRow;
int endRow;

public:

    Maze(int r, int c);

    void generateMaze();

    void displayMaze();
    bool solveMaze(int row, int col);
};

#endif
