#include "evaluation.h"
#include "board.h"
#include <bitset>

double Board::evaluate() const {
    double score = (static_cast<double>(materialEvaluation()) + positionalEvaluation()) / 100.0;
    return score;
}

int Board::materialEvaluation() const {
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

// Count bits (population count) for fast bitboard evaluation
inline int countBits(uint64_t bitboard) {
    return __builtin_popcountll(bitboard);
}

// Evaluate positional factors
int Board::positionalEvaluation() const {
    int score = 0;

    // Center control
    score += countBits(whitePawns & CENTER_SQUARES) * CENTER_CONTROL_BONUS;
    score -= countBits(blackPawns & CENTER_SQUARES) * CENTER_CONTROL_BONUS;
    score += countBits(whiteKnights & CENTER_SQUARES) * KNIGHT_CENTER_BONUS;
    score -= countBits(blackKnights & CENTER_SQUARES) * KNIGHT_CENTER_BONUS;

    // King safety
    uint64_t whiteKingPos = whiteKings;
    uint64_t blackKingPos = blackKings;

    for (int i = 0; i < 8; i++) {
        uint64_t wKingAdj = (ADJACENT_SQUARES[i] > 0) ? (whiteKingPos << ADJACENT_SQUARES[i]) : (whiteKingPos >> -ADJACENT_SQUARES[i]);
        uint64_t bKingAdj = (ADJACENT_SQUARES[i] > 0) ? (blackKingPos << ADJACENT_SQUARES[i]) : (blackKingPos >> -ADJACENT_SQUARES[i]);

        if (wKingAdj & (blackPawns | blackKnights | blackBishops | blackRooks | blackQueens)) {
            score += KING_SAFETY_PENALTY; // White king unsafe
        }
        if (bKingAdj & (whitePawns | whiteKnights | whiteBishops | whiteRooks | whiteQueens)) {
            score -= KING_SAFETY_PENALTY; // Black king unsafe
        }
    }

    // Pawn structure - will be updated later with pawn position hash tables
    score += countBits(whitePawns & 0x000000000000FF00ULL) * ADVANCED_PAWN_BONUS; // White pawns on 2nd rank
    score -= countBits(blackPawns & 0x00FF000000000000ULL) * ADVANCED_PAWN_BONUS; // Black pawns on 7th rank

    // Rooks on open files - will be updated to distinguish between open and semi-open
    for (int file = 0; file < 8; file++) {
        uint64_t fileMask = 0x0101010101010101ULL << file; // Vertical file mask
        if (!(whitePawns & fileMask) && (whiteRooks & fileMask)) score += ROOK_OPEN_FILE_BONUS;
        if (!(blackPawns & fileMask) && (blackRooks & fileMask)) score -= ROOK_OPEN_FILE_BONUS;
    }

    return score;
}