#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include "../player/player.h"

using namespace std;

class board {
    vector<vector<Player>> grid;
public:
    const unsigned short NUM_COLS, NUM_ROWS;
    unsigned short HIGHEST_PIECE;

    board() : grid(6, vector(7, PLAYER_NONE)), NUM_COLS(7), NUM_ROWS(6), HIGHEST_PIECE(5) {}
    board(const unsigned short num_rows, const unsigned short num_cols) : grid(num_rows, vector(num_cols, PLAYER_NONE)), NUM_COLS(num_cols), NUM_ROWS(num_rows), HIGHEST_PIECE(num_rows-1) {}
    board(const board &b) = default;
    [[nodiscard]] Player winner() const;
    [[nodiscard]] bool full() const;
    bool placePiece(int col, const Player &piece);

    [[nodiscard]] vector<vector<Player>> getRawGrid() const;
    void setBoard(const vector<vector<Player>> &board);

    [[nodiscard]] string toString() const;

    [[nodiscard]] string toBorderString() const;
};



#endif //BOARD_H
