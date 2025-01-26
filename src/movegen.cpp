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