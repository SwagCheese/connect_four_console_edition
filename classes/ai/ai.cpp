#include "ai.h"

using namespace std;

array<int, 2> ai::negamax(const board &b, const unsigned int depth, int alpha, const int beta, const Player player)
{
    if (depth == 0 || b.full()) {
        return {score(b, player), -1};
    }

    if (b.winner() != PLAYER_NONE) {
        return {b.winner() == player ? 1000000 : -1000000, -1};
    }

    array moveSoFar = {INT_MIN, -1};

    for (unsigned short i = 0; i < b.NUM_COLS; ++i) {
        if (b.getRawGrid()[0][i] == 0) {
            board newBoard = b;
            newBoard.placePiece(i, player);

            const int currentScore = -negamax(newBoard, depth - 1, -beta, -alpha, player == PLAYER_ONE ? PLAYER_TWO : PLAYER_ONE)[0];
            if (currentScore > moveSoFar[0]) {
                moveSoFar = {currentScore, i};
            }

            alpha = max(alpha, currentScore);
            if (alpha >= beta) {
                break;
            }
        }
    }

    return moveSoFar;
}

int ai::heuristicEval(const unsigned short playerCount, const unsigned short emptyCount, const unsigned short opponentCount) {
    int score = 0;

    if (playerCount == 4) score += 100001; // prefer to win
    else if (playerCount == 3 && emptyCount == 1) score += 100;
    else if (playerCount == 2 && emptyCount == 2) score += 10;
    else if (opponentCount == 3 && emptyCount == 1) score -= 101; // prefer to block opponent
    else if (opponentCount == 2 && emptyCount == 2) score -= 11; // prefer to block opponent
    else if (opponentCount == 4) score -= 100000;

    return score;
}

int ai::scoreSet(const array<Player, 4> set, const Player player) {
    unsigned short emptyCount = 0;
    unsigned short playerCount = 0;
    unsigned short opponentCount = 0;

    for (const auto &piece : set) {
        playerCount += piece == player;
        opponentCount += piece != player && piece != PLAYER_NONE;
        emptyCount += piece == PLAYER_NONE;
    }

    return heuristicEval(playerCount, emptyCount, opponentCount);
}

int ai::score(const board &board, const Player player) {
    if (board.winner() == player) {
        return INT_MAX;
    }

    if (board.winner() != PLAYER_NONE) {
        return INT_MIN;
    }

    int score = 0;

    // evaluate horizontal sets
    for (int i = board.HIGHEST_PIECE; i < board.NUM_ROWS; ++i) {
        for (int j = 0; j < board.NUM_COLS - 3; ++j) {
            const array set = {board.getRawGrid()[i][j], board.getRawGrid()[i][j + 1], board.getRawGrid()[i][j + 2], board.getRawGrid()[i][j + 3]};
            score += scoreSet(set, player);
        }
    }

    // evaluate vertical sets
    for (int i = 0; i < board.NUM_COLS; ++i) {
        for (int j = 0; j < board.NUM_ROWS - 3; ++j) {
            const array set = {board.getRawGrid()[j][i], board.getRawGrid()[j + 1][i], board.getRawGrid()[j + 2][i], board.getRawGrid()[j + 3][i]};
            score += scoreSet(set, player);
        }
    }

    // evaluate diagonal sets
    for (int i = 0; i < board.NUM_ROWS - 3; ++i) {
        for (int j = 0; j < board.NUM_COLS - 3; ++j) {
            const array set = {board.getRawGrid()[i][j], board.getRawGrid()[i + 1][j + 1], board.getRawGrid()[i + 2][j + 2], board.getRawGrid()[i + 3][j + 3]};
            score += scoreSet(set, player);
        }
    }

    for (int i = 0; i < board.NUM_ROWS - 3; ++i) {
        for (int j = 3; j < board.NUM_COLS; ++j) {
            const array set = {board.getRawGrid()[i][j], board.getRawGrid()[i + 1][j - 1], board.getRawGrid()[i + 2][j - 2], board.getRawGrid()[i + 3][j - 3]};
            score += scoreSet(set, player);
        }
    }

    return score;
}


unsigned short ai::predict(board &b, const unsigned short depth) const {
    return negamax(b, depth, INT_MIN, INT_MAX, PLAYER)[1];
}
