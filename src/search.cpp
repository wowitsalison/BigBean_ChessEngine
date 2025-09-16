#include <iostream>
#include "search.h"

MoveEval minimax(GameState gs, int depth, bool maximizingPlayer) {
    // Base case: evaluate the board
    if (depth == 0) return {Move(), gs.board.evaluate()};

    // Get a list of all the legal moves
    std::vector<Move> legalMoves = gs.generateLegalMoves();

    // Handle end-of-game positions
    if (legalMoves.empty()) {
        double eval = 0;
        if (gs.isCheckmate()) eval = maximizingPlayer ? -100000 : 100000;
        if (gs.isStalemate()) eval = 0;
        return {Move(), eval};
    }

    Move bestMove;
    double bestEval = maximizingPlayer ? -100000 : 100000;

    // Loop through all legal moves to find the best one
    for (const Move& move : legalMoves) {
        gs.makeMove(move);
        std::cout << "Evaluating move: " << move.piece << squareToAlgebraic(move.destinationSquare);
        double eval = minimax(gs, depth - 1, !maximizingPlayer).eval;
        std::cout << ", Eval: " << eval << std::endl;
        gs.undoMove();

        if ((maximizingPlayer && eval > bestEval) || (!maximizingPlayer && eval < bestEval)) {
            bestEval = eval;
            bestMove = move;
        }
    }

    return {bestMove, bestEval};
}
