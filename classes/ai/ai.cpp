#include "ai.h"

#include "../bitboard/bitboard.h"

/**
 * Negamax algorithm with alpha-beta pruning.
 *
 * @param board The board to evaluate
 * @param depth The depth to search to
 * @param alpha The alpha value
 * @param beta The beta value
 * @return An array containing the score for the chosen move and the column to place the piece
 */
// NOLINTNEXTLINE(misc-no-recursion)
array<int, 2> ai::negamax(const bitboard &board, const int depth, int alpha, int beta) {
    if(board.full()) return {0, -1};
    if(depth == 0) return {rand()*100, -1};

    for(const unsigned short i : column_order) {
        if (!board.col_full(i) && board.is_winning_move(i)) {
            return {bitboard::WIDTH*bitboard::HEIGHT - (board.get_moves() + 1), i};
        }
    }

    if (int max = bitboard::WIDTH*bitboard::HEIGHT - board.get_moves(); beta > max) {
        beta = max;               // there is no need to keep beta above our max possible score.
        if(alpha >= beta)
            return {beta, -1};  // prune the exploration if the [alpha;beta] window is empty.
    }

    int bestMove = -1;

    for(unsigned short i : column_order) {
        if (!board.col_full(i)) {

            bitboard boardCopy = board;
            boardCopy.place_piece(i);
            const int score = -negamax(boardCopy, depth-1, -beta, -alpha)[0]; // explore opponent's score within [-beta;-alpha] windows:
            // no need to have good precision for score better than beta (opponent's score worse than -beta)
            // no need to check for score worse than alpha (opponent's score worse better than -alpha)

            if(score >= beta) return {score, i};
            if(score > alpha) {
                alpha = score;
                bestMove = i;
            }
        }
    }

    return {alpha, bestMove};
}

/**
 * Predict the best move for a given board.
 *
 * @param board The board to predict the best move for
 * @param depth The depth to search to
 * @return The best column to place the piece
 */
unsigned short ai::predict(const bitboard &board, const int depth) {
    return negamax(board, depth, -INT_MAX, INT_MAX)[1];
}
