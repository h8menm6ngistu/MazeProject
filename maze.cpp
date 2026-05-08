#include "Maze.h"

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

// Represents one maze cell
struct Cell {

    int row;
    int col;
};

// Constructor
Maze::Maze(int r, int c) {

    rows = r;
    cols = c;

    // All walls initially exist
    northWall.resize(rows, vector<bool>(cols, true));
    eastWall.resize(rows, vector<bool>(cols, true));

    // No cells visited yet
    visited.resize(rows, vector<bool>(cols, false));
    solutionPath.resize(rows, vector<bool>(cols, false));

    srand(time(0));
    startRow = rand() % rows;
endRow = rand() % rows;
}

// Generate maze using DFS + stack
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

        // UP
        if (currentRow > 0 &&
            !visited[currentRow - 1][currentCol]) {

            neighbors.push_back({currentRow - 1, currentCol});
        }

        // DOWN
        if (currentRow < rows - 1 &&
            !visited[currentRow + 1][currentCol]) {

            neighbors.push_back({currentRow + 1, currentCol});
        }

        // LEFT
        if (currentCol > 0 &&
            !visited[currentRow][currentCol - 1]) {

            neighbors.push_back({currentRow, currentCol - 1});
        }

        // RIGHT
        if (currentCol < cols - 1 &&
            !visited[currentRow][currentCol + 1]) {

            neighbors.push_back({currentRow, currentCol + 1});
        }

        // If unvisited neighbors exist
        if (!neighbors.empty()) {

            int randomIndex = rand() % neighbors.size();

            Cell next = neighbors[randomIndex];

            // Remove walls between cells

            // Moving UP
            if (next.row == currentRow - 1) {

                northWall[currentRow][currentCol] = false;
            }

            // Moving DOWN
            else if (next.row == currentRow + 1) {

                northWall[next.row][next.col] = false;
            }

            // Moving LEFT
            else if (next.col == currentCol - 1) {

                eastWall[next.row][next.col] = false;
            }

            // Moving RIGHT
            else if (next.col == currentCol + 1) {

                eastWall[currentRow][currentCol] = false;
            }

            visited[next.row][next.col] = true;

            st.push(next);
        }

        else {

            // Dead end → go backward
            st.pop();
        }
    }
}

// Display maze in console
void Maze::displayMaze() {

    // Top border
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

            // Bottom wall
            if (solutionPath[i][j])
    cout << ".";
else if (northWall[i][j])
    cout << "_";
else
    cout << " ";

            // Right wall
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
bool Maze::solveMaze(int row, int col) {

    // Reached exit
    if (row == endRow && col == cols - 1) {

        solutionPath[row][col] = true;

        return true;
    }

    // Mark current cell as part of path
    solutionPath[row][col] = true;

    // MOVE RIGHT
    if (col < cols - 1 &&
        !eastWall[row][col] &&
        !solutionPath[row][col + 1]) {

        if (solveMaze(row, col + 1))
            return true;
    }

    // MOVE LEFT
    if (col > 0 &&
        !eastWall[row][col - 1] &&
        !solutionPath[row][col - 1]) {

        if (solveMaze(row, col - 1))
            return true;
    }

    // MOVE UP
    if (row > 0 &&
        !northWall[row][col] &&
        !solutionPath[row - 1][col]) {

        if (solveMaze(row - 1, col))
            return true;
    }

    // MOVE DOWN
    if (row < rows - 1 &&
        !northWall[row + 1][col] &&
        !solutionPath[row + 1][col]) {

        if (solveMaze(row + 1, col))
            return true;
    }

    // Dead end -> remove from path
    solutionPath[row][col] = false;

    return false;
}