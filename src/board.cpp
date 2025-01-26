#include <iostream>
#include "board.h"
#include "movegen.h"

// Initialize board with starting position
void Board::initialize() {
    pawns = RANK_2 | RANK_7;
    rooks = (FILE_A | FILE_H) & (RANK_1 | RANK_8);
    knights = (FILE_B | FILE_G) & (RANK_1 | RANK_8);
    bishops = (FILE_C | FILE_F) & (RANK_1 | RANK_8);
    queens = FILE_D & (RANK_1 | RANK_8);
    kings = FILE_E & (RANK_1 | RANK_8);
    whitePieces = RANK_1;
    blackPieces = RANK_8;
    allPieces = whitePieces | blackPieces;
}

// Print board in human-readable format
void Board::print() const {
    for (int i = 0; i < 64; i++) {
        if (pawns & (1ULL << i)) std::cout << "P ";
        else if (rooks & (1ULL << i)) std::cout << "R ";
        else if (knights & (1ULL << i)) std::cout << "N ";
        else if (bishops & (1ULL << i)) std::cout << "B ";
        else if (queens & (1ULL << i)) std::cout << "Q ";
        else if (kings & (1ULL << i)) std::cout << "K ";
        else std::cout << ". ";
        if ((i + 1) % 8 == 0) std::cout << "\n";
    }
    std::cout << std::endl;
}

// Get any piece at its square
char Board::getPiece(int square) const {
    if (pawns & (1ULL << square)) return 'P';
    if (bishops & (1ULL << square )) return 'B';
    if (knights & (1ULL << square)) return 'N';
    if (rooks & (1ULL << square)) return 'R';
    if (queens & (1ULL << square)) return 'Q';
    if (kings & (1ULL << square)) return 'K';
    return '?';
}