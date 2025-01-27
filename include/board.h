#pragma once
#include <cstdint>

struct Move {
    char piece;
    int sourceSquare;
    int destinationSquare;
    bool isCastling;
    bool isEnPassant;
    char promotionPiece;

    Move(char p, int src, int dest, bool castling = false, bool enPassant = false, char promo = '\0')
        : piece(p), sourceSquare(src), destinationSquare(dest), isCastling(castling), isEnPassant(enPassant), promotionPiece(promo) {}
};

struct Board {
public:
    uint64_t pawns, rooks, knights, bishops, queens, kings;
    uint64_t whitePieces, blackPieces, allPieces;

    void initialize();
    void print() const;
    char getPiece(int square) const;
    void makeMove(const Move& move);
    void undoMove(const Move& move);
};

// Board masks
const uint64_t FILE_A = 0x0101010101010101ULL;
const uint64_t FILE_B = FILE_A << 1;
const uint64_t FILE_C = FILE_A << 2;
const uint64_t FILE_D = FILE_A << 3;
const uint64_t FILE_E = FILE_A << 4;
const uint64_t FILE_F = FILE_A << 5;
const uint64_t FILE_G = FILE_A << 6;
const uint64_t FILE_H = FILE_A << 7;

const uint64_t RANK_1 = 0xff00000000000000ULL;
const uint64_t RANK_2 = RANK_1 >> 8;
const uint64_t RANK_3 = RANK_1 >> 16;
const uint64_t RANK_4 = RANK_1 >> 24;
const uint64_t RANK_5 = RANK_1 >> 32;
const uint64_t RANK_6 = RANK_1 >> 40;
const uint64_t RANK_7 = RANK_1 >> 48;
const uint64_t RANK_8 = RANK_1 >> 56;
