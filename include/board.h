#pragma once
#include <cstdint>

struct Board {
public:
    uint64_t pawns, rooks, knights, bishops, queens, kings;
    uint64_t whitePieces, blackPieces, allPieces;

    void initialize();
    void print() const;
    char getPiece(int square) const;
};

// Board masks
const uint64_t FILE_A = 0x0101010101010101ULL; // File A mask
const uint64_t FILE_H = 0x8080808080808080ULL; // File H mask