#include "board.h"
#include <iostream>

void Board::initialize() {
    pawns = 0x00FF00000000FF00ULL;
    rooks = 0x8100000000000081ULL;
    knights = 0x4200000000000042ULL;
    bishops = 0x2400000000000024ULL;
    queens = 0x0800000000000008ULL;
    kings = 0x1000000000000010ULL;

    whitePieces = 0x000000000000FFFFULL;
    blackPieces = 0xFFFF000000000000ULL;
    allPieces = whitePieces | blackPieces;
}

// Print board in human-readable format
void Board::print() const {
    for (int i = 63; i >= 0; i--) {
        if (pawns & (1ULL << i)) std::cout << "P ";
        else if (rooks & (1ULL << i)) std::cout << "R ";
        else if (knights & (1ULL << i)) std::cout << "N ";
        else if (bishops & (1ULL << i)) std::cout << "B ";
        else if (queens & (1ULL << i)) std::cout << "Q ";
        else if (kings & (1ULL << i)) std::cout << "K ";
        else std::cout << ". ";
        if (i % 8 == 0) std::cout << "\n";
    }
    std::cout << std::endl;
}