#include "bitboard.h"

#include <bitset>
#include <iostream>
#include <ostream>

bool bitboard::col_full(const unsigned short col) const
{
    return (mask & top_mask(col)) != 0;
}

unsigned long long bitboard::top_mask(const unsigned short col) {
    return 1ULL << (HEIGHT - 1) << col*(HEIGHT+1);
}

void bitboard::place_piece(const unsigned short col) {
    board ^= mask; // swap the current player bits to 0 and opponent bits to 1
    mask |= mask + bottom_mask(col);
    moves++; // increment the number of moves (now it is the opponent's turn)
}

bool bitboard::full() const {
    return moves == WIDTH * HEIGHT;
}

unsigned short bitboard::get_moves() const {
    return moves;
}

unsigned long long bitboard::get_mask() const {
    return mask;
}

unsigned long long bitboard::get_position() const {
    return board;
}

unsigned long long bitboard::bottom_mask(const unsigned short col) {
    return 1ULL << col * (HEIGHT + 1);
}

bool bitboard::is_winning_move(const int col) const {
    unsigned long long pos = board;
    pos |= (mask + bottom_mask(col)) & column_mask(col);
    return alignment(pos);
}

unsigned long long bitboard::column_mask(const int col) {
    return ((UINT64_C(1) << HEIGHT)-1) << col*(HEIGHT+1);
}

bool bitboard::alignment(const unsigned long long pos) {
    // horizontal
    unsigned long long m = pos & pos >> (HEIGHT + 1);
    if(m & m >> 2 * (HEIGHT + 1)) return true;

    // diagonal 1
    m = pos & pos >> HEIGHT;
    if(m & m >> 2 * HEIGHT) return true;

    // diagonal 2
    m = pos & pos >> (HEIGHT + 2);
    if(m & m >> 2 * (HEIGHT + 2)) return true;

    // vertical;
    m = pos & pos >> 1;
    if(m & m >> 2) return true;

    return false;
}

std::array<std::array<Player, bitboard::WIDTH>, bitboard::HEIGHT> bitboard::toArray() const {
    std::array<std::array<Player, WIDTH>, HEIGHT> arr{};

    unsigned long long grid = key();

    for(short i = 0; i < WIDTH; ++i) {
        bool empty = true;
        for(short j = HEIGHT; j >= 0; --j) {
            const bool piece = (grid & (1ULL << (i*(HEIGHT+1) + j))) != 0;
            if (piece || !empty) {
                if (empty) {
                    empty = false;
                } else {
                    arr[HEIGHT-j-1][i] = piece == moves%2 ? PLAYER_ONE : PLAYER_TWO;
                    empty = false;
                }
            }
        }
    }

    return arr;
}

/**
 * Returns a string representation of the current board
 *
 * @return A string representation of the current board
 */
std::string bitboard::toString() const {
    // std::string result;
    //
    // for (const auto grid = toArray(); auto &row : grid) {
    //     for (const auto &col : row) {
    //         switch (col) {
    //             case PLAYER_NONE:
    //                 result += " ";
    //             break;
    //             case PLAYER_ONE:
    //                 result += "X";
    //             break;
    //             case PLAYER_TWO:
    //                 result += "O";
    //             break;
    //         }
    //     }
    //     result += "\n";
    // }

    std::string res;

    for (int i = -1; const char &c : std::bitset<64>(key()).to_string()) {
        res += c;

        if (i++ % WIDTH == WIDTH - 1) {
            res += '\n';
        }
    }

    return res;
}

unsigned long long bitboard::key() const {
    return board + mask + 0b1000000100000010000001000000100000010000001;
}


/**
 * Returns a string representation of the current board with connect four style borders
 *
 * @return A string representation of the current board with borders
 */
std::string bitboard::to_border_string() const {
    std::string result = "┏━━━";
    for (int i = 0; i < WIDTH - 1; ++i) {
        result += "┳━━━";
    }
    result += "┓\n";

    auto grid = toArray();

    for (auto row = grid.begin(); row != grid.end(); ++row) {
        result += "┃";
        for (const auto &col : *row) {
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
            for (int i = 0; i < WIDTH - 1; ++i) {
                result += "╋━━━";
            }
            result += "┫\n";

        }
    }

    result += "\n┗━━━";
    for (int i = 0; i < WIDTH - 1; ++i) {
        result += "┻━━━";
    }
    result += "┛\n";

    return result;
}