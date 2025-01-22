#pragma once
#include <cstdint>

struct Board {
public:
    uint64_t pawns, rooks, knights, bishops, queens, kings;
    uint64_t whitePieces, blackPieces, allPieces;

    void initialize();
    void print() const;
};