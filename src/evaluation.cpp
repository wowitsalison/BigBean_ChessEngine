#include "evaluation.h"

int evaluate(const Board& board) {
    int score = 0;

    for (int square = 0; square < 64; square++) {
        char piece = board.getPiece(square);
        if (piece != '.') {  // Ignore empty squares
            auto it = PIECE_VALUES.find(piece);
            if (it != PIECE_VALUES.end()) {
                score += it->second;
            }
        }
    }

    return score;
}
