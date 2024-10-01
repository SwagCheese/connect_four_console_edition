#include "ai.h"

/**
 * Negamax algorithm with alpha-beta pruning.
 *
 * @param b The board to evaluate
 * @param depth The depth of the search
 * @param alpha The alpha value
 * @param beta The beta value
 * @return An array containing the score for the chosen move and the column to place the piece
 */
// suppress clang-tidy warning about recursion
// NOLINTNEXTLINE
array<int, 2> ai::negamax(const board &b, const unsigned int depth, int alpha, int beta) {
    if (b.full()) return {0, -1};
    if (depth == 0) return {score(b), -1};

    for(const unsigned short i : b.getValidMoves()) {
        // check if current player can win next move
        board boardCopy(b);
        boardCopy.placePiece(i); // should be replaced with some kind of board.winningMove(i) method
        if(boardCopy.winner() != PLAYER_NONE) {
            return {100000, i};
        }
    }

    if(constexpr int max = 100000; beta > max) {
        beta = max;                     // there is no need to keep beta above our max possible score.
        if(alpha >= beta)
            return {beta, -1};  // prune the exploration if the [alpha;beta] window is empty.
    }

    int bestMove = -1;

    for(const unsigned short x : b.getValidMoves()) {
        board bCopy(b);
        bCopy.placePiece(x);
        const int score = -negamax(bCopy, depth-1, -beta, -alpha)[0]; // explore opponent's score within [-beta;-alpha] windows:
        // no need to have good precision for score better than beta (opponent's score worse than -beta)
        // no need to check for score worse than alpha (opponent's score worse better than -alpha)

        if(score >= beta) return {score, x};
        if(score > alpha) {
            alpha = score;
            bestMove = x;
        }
    }

    return {alpha, bestMove};
}

/**
 * Heuristic evaluation function for a set of pieces.
 *
 * @param playerCount The number of pieces the player has in the set
 * @param emptyCount The number of empty spaces in the set
 * @param opponentCount The number of pieces the opponent has in the set
 * @return The evaluation score for the set
 */
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

/**
 * Evaluate a set of pieces.
 *
 * @param set The set of pieces to evaluate
 * @param player The player to evaluate for
 * @return The score for the set
 */
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

/**
 * Evaluate a board.
 *
 * @param board The board to evaluate
 * @return The score for the board
 */
int ai::score(const board &board) {
    if (board.winner() == board.getCurrentPlayer()) {
        return INT_MAX;
    }

    if (board.winner() != PLAYER_NONE) {
        return INT_MIN;
    }

    int score = 0;

    // evaluate horizontal sets
    for (int i = board.getHighestPiece(); i < board.getNumRows(); ++i) {
        for (int j = 0; j < board.getNumCols() - 3; ++j) {
            const array set = {board.getRawGrid()[i][j], board.getRawGrid()[i][j + 1], board.getRawGrid()[i][j + 2], board.getRawGrid()[i][j + 3]};
            score += scoreSet(set, board.getCurrentPlayer());
        }
    }

    // evaluate vertical sets
    for (int i = 0; i < board.getNumCols(); ++i) {
        for (int j = 0; j < board.getNumRows() - 3; ++j) {
            const array set = {board.getRawGrid()[j][i], board.getRawGrid()[j + 1][i], board.getRawGrid()[j + 2][i], board.getRawGrid()[j + 3][i]};
            score += scoreSet(set, board.getCurrentPlayer());
        }
    }

    // evaluate diagonal sets
    for (int i = 0; i < board.getNumRows() - 3; ++i) {
        for (int j = 0; j < board.getNumCols() - 3; ++j) {
            const array set = {board.getRawGrid()[i][j], board.getRawGrid()[i + 1][j + 1], board.getRawGrid()[i + 2][j + 2], board.getRawGrid()[i + 3][j + 3]};
            score += scoreSet(set, board.getCurrentPlayer());
        }
    }

    for (int i = 0; i < board.getNumRows() - 3; ++i) {
        for (int j = 3; j < board.getNumCols(); ++j) {
            const array set = {board.getRawGrid()[i][j], board.getRawGrid()[i + 1][j - 1], board.getRawGrid()[i + 2][j - 2], board.getRawGrid()[i + 3][j - 3]};
            score += scoreSet(set, board.getCurrentPlayer());
        }
    }

    return score;
}

/**
 * Predict the best move for a given board.
 *
 * @param b The board to predict the best move for
 * @param depth The depth of the search
 * @return The best column to place the piece
 */
unsigned short ai::predict(const board &b, const unsigned short depth) {
    return negamax(b, depth, -INT_MAX, INT_MAX)[1];
}
