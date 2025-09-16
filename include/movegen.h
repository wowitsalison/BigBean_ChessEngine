#pragma once
#include "board.h"
#include <cstdint>
#include <vector>

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
const int EASTNORTH_L = -6;  // Two squares east, one square north
const int EASTSOUTH_L = 10;  // Two squares east, one square south
const int SOUTHEAST_L = 17;  // Two squares south, one square east
const int SOUTHWEST_L = 15;  // Two squares south, one square west
const int WESTSOUTH_L = 6;   // Two squares west, one square south
const int WESTNORTH_L = -10; // Two squares west, one square north
const int NORTHWEST_L = -17; // Two squares north, one square west

const int BISHOP_DIRECTIONS[] = {NORTHEAST, SOUTHEAST, SOUTHWEST, NORTHWEST};
const int KNIGHT_DIRECTIONS[] = {NORTHEAST_L, EASTNORTH_L, EASTSOUTH_L, SOUTHEAST_L, SOUTHWEST_L, WESTSOUTH_L, WESTNORTH_L, NORTHWEST_L};
const int ROOK_DIRECTIONS[] =   {NORTH, SOUTH, EAST, WEST};
const int QUEEN_DIRECTIONS[] = {NORTH, SOUTH, EAST, WEST, NORTHEAST, SOUTHEAST, SOUTHWEST, NORTHWEST};
const int KING_DIRECTIONS[] = {NORTH, SOUTH, EAST, WEST, NORTHEAST, SOUTHEAST, SOUTHWEST, NORTHWEST};

// Move generation
uint64_t generatePawnSinglePush(uint64_t pawns, uint64_t empty_squares, bool isWhite);
uint64_t generatePawnDoublePush(uint64_t pawns, uint64_t empty_squares, bool isWhite);
uint64_t generatePawnCaptures(uint64_t pawns, uint64_t enemy_peices, bool isWhite);
uint64_t generateBishopMoves(uint64_t bishops, uint64_t empty_squares, uint64_t enemy_pieces);
uint64_t generateKnightMoves(uint64_t knights, uint64_t empty_squares, uint64_t enemy_pieces);
uint64_t generateRookMoves(uint64_t rooks, uint64_t empty_squares, uint64_t enemy_pieces);
uint64_t generateQueenMoves(uint64_t queens, uint64_t empty_squares, uint64_t enemy_pieces);
uint64_t generateKingMoves(uint64_t kings, uint64_t empty_squares, uint64_t enemy_pieces, uint64_t enemy_attacks);

// Attack generation
uint64_t getWhiteAttacks();
uint64_t getBlackAttacks();
uint64_t generatePawnAttacks(uint64_t pawns, Side side);
uint64_t generateKnightAttacks(uint64_t knights);
uint64_t generateBishopAttacks(uint64_t bishops, uint64_t allPieces);
uint64_t generateRookAttacks(uint64_t rooks, uint64_t allPieces);
uint64_t generateQueenAttacks(uint64_t queens, uint64_t allPieces);
uint64_t generateKingAttacks(uint64_t king);
uint64_t generateSlidingAttacks(int square, uint64_t allPieces, const int directions[]);

std::vector<Move> generateAllMoves(const Board& board, Side side);
std::vector<Move> bitboardToAlgebraicMoves(uint64_t fromPieces, uint64_t toSquares, char piece);