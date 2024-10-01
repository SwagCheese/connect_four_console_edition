#ifndef AI_H
#define AI_H

#include <array>
#include "../board/board.h"

using namespace std;

class ai {
    Player PLAYER;
    static int score(const board &board);
    static int heuristicEval(unsigned short playerCount, unsigned short emptyCount, unsigned short opponentCount);
    static int scoreSet(array<Player, 4> set, Player player);
    array<int, 2> negamax(const board &b, unsigned int depth, int alpha, int beta);

    public:
    explicit ai(const Player p = PLAYER_TWO) : PLAYER(p) {}

    [[nodiscard]] unsigned short predict(const board &b, unsigned short depth);
};

#endif //AI_H
