#ifndef AI_H
#define AI_H

#include <array>
#include "../board/board.h"

using namespace std;

class ai {
    Player PLAYER;
    static int score(const board &board, Player player);
    static int heuristicEval(unsigned short playerCount, unsigned short emptyCount, unsigned short opponentCount);
    static int scoreSet(array<Player, 4> set, Player player);
    static array<int, 2> negamax(const board &b, unsigned int depth, int alpha, int beta, Player player);

    public:
    explicit ai(const Player p = PLAYER_TWO) : PLAYER(p) {}

    [[nodiscard]] unsigned short predict(const board &b, unsigned short depth) const;
};

#endif //AI_H
