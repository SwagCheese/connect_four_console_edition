#ifndef AI_H
#define AI_H

#include <array>
#include "../bitboard/bitboard.h"

using namespace std;

class ai {
    static constexpr unsigned short column_order[bitboard::WIDTH]{3, 2, 4, 1, 5, 0, 6};
    [[nodiscard]] static array<int, 2> negamax(const bitboard &board, int depth, int alpha, int beta);

public:
    [[nodiscard]] static unsigned short predict(const bitboard &board, int depth);
};

#endif //AI_H
