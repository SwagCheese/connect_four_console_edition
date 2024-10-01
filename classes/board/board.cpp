#include "board.h"

#include <iostream>
#include <ranges>

/**
 * Check if the board is full of pieces
 * Note that we assume that if every piece in the top row is filled, the board is full
 *
 * @return true if the board is full, false otherwise
 */
bool board::full() const {
    return ranges::all_of(grid[0], [](const Player &p) { return p != PLAYER_NONE; } );
}

/**
 * Check if the current board is in a winning state
 *
 * @return true if the board is in a winning state, false otherwise
 */
Player board::winner() const {
    // Check for horizontal wins
    for (auto &row : grid) {
        for (int i = 0; i < row.size() - 3  ; ++i) {
            if (row[i] == row[i + 1] && row[i] == row[i + 2] && row[i] == row[i + 3] && row[i] != PLAYER_NONE) {
                return row[i];
            }
        }
    }

    // Check for vertical wins
    for (int i = 0; i < grid[0].size(); ++i) {
        for (int j = 0; j < grid.size() - 3; ++j) {
            if (grid[j][i] == grid[j + 1][i] && grid[j][i] == grid[j + 2][i] && grid[j][i] == grid[j + 3][i] && grid[j][i] != PLAYER_NONE) {
                return grid[j][i];
            }
        }
    }

    // Check for diagonal wins
    for (int i = 0; i < grid.size() - 3; ++i) {
        for (int j = 0; j < grid[0].size() - 3; ++j) {
            if (grid[i][j] == grid[i + 1][j + 1] && grid[i][j] == grid[i + 2][j + 2] && grid[i][j] == grid[i + 3][j + 3] && grid[i][j] != PLAYER_NONE) {
                return grid[i][j];
            }
        }
    }

    for (int i = 0; i < grid.size() - 3; ++i) {
        for (int j = 3; j < grid[0].size(); ++j) {
            if (grid[i][j] == grid[i + 1][j - 1] && grid[i][j] == grid[i + 2][j - 2] && grid[i][j] == grid[i + 3][j - 3] && grid[i][j] != PLAYER_NONE) {
                return grid[i][j];
            }
        }
    }

    return PLAYER_NONE;
}

/**
 * Returns a string representation of the current board
 *
 * @return A string representation of the current board
 */
string board::toString() const {
    string result;
    for (auto &row : grid) {
        for (auto &col : row) {
            switch (col) {
                case PLAYER_NONE:
                    result += " ";
                    break;
                case PLAYER_ONE:
                    result += "X";
                    break;
                case PLAYER_TWO:
                    result += "O";
                    break;
            }
        }
        result += "\n";
    }

    return result;
}

/**
 * Returns a string representation of the current board with connect four style borders
 *
 * @return A string representation of the current board with borders
 */
string board::toBorderString() const {
    string result = "┏━━━";
    for (int i = 0; i < NUM_COLS - 1; ++i) {
        result += "┳━━━";
    }
    result += "┓\n";

    for (auto row = grid.begin(); row != grid.end(); ++row) {
        result += "┃";
        for (auto &col : *row) {
            switch (col) {
                case PLAYER_NONE:
                    result += "   ";
                break;
                case PLAYER_ONE:
                    result += " X ";
                break;
                case PLAYER_TWO:
                    result += " O ";
                break;
            }
            result += "┃";
        }

        if (row != grid.end() - 1) {
            result += "\n┣━━━";
            for (int i = 0; i < NUM_COLS - 1; ++i) {
                result += "╋━━━";
            }
            result += "┫\n";

        }
    }

    result += "\n┗━━━";
    for (int i = 0; i < NUM_COLS - 1; ++i) {
        result += "┻━━━";
    }
    result += "┛\n";

    return result;
}



/**
 * Place a piece in the lowest available slot in a column
 *
 * @param col The column to place a piece in
 * @param piece The piece to place
 * @return if the operation was successful
 */
bool board::placePiece(const int col, const Player &piece) {
    if (col < 0 || col >= grid[0].size()) return false;
    for (int i = static_cast<int>(grid.size()) - 1; i >= 0; --i) {
        if (grid[i][col] == PLAYER_NONE) {
            grid[i][col] = piece;
            HIGHEST_PIECE = HIGHEST_PIECE > i ? HIGHEST_PIECE : i;
            return true;
        }
    }

    return false;
}


/**
 * Returns a 2d vector representation of the current board
 *
 * @return A 2d vector representation of the current board
 */
vector<vector<Player>> board::getRawGrid() const {
    return grid;
}

/**
 * Sets the current board to the given board
 *
 * @param board The board to set the current board to
 */
void board::setBoard(const vector<vector<Player>> &board) {
    grid = board;
}
