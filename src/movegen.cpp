#include "movegen.h"

// Move pawn one square forward
uint64_t generatePawnSinglePush(uint64_t pawns, uint64_t empty_squares, bool isWhite) {
    if (isWhite) {
        return (pawns << 8) & empty_squares;
    } else {
        return (pawns >> 8) & empty_squares;
    }
}

// Move pawn two squares forward from starting rank
uint64_t generatePawnDoublePush(uint64_t pawns, uint64_t empty_squares, bool isWhite) {
    if (isWhite) {
        uint64_t singlePush = generatePawnSinglePush(pawns, empty_squares, true);
        return (singlePush << 8) & empty_squares & 0x00000000FF000000ULL; // Ranks 2 - 4
    } else {
        uint64_t singlePush = generatePawnSinglePush(pawns, empty_squares, false);
        return (singlePush >> 8) & empty_squares & 0x000000FF00000000ULL; // Ranks 5 - 7
    }
}

// Capture piece with pawn diagonally
uint64_t generatePawnCaptures(uint64_t pawns, uint64_t enemy_peices, bool isWhite) {
    if (isWhite) {
        uint64_t leftCapture = (pawns << 7) & ~FILE_A & enemy_peices;
        uint64_t rightCapture = (pawns << 9) & ~FILE_H & enemy_peices;
        return leftCapture | rightCapture;
    } else {
        uint64_t leftCapture = (pawns >> 9) & ~FILE_H & enemy_peices;
        uint64_t rightCapture = (pawns >> 7) & ~FILE_A & enemy_peices;
        return leftCapture | rightCapture;
    }
}

// Move Bishop diagonally
uint64_t generateBishopMoves(uint64_t bishops, uint64_t empty_squares, uint64_t enemy_pieces) {
    uint64_t moves = 0;
    const int BISHOP_DIRS[] = {NORTHEAST, SOUTHEAST, SOUTHWEST, NORTHWEST};
    uint64_t availableSquares = empty_squares | enemy_pieces; // All squares that aren't occupied by own pieces

    for (int square = 0; square < 64; square++) {
        if (bishops & (1ULL << square)) { // Check if the piece is a bishop
            for (int dir : BISHOP_DIRS) { // Iterate over all directions
                uint64_t piece = 1ULL << square;
                // Move bishop in one direction until edge of board or blocked by own piece
                while (piece && !((dir > 0 ? piece & FILE_H : piece & FILE_A) && dir % 8 != 0)) {
                    piece = (dir > 0) ? (piece << dir) : (piece >> -dir); 
                    if (piece & availableSquares) { 
                        moves |= piece; // Add move to possible moves
                        if (piece & enemy_pieces) break; // Stop after capturing
                    } else break;
                }
            }
        }
    }
    return moves;
}