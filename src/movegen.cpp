#include "movegen.h"
#include "utils.h"

// Move pawn one square forward
uint64_t generatePawnSinglePush(uint64_t pawns, uint64_t empty_squares, bool isWhite) {
    uint64_t move = 0;
    if (isWhite) {
        move = (pawns >> 8) & empty_squares;
        logMoves(move);
        return move;
    } else {
        move = (pawns << 8) & empty_squares;
        logMoves(move);
        return move;
    }
}

// Move pawn two squares forward from starting rank
uint64_t generatePawnDoublePush(uint64_t pawns, uint64_t empty_squares, bool isWhite) {
    uint64_t moves = 0;
    if (isWhite) {
        uint64_t singlePush = generatePawnSinglePush(pawns, empty_squares, true);
        moves = (singlePush >> 8) & empty_squares & 0x000000FF00000000ULL; // Ranks 2 - 4;
        logMoves(moves);
        return moves;
    } else {
        uint64_t singlePush = generatePawnSinglePush(pawns, empty_squares, false);
        moves = (singlePush << 8) & empty_squares & 0x00000000FF000000ULL; // Ranks 5 - 7
        logMoves(moves);
        return moves;
    }
}

// Capture piece with pawn diagonally
uint64_t generatePawnCaptures(uint64_t pawns, uint64_t enemy_peices, bool isWhite) {
    uint64_t move = 0;
    if (isWhite) {
        uint64_t leftCapture = (pawns >> 7) & ~FILE_A & enemy_peices;
        uint64_t rightCapture = (pawns >> 9) & ~FILE_H & enemy_peices;
        move = leftCapture | rightCapture;
        logMoves(move);
        return move;
    } else {
        uint64_t leftCapture = (pawns << 9) & ~FILE_H & enemy_peices;
        uint64_t rightCapture = (pawns << 7) & ~FILE_A & enemy_peices;
        move = leftCapture | rightCapture;
        logMoves(move);
        return move;
    }
}

// Move Bishop diagonally
uint64_t generateBishopMoves(uint64_t bishops, uint64_t empty_squares, uint64_t enemy_pieces) {
    uint64_t moves = 0;
    uint64_t availableSquares = empty_squares | enemy_pieces;
    const int BISHOP_DIRS[] = {NORTHEAST, SOUTHEAST, SOUTHWEST, NORTHWEST};

    for (int square = 0; square < 64; square++) {
        if (bishops & (1ULL << square)) {
            for (int dir : BISHOP_DIRS) {
                uint64_t piece = 1ULL << square;
                
                // Check if current position is on edge before moving
                if ((piece & FILE_A && (dir == NORTHWEST || dir == SOUTHWEST)) ||
                    (piece & FILE_H && (dir == NORTHEAST || dir == SOUTHEAST)) ||
                    (piece & RANK_1 && (dir == SOUTHWEST || dir == SOUTHEAST)) ||
                    (piece & RANK_8 && (dir == NORTHWEST || dir == NORTHEAST))) {
                    continue;
                }

                while (true) {
                    if (dir > 0) {
                        piece <<= dir;
                    } else {
                        piece >>= -dir;
                    }

                    if (piece == 0) break;

                    if (piece & availableSquares) {
                        moves |= piece;
                        if (piece & enemy_pieces) break;
                    } else break;

                    // Check edges after move is added
                    if ((piece & FILE_A && (dir == NORTHWEST || dir == SOUTHWEST)) ||
                        (piece & FILE_H && (dir == NORTHEAST || dir == SOUTHEAST)) ||
                        (piece & RANK_1 && (dir == NORTHWEST || dir == NORTHEAST)) ||
                        (piece & RANK_8 && (dir == SOUTHWEST || dir == SOUTHEAST))) {
                        break;
                    }
                }
            }
        }
    }

    logMoves(moves); // Log moves in algebraic notation
    return moves;
}

// Move knight in L-shape
uint64_t generateKnightMoves(uint64_t knights, uint64_t empty_squares, uint64_t enemy_pieces) {
    uint64_t moves = 0;
    uint64_t availableSquares = empty_squares | enemy_pieces;
    const int KNIGHT_DIRS[] = {NORTHEAST_L, EASTNORTH_L, EASTSOUTH_L, SOUTHEAST_L, SOUTHWEST_L, WESTSOUTH_L, WESTNORTH_L, NORTHWEST_L};
    
    for (int square = 0; square < 64; square++) {
        if (knights & (1ULL << square)) {
            for (int dir : KNIGHT_DIRS) {
                uint64_t piece = 1ULL << square;
                
                // Check if current position is on edge before moving
                if ((piece & FILE_A && (dir == NORTHWEST_L || dir == WESTNORTH_L || dir == WESTSOUTH_L || dir == SOUTHWEST_L)) ||
                    (piece & FILE_B && (dir == WESTNORTH_L || dir == WESTSOUTH_L)) ||
                    (piece & FILE_G && (dir == EASTNORTH_L || dir == EASTSOUTH_L)) ||
                    (piece & FILE_H && (dir == NORTHEAST_L || dir == EASTNORTH_L || dir == EASTSOUTH_L || dir == SOUTHEAST_L)) ||
                    (piece & RANK_1 && (dir == SOUTHWEST_L || dir == SOUTHEAST_L || dir == WESTSOUTH_L || dir == EASTSOUTH_L)) ||
                    (piece & RANK_2 && (dir == WESTNORTH_L || dir == EASTNORTH_L)) ||
                    (piece & RANK_7 && (dir == WESTSOUTH_L || dir == EASTSOUTH_L)) ||
                    (piece & RANK_8 && (dir == NORTHWEST_L || dir == NORTHEAST_L || dir == WESTNORTH_L || dir == EASTNORTH_L))) {
                    continue;
                }

                // Make single knight move
                piece = (dir > 0) ? (piece << dir) : (piece >> -dir);
                
                // Add move if valid
                if (piece && (piece & availableSquares)) {
                    moves |= piece;
                }
            }
        }
    }
    logMoves(moves); // Log moves in algebraic notation
    return moves;
}

// Move rook horizontally or vertically
uint64_t generateRookMoves(uint64_t rooks, uint64_t empty_squares, uint64_t enemy_pieces) {
    uint64_t moves = 0;
    uint64_t availableSquares = empty_squares | enemy_pieces;
    const int ROOK_DIRS[] = {NORTH, SOUTH, EAST, WEST};

    for (int square = 0; square < 64; square++) {
        if (rooks & (1ULL << square)) {
            for (int dir : ROOK_DIRS) {
                uint64_t piece = 1ULL << square;

                // Check if current position is on edge before moving
                if ((piece & FILE_A && dir == WEST) ||
                    (piece & FILE_H && dir == EAST) ||
                    (piece & RANK_1 && dir == SOUTH) ||
                    (piece & RANK_8 && dir == NORTH)) {
                    continue;
                }

                while (true) {
                    if (dir > 0) {
                        piece <<= dir;
                    } else {
                        piece >>= -dir;
                    }

                    if (piece == 0) break;

                    if (piece & availableSquares) {
                        moves |= piece;
                        if (piece & enemy_pieces) break;
                    } else break;

                    // Check edges after move is added
                    if ((piece & FILE_A && dir == WEST) ||
                        (piece & FILE_H && dir == EAST) ||
                        (piece & RANK_1 && dir == SOUTH) ||
                        (piece & RANK_8 && dir == NORTH)) {
                        break;
                    }
                }
            }
        }
    }
    logMoves(moves); // Log moves in algebraic notation
    return moves;
}

// Move queen horizontally, vertically, or diagonally
uint64_t generateQueenMoves(uint64_t queens, uint64_t empty_squares, uint64_t enemy_pieces) {
    uint64_t moves = 0;
    uint64_t availableSquares = empty_squares | enemy_pieces;
    const int QUEEN_DIRS[] = {NORTH, SOUTH, EAST, WEST, NORTHEAST, SOUTHEAST, SOUTHWEST, NORTHWEST};

    for (int square = 0; square < 64; square++) {
        if (queens & (1ULL << square)) {
            for (int dir : QUEEN_DIRS) {
                uint64_t piece = 1ULL << square;

                // Check if current position is on edge before moving
                if ((piece & FILE_A && (dir == NORTHWEST || dir == SOUTHWEST || dir == WEST)) ||
                    (piece & FILE_H && (dir == NORTHEAST || dir == SOUTHEAST || dir == EAST)) ||
                    (piece & RANK_1 && (dir == NORTH || dir == NORTHWEST || dir == NORTHEAST)) ||
                    (piece & RANK_8 && (dir == SOUTH || dir == SOUTHWEST || dir == SOUTHEAST))) {
                    continue;
                }

                while (true) {
                    if (dir > 0) {
                        piece <<= dir;
                    } else {
                        piece >>= -dir;
                    }

                    if (piece == 0) break;

                    if (piece & availableSquares) {
                        moves |= piece;
                        if (piece & enemy_pieces) break;
                    } else break;

                    // Check edges after move is added
                    if ((piece & FILE_A && (dir == NORTHWEST || dir == SOUTHWEST || dir == WEST)) ||
                        (piece & FILE_H && (dir == NORTHEAST || dir == SOUTHEAST || dir == EAST)) ||
                        (piece & RANK_1 && (dir == NORTH || dir == NORTHWEST || dir == NORTHEAST)) ||
                        (piece & RANK_8 && (dir == SOUTH || dir == SOUTHWEST || dir == SOUTHEAST))) {
                        break;
                    }
                }
            }
        }
    }
    logMoves(moves); // Log moves in algebraic notation
    return moves;
}

// Move king one square in any direction
uint64_t generateKingMoves(uint64_t kings, uint64_t empty_squares, uint64_t enemy_pieces, uint64_t enemy_attacks) {
    uint64_t moves = 0;
    uint64_t availableSquares = empty_squares | enemy_pieces;
    const int KING_DIRS[] = {NORTH, SOUTH, EAST, WEST, NORTHEAST, SOUTHEAST, SOUTHWEST, NORTHWEST};
    
    for (int square = 0; square < 64; square++) {
        if (kings & (1ULL << square)) {
            for (int dir : KING_DIRS) {
                uint64_t piece = 1ULL << square;

                // Check if current position is on edge before moving
                if ((piece & FILE_A && (dir == NORTHWEST || dir == WEST || dir == SOUTHWEST)) ||
                    (piece & FILE_H && (dir == NORTHEAST || dir == EAST || dir == SOUTHEAST)) ||
                    (piece & RANK_1 && (dir == SOUTH || dir == SOUTHWEST || dir == SOUTHEAST)) ||
                    (piece & RANK_8 && (dir == NORTH || dir == NORTHWEST || dir == NORTHEAST))) {
                    continue;
                }

                // Make single king move
                piece = (dir > 0) ? (piece << dir) : (piece >> -dir);
                
                // Add move if valid
                if (piece && (piece & availableSquares) && !(piece & enemy_attacks)) {
                    moves |= piece;
                }
            }
        }
    }
    logMoves(moves); // Log moves in algebraic notation
    return moves;
}