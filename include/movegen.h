#pragma once
#include "board.h"
#include <cstdint>

// Direction constants for sliding pieces
const int NORTH = -8;
const int SOUTH = 8;
const int EAST = 1;
const int WEST = -1;
const int NORTHEAST = -7;
const int SOUTHEAST = 9;
const int SOUTHWEST = 7;
const int NORTHWEST = -9;

// Direction constants for knight moves
const int NORTHEAST_L = -15; // Two squares north, one square east
const int EASTNORTH_L = -6; // Two squares east, one square north
const int EASTSOUTH_L = 10; // Two squares east, one square south
const int SOUTHEAST_L = 17;
const int SOUTHWEST_L = 15;
const int WESTSOUTH_L = 6;
const int WESTNORTH_L = -10;
const int NORTHWEST_L = -17;

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