#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include "../player/player.h"

using namespace std;

class board {
    const unsigned short NUM_COLS, NUM_ROWS;
    unsigned short HIGHEST_PIECE;
    Player currentPlayer = PLAYER_ONE;
    vector<vector<Player>> grid;
public:

    board() : NUM_COLS(7), NUM_ROWS(6), HIGHEST_PIECE(5), grid(6, vector(7, PLAYER_NONE)) {}
    board(const unsigned short num_rows, const unsigned short num_cols) : NUM_COLS(num_cols), NUM_ROWS(num_rows), HIGHEST_PIECE(num_rows-1), grid(num_rows, vector(num_cols, PLAYER_NONE)) {}
    board(const board &b) = default;
    [[nodiscard]] Player winner() const;
    [[nodiscard]] bool full() const;
    [[nodiscard]] vector<unsigned short> getValidMoves() const;
    // [[nodiscard]] bool isWinningMove(int col) const;
    bool placePiece(int col);
    [[nodiscard]] unsigned short getHighestPiece() const { return HIGHEST_PIECE; }
    [[nodiscard]] unsigned short getNumCols() const { return NUM_COLS; }
    [[nodiscard]] unsigned short getNumRows() const { return NUM_ROWS; }
    [[nodiscard]] Player getCurrentPlayer() const { return currentPlayer; }

    [[nodiscard]] vector<vector<Player>> getRawGrid() const;
    void setBoard(const vector<vector<Player>> &board);

    [[nodiscard]] string toString() const;

    [[nodiscard]] string toBorderString() const;
};



#endif //BOARD_H
