#include "utils.h"
#include <stdexcept>
#include <iostream>
#include <string>
#include <cstdint>

int algebraicToSquare(const std::string& algebraic) {
    // Check for valid algebraic notation
    if (algebraic.length() != 2) {
        throw std::invalid_argument("Invalid algebraic notation");
    }

    char file = algebraic[0];
    char rank = algebraic[1];

    if (file < 'a' || file > 'h' || rank < '1' || rank > '8') {
        throw std::invalid_argument("Invalid algebraic notation");
    }

    int fileInt = file - 'a';
    int rankInt = 7 - (rank - '1'); 

    return rankInt * 8 + fileInt;
}

std::string squareToAlgebraic(int square) {
    char file = 'a' + (square % 8);
    char rank = '1' + (7 - (square / 8));
    return std::string(1, file) + rank;
}

void logMoves(uint64_t board) {
    for (int i = 0; i < 64; i++) {
        if (board & (1ULL << i)) {
            std::cout << squareToAlgebraic(i) << " ";
        }
    }
    std::cout << std::endl;
}