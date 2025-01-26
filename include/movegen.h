#pragma once
#include "board.h"
#include <cstdint>

// Pawn moves
uint64_t generatePawnSinglePush(uint64_t pawns, uint64_t empty_squares, bool isWhite);
uint64_t generatePawnDoublePush(uint64_t pawns, uint64_t empty_squares, bool isWhite);
uint64_t generatePawnCaptures(uint64_t pawns, uint64_t enemy_peices, bool isWhite);
// Bishop moves
uint64_t generateBishopMoves(uint64_t bishops, uint64_t empty_squares, uint64_t enemy_pieces);
// Knight moves
uint64_t generateKnightMoves(uint64_t knights, uint64_t empty_squares, uint64_t enemy_pieces);
// Rook moves
uint64_t generateRookMoves(uint64_t rooks, uint64_t empty_squares, uint64_t enemy_pieces);
// Queen moves
uint64_t generateQueenMoves(uint64_t queens, uint64_t empty_squares, uint64_t enemy_pieces);
// King moves
uint64_t generateKingMoves(uint64_t kings, uint64_t empty_squares, uint64_t enemy_pieces);