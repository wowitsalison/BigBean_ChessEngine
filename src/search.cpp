#include <iostream>
#include "search.h"

int minimax(GameState gs, int depth, bool maximizingPlayer) {
    if (depth == 0) return gs.board.evaluate();

    std::vector<Move> legalMoves = gs.generateLegalMoves();

    if (legalMoves.empty()) {
        if (gs.isCheckmate()) return maximizingPlayer ? -100000 : 100000;
        if (gs.isStalemate()) return 0;
    }

    if (maximizingPlayer) {
        int maxEval = -100000;
        for (const Move& move : legalMoves) {
            gs.makeMove(move);
            int eval = minimax(gs, depth - 1, false);
            gs.undoMove();
            maxEval = std::max(maxEval, eval);
        }
        return maxEval;
    } else {
        int minEval = 100000;
        for (const Move& move : legalMoves) {
            gs.makeMove(move);
            int eval = minimax(gs, depth - 1, true);
            gs.undoMove();
            minEval = std::min(minEval, eval);
        }
        return minEval;
    }
}
