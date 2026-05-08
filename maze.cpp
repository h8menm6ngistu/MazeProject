#include "Maze.h"

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

struct Cell {

    int row;
    int col;
};

Maze::Maze(int r, int c) {

    rows = r;
    cols = c;

    northWall.resize(rows, vector<bool>(cols, true));
    eastWall.resize(rows, vector<bool>(cols, true));

    visited.resize(rows, vector<bool>(cols, false));

    solutionPath.resize(rows, vector<bool>(cols, false));

    deadEnd.resize(rows, vector<bool>(cols, false));

    srand(time(0));

    startRow = rand() % rows;
    endRow = rand() % rows;
}

void Maze::generateMaze() {

    stack<Cell> st;

    int currentRow = 0;
    int currentCol = 0;

    visited[currentRow][currentCol] = true;

    st.push({currentRow, currentCol});

    while (!st.empty()) {

        currentRow = st.top().row;
        currentCol = st.top().col;

        vector<Cell> neighbors;

        if (currentRow > 0 &&
            !visited[currentRow - 1][currentCol]) {

            neighbors.push_back({currentRow - 1, currentCol});
        }

        if (currentRow < rows - 1 &&
            !visited[currentRow + 1][currentCol]) {

            neighbors.push_back({currentRow + 1, currentCol});
        }

        if (currentCol > 0 &&
            !visited[currentRow][currentCol - 1]) {

            neighbors.push_back({currentRow, currentCol - 1});
        }

        if (currentCol < cols - 1 &&
            !visited[currentRow][currentCol + 1]) {

            neighbors.push_back({currentRow, currentCol + 1});
        }

        if (!neighbors.empty()) {

            int randomIndex = rand() % neighbors.size();

            Cell next = neighbors[randomIndex];

            if (next.row == currentRow - 1) {

                northWall[currentRow][currentCol] = false;
            }

            else if (next.row == currentRow + 1) {

                northWall[next.row][next.col] = false;
            }

            else if (next.col == currentCol - 1) {

                eastWall[next.row][next.col] = false;
            }

     
            else if (next.col == currentCol + 1) {

                eastWall[currentRow][currentCol] = false;
            }

            visited[next.row][next.col] = true;

            st.push(next);
        }

        else {

            st.pop();
        }
    }
}


bool Maze::solveMaze(int row, int col) {

    if (row == endRow && col == cols - 1) {

        solutionPath[row][col] = true;

        return true;
    }

    solutionPath[row][col] = true;

    if (col < cols - 1 &&
        !eastWall[row][col] &&
        !solutionPath[row][col + 1]) {

        if (solveMaze(row, col + 1))
            return true;
    }

    if (col > 0 &&
        !eastWall[row][col - 1] &&
        !solutionPath[row][col - 1]) {

        if (solveMaze(row, col - 1))
            return true;
    }

    if (row > 0 &&
        !northWall[row][col] &&
        !solutionPath[row - 1][col]) {

        if (solveMaze(row - 1, col))
            return true;
    }

    if (row < rows - 1 &&
        !northWall[row + 1][col] &&
        !solutionPath[row + 1][col]) {

        if (solveMaze(row + 1, col))
            return true;
    }

    solutionPath[row][col] = false;

    deadEnd[row][col] = true;

    return false;
}


void Maze::displayMaze() {

    for (int i = 0; i < cols; i++) {

        cout << " _";
    }

    cout << endl;

    for (int i = 0; i < rows; i++) {

        if (i == startRow)
            cout << " ";
        else
            cout << "|";

        for (int j = 0; j < cols; j++) {

            if (solutionPath[i][j])
                cout << ".";
    
            else if (deadEnd[i][j])
                cout << "x";

            else if (northWall[i][j])
                cout << "_";

            else
                cout << " ";

            if (j == cols - 1 && i == endRow)
                cout << " ";

            else if (eastWall[i][j])
                cout << "|";

            else
                cout << " ";
        }

        cout << endl;
    }
}
