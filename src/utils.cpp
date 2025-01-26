#include "utils.h"
#include <stdexcept>

int algebraicToSquare(const std::string& algebraic) {
    // Check for valid algebraic notation
    if (algebraic.length() != 2) {
        throw std::invalid_argument("Invalid algebraic notation");
    }

    char file = algebraic[0];
    char rank = algebraic[1];
    
    if (file < 'a' || file > 'h' || rank <'1' || rank > '8') {
        throw std::invalid_argument("Invalid algebraic notation");
    }

    int fileInt = file - 'a';
    int rankInt = rank - '1';

    return rankInt * 8 + fileInt;
}