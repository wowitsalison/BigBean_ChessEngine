#pragma once
#include "board.h"
#include <cstdint>

// Pawn moves
uint64_t generatePawnSinglePush(uint64_t pawns, uint64_t empty_squares, bool isWhite);
uint16_t generatePawnDoublePush(uint64_t pawns, uint64_t empty_squares, bool isWhite);
uint64_t generatePawnCaptures(uint64_t pawns, uint64_t enemy_peices, bool isWhite);