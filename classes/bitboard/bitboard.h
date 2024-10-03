#ifndef BITBOARD_H
#define BITBOARD_H
#include <string>
#include <array>
#include "../player/player.h"


class bitboard {
    unsigned long long board; // a bitboard where players are 1 and 0, and the topmost empty space is 1. The top row is
    unsigned long long mask; // a mask with a 1 for each piece, regardless of player
    unsigned short moves = 0;
    [[nodiscard]] static bool alignment(unsigned long long pos);
    [[nodiscard]] static unsigned long long top_mask(unsigned short col);
    [[nodiscard]] static unsigned long long bottom_mask(unsigned short col);




public:
    static constexpr unsigned short HEIGHT = 6, WIDTH = 7;

    bitboard() : board(0), mask(0) {}
    bitboard(const unsigned long long b, const unsigned long long m) : board(b), mask(m) {}

    [[nodiscard]] bool col_full(unsigned short col) const;
    [[nodiscard]] static unsigned long long column_mask(int col);
    [[nodiscard]] bool full() const;
    [[nodiscard]] unsigned long long get_mask() const;
    [[nodiscard]] unsigned long long get_position() const;
    [[nodiscard]] bool is_winning_move(int col) const;


    [[nodiscard]] unsigned short get_moves() const;

    [[nodiscard]] std::array<std::array<Player, WIDTH>, HEIGHT> toArray() const;
    [[nodiscard]] std::string to_border_string() const;
    [[nodiscard]] std::string toString() const;

    unsigned long long key() const;

    void place_piece(unsigned short col);
};



#endif //BITBOARD_H
