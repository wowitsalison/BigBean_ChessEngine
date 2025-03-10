#include "movegen.h"
#include "utils.h"
#include "board.h"
#include "gameState.h"

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

    for (int square = 0; square < 64; square++) {
        if (bishops & (1ULL << square)) {
            for (int dir : BISHOP_DIRECTIONS) {
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
    
    for (int square = 0; square < 64; square++) {
        if (knights & (1ULL << square)) {
            for (int dir : KNIGHT_DIRECTIONS) {
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

    for (int square = 0; square < 64; square++) {
        if (rooks & (1ULL << square)) {
            for (int dir : ROOK_DIRECTIONS) {
                uint64_t piece = 1ULL << square;

                // Check if current position is on edge before moving
                if ((piece & FILE_A && dir == WEST) ||
                    (piece & FILE_H && dir == EAST) ||
                    (piece & RANK_1 && dir == SOUTH) ||
                    (piece & RANK_8 && dir == NORTH)) {
                    continue;
                }

                while (true) {
                    if (dir > 0) piece <<= dir;
                    else piece >>= -dir;
                    
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

    for (int square = 0; square < 64; square++) {
        if (queens & (1ULL << square)) {
            for (int dir : QUEEN_DIRECTIONS) {
                uint64_t piece = 1ULL << square;

                // Check if current position is on edge before moving
                if ((piece & FILE_A && (dir == NORTHWEST || dir == SOUTHWEST || dir == WEST)) ||
                    (piece & FILE_H && (dir == NORTHEAST || dir == SOUTHEAST || dir == EAST)) ||
                    (piece & RANK_1 && (dir == SOUTH || dir == SOUTHWEST || dir == SOUTHEAST)) ||
                    (piece & RANK_8 && (dir == NORTH || dir == NORTHWEST || dir == NORTHEAST))) {
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
    
    for (int square = 0; square < 64; square++) {
        if (kings & (1ULL << square)) {
            for (int dir : KING_DIRECTIONS) {
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

// Pawn attack bitboards
uint64_t generatePawnAttacks(uint64_t pawns, Side side) {
    return (side == WHITE) ? ((pawns & ~FILE_A) << 7) | ((pawns & ~FILE_H) << 9)
                           : ((pawns & ~FILE_A) >> 9) | ((pawns & ~FILE_H) >> 7);
}

// Knight attack bitboards
uint64_t generateKnightAttacks(uint64_t knights) {
    uint64_t attacks = 0;
    attacks |= (knights & ~FILE_A) >> 17;
    attacks |= (knights & ~FILE_H) >> 15;
    attacks |= (knights & ~(FILE_A | FILE_B)) >> 10;
    attacks |= (knights & ~(FILE_H | FILE_G)) >> 6;
    attacks |= (knights & ~FILE_A) << 15;
    attacks |= (knights & ~FILE_H) << 17;
    attacks |= (knights & ~(FILE_A | FILE_B)) << 6;
    attacks |= (knights & ~(FILE_H | FILE_G)) << 10;
    return attacks;
}

// Bishop attack bitboards
uint64_t generateBishopAttacks(uint64_t bishops, uint64_t allPieces) {
    uint64_t attacks = 0;
    for (int square = 0; square < 64; square++) {
        if (bishops & (1ULL << square)) {
            attacks |= generateSlidingAttacks(square, allPieces, BISHOP_DIRECTIONS);
        }
    }
    return attacks;
}

// Rook attack bitboards
uint64_t generateRookAttacks(uint64_t rooks, uint64_t allPieces) {
    uint64_t attacks = 0;
    for (int square = 0; square < 64; square++) {
        if (rooks & (1ULL << square)) {
            attacks |= generateSlidingAttacks(square, allPieces, ROOK_DIRECTIONS);
        }
    }
    return attacks;
}

// Queen attack bitboards (combination of bishop and rook)
uint64_t generateQueenAttacks(uint64_t queens, uint64_t allPieces) {
    return generateBishopAttacks(queens, allPieces) | generateRookAttacks(queens, allPieces);
}

// King attack bitboards
uint64_t generateKingAttacks(uint64_t king) {
    uint64_t attacks = 0;
    attacks |= (king & ~FILE_A) >> 1;
    attacks |= (king & ~FILE_H) << 1;
    attacks |= king >> 8;
    attacks |= king << 8;
    attacks |= (king & ~FILE_A) >> 9;
    attacks |= (king & ~FILE_H) >> 7;
    attacks |= (king & ~FILE_A) << 7;
    attacks |= (king & ~FILE_H) << 9;
    return attacks;
}

// Sliding piece attack generator
uint64_t generateSlidingAttacks(int square, uint64_t allPieces, const int directions[]) {
    uint64_t attacks = 0;
    for (int dir = 0; dir < 4; dir++) {
        uint64_t piece = 1ULL << square;
        while (piece) {
            piece = (directions[dir] > 0) ? (piece << directions[dir]) : (piece >> -directions[dir]);
            if (piece & allPieces) break;
            attacks |= piece;
        }
    }
    return attacks;
}

std::vector<Move> generateAllMoves(const Board& board, Side side) {
    std::vector<Move> moves;
    bool isWhite = (side == WHITE);

    uint64_t friendlyPieces = isWhite ? board.whitePieces : board.blackPieces;
    uint64_t enemyPieces = isWhite ? board.blackPieces : board.whitePieces;
    uint64_t emptySquares = ~board.allPieces;
    uint64_t enemyAttacks = isWhite ? board.getBlackAttacks() : board.getWhiteAttacks();

    uint64_t pawns = isWhite ? board.whitePawns : board.blackPawns;
    uint64_t singlePushes = generatePawnSinglePush(pawns, emptySquares, isWhite);
    uint64_t doublePushes = generatePawnDoublePush(pawns, emptySquares, isWhite);
    uint64_t captures = generatePawnCaptures(pawns, enemyPieces, isWhite);

    // Correct insert usage
    std::vector<Move> pawnMoves = bitboardToAlgebraicMoves(pawns, singlePushes, 'P');
    moves.insert(moves.end(), pawnMoves.begin(), pawnMoves.end());

    pawnMoves = bitboardToAlgebraicMoves(pawns, doublePushes, 'P');
    moves.insert(moves.end(), pawnMoves.begin(), pawnMoves.end());

    pawnMoves = bitboardToAlgebraicMoves(pawns, captures, 'P');
    moves.insert(moves.end(), pawnMoves.begin(), pawnMoves.end());

    uint64_t bishops = isWhite ? board.whiteBishops : board.blackBishops;
    uint64_t bishopMoves = generateBishopMoves(bishops, emptySquares, enemyPieces);
    std::vector<Move> bishopMoveList = bitboardToAlgebraicMoves(bishops, bishopMoves, 'B');
    moves.insert(moves.end(), bishopMoveList.begin(), bishopMoveList.end());

    uint64_t knights = isWhite ? board.whiteKnights : board.blackKnights;
    uint64_t knightMoves = generateKnightMoves(knights, emptySquares, enemyPieces);
    std::vector<Move> knightMoveList = bitboardToAlgebraicMoves(knights, knightMoves, 'N');
    moves.insert(moves.end(), knightMoveList.begin(), knightMoveList.end());

    uint64_t rooks = isWhite ? board.whiteRooks : board.blackRooks;
    uint64_t rookMoves = generateRookMoves(rooks, emptySquares, enemyPieces);
    std::vector<Move> rookMoveList = bitboardToAlgebraicMoves(rooks, rookMoves, 'R');
    moves.insert(moves.end(), rookMoveList.begin(), rookMoveList.end());

    uint64_t queens = isWhite ? board.whiteQueens : board.blackQueens;
    uint64_t queenMoves = generateQueenMoves(queens, emptySquares, enemyPieces);
    std::vector<Move> queenMoveList = bitboardToAlgebraicMoves(queens, queenMoves, 'Q');
    moves.insert(moves.end(), queenMoveList.begin(), queenMoveList.end());

    uint64_t kings = isWhite ? board.whiteKings : board.blackKings;
    uint64_t kingMoves = generateKingMoves(kings, emptySquares, enemyPieces, enemyAttacks);
    std::vector<Move> kingMoveList = bitboardToAlgebraicMoves(kings, kingMoves, 'K');
    moves.insert(moves.end(), kingMoveList.begin(), kingMoveList.end());

    return moves;
}


std::vector<Move> bitboardToAlgebraicMoves(uint64_t fromPieces, uint64_t toSquares, char piece) {
    std::vector<Move> moves;
    while (fromPieces) {
        int from = __builtin_ctzll(fromPieces);  // Get source square
        uint64_t toMask = toSquares & ~(toSquares - 1); // Get each destination one by one
        while (toMask) {
            int to = __builtin_ctzll(toMask);  // Get destination square
            std::string fromAlgebraic = squareToAlgebraic(from);
            std::string toAlgebraic = squareToAlgebraic(to);
            moves.push_back(Move(piece, from, to));  // Store as Move object
            toSquares &= ~toMask; // Remove processed move
            toMask = toSquares & ~(toSquares - 1);
        }
        fromPieces &= fromPieces - 1;  // Remove processed piece
    }
    return moves;
}
