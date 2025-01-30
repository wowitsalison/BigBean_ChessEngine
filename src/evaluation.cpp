#include "evaluation.h"

#include "evaluation.h"
#include "board.h"
#include <bitset>

int Board::evaluate() const {
    int score = 0;
    
    // Count pieces using __builtin_popcountll (fast population count)
    score += __builtin_popcountll(whitePawns) * PAWN_VALUE;
    score -= __builtin_popcountll(blackPawns) * PAWN_VALUE;
    score += __builtin_popcountll(whiteKnights) * KNIGHT_VALUE;
    score -= __builtin_popcountll(blackKnights) * KNIGHT_VALUE;
    score += __builtin_popcountll(whiteBishops) * BISHOP_VALUE;
    score -= __builtin_popcountll(blackBishops) * BISHOP_VALUE;
    score += __builtin_popcountll(whiteRooks) * ROOK_VALUE;
    score -= __builtin_popcountll(blackRooks) * ROOK_VALUE;
    score += __builtin_popcountll(whiteQueens) * QUEEN_VALUE;
    score -= __builtin_popcountll(blackQueens) * QUEEN_VALUE;

    return score;  // Positive means white is ahead, negative means black is ahead
}
