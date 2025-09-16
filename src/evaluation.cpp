#include "evaluation.h"
#include "board.h"
#include <bitset>

double Board::evaluate() const {
    // Evaluation formula from (source) - FIND A NEW FORMULA
    double score = (static_cast<double>(materialEvaluation()) + positionalEvaluation()) / 100.0;
    return score;
}

// Count bits (population count) for fast bitboard evaluation
inline int countBits(uint64_t bitboard) {
    return __builtin_popcountll(bitboard);
}

int Board::materialEvaluation() const {
    int score = 0;
    
    // Count piece points
    score += countBits(whitePawns)   * PAWN_VALUE;
    score -= countBits(blackPawns)   * PAWN_VALUE;
    score += countBits(whiteKnights) * KNIGHT_VALUE;
    score -= countBits(blackKnights) * KNIGHT_VALUE;
    score += countBits(whiteBishops) * BISHOP_VALUE;
    score -= countBits(blackBishops) * BISHOP_VALUE;
    score += countBits(whiteRooks)   * ROOK_VALUE;
    score -= countBits(blackRooks)   * ROOK_VALUE;
    score += countBits(whiteQueens)  * QUEEN_VALUE;
    score -= countBits(blackQueens)  * QUEEN_VALUE;

    return score;
}

// Evaluate positional factors
int Board::positionalEvaluation() const {
    int score = 0;

    // Give bonus for center control
    score += countBits(whitePawns & CENTER_SQUARES) * CENTER_CONTROL_BONUS;
    score -= countBits(blackPawns & CENTER_SQUARES) * CENTER_CONTROL_BONUS;
    // Give bonus for knights in the center
    score += countBits(whiteKnights & CENTER_SQUARES) * KNIGHT_CENTER_BONUS;
    score -= countBits(blackKnights & CENTER_SQUARES) * KNIGHT_CENTER_BONUS;

    // Get king positions
    uint64_t whiteKingPos = whiteKings;
    uint64_t blackKingPos = blackKings;

    // Give penalty for unsafe king
    for (int i = 0; i < 8; i++) {
        // Get squares adjacent to kings
        uint64_t wKingAdj = (ADJACENT_SQUARES[i] > 0) ? (whiteKingPos << ADJACENT_SQUARES[i]) : (whiteKingPos >> -ADJACENT_SQUARES[i]);
        uint64_t bKingAdj = (ADJACENT_SQUARES[i] > 0) ? (blackKingPos << ADJACENT_SQUARES[i]) : (blackKingPos >> -ADJACENT_SQUARES[i]);

        if (wKingAdj & (blackPawns | blackKnights | blackBishops | blackRooks | blackQueens)) {
            // Penalty for enemy pieces adjacent to white king
            score += KING_SAFETY_PENALTY;
        }
        if (bKingAdj & (whitePawns | whiteKnights | whiteBishops | whiteRooks | whiteQueens)) {
            // Penalty for enemy pieces adjacent to black king
            score -= KING_SAFETY_PENALTY;
        }
    }

    // Pawn structure - will be updated later with pawn position hash tables
    score += countBits(whitePawns & 0x000000000000FF00ULL) * ADVANCED_PAWN_BONUS; // White pawns on 2nd rank
    score -= countBits(blackPawns & 0x00FF000000000000ULL) * ADVANCED_PAWN_BONUS; // Black pawns on 7th rank

    // Rooks on open files - will be updated to distinguish between open and semi-open
    for (int file = 0; file < 8; file++) {
        // Create mask for given file
        uint64_t fileMask = 0x0101010101010101ULL << file; 
        if (!(whitePawns & fileMask) && (whiteRooks & fileMask)) score += ROOK_OPEN_FILE_BONUS;
        if (!(blackPawns & fileMask) && (blackRooks & fileMask)) score -= ROOK_OPEN_FILE_BONUS;
    }

    return score;
}