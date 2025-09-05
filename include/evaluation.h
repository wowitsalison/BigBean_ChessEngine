#pragma once
#include <unordered_map>
#include "board.h"

// Values calculated by taking Larry Kaufman's values from 1999 and adjusting to
// have the ratio be more similar to the ratio of Stockfish's piece values
const int PAWN_VALUE = 100;
const int KNIGHT_VALUE = 370;
const int BISHOP_VALUE = 390;
const int ROOK_VALUE = 600;
const int QUEEN_VALUE = 1000;

// Piece values mapping
const std::unordered_map<char, int> PIECE_VALUES = {
    {'P', PAWN_VALUE},   {'p', -PAWN_VALUE},
    {'N', KNIGHT_VALUE}, {'n', -KNIGHT_VALUE},
    {'B', BISHOP_VALUE}, {'b', -BISHOP_VALUE},
    {'R', ROOK_VALUE},   {'r', -ROOK_VALUE},
    {'Q', QUEEN_VALUE},  {'q', -QUEEN_VALUE},
    {'K', 0},            {'k', 0}
};

// Positional values - will most likely be adjusted later
const int CENTER_CONTROL_BONUS = 8;     // Bonus for controlling central squares
const int KING_SAFETY_PENALTY = -15;    // Penalty for exposed kings
const int ADVANCED_PAWN_BONUS = 15;     // Bonus for pawns on 2nd/7th rank
const int KNIGHT_CENTER_BONUS = 20;     // Bonus for knights in the center
const int ROOK_OPEN_FILE_BONUS = 25;    // Bonus for rooks on open files

// Important bitboards
const uint64_t CENTER_SQUARES = (1ULL << 27) | (1ULL << 28) | (1ULL << 35) | (1ULL << 36);  // d4, e4, d5, e5
const int ADJACENT_SQUARES[] = {1, 7, 8, 9, -1, -7, -8, -9}; // 8 squares around the kings
