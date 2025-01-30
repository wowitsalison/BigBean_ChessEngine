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

int evaluate(const Board& board);