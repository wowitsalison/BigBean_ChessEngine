#include <iostream>
#include "board.h"
#include "movegen.h"

// Initialize board with starting position
void Board::initialize(const std::string& fen) {
    // Clear the board
    whitePawns = blackPawns = 0;
    whiteKnights = blackKnights = 0;
    whiteBishops = blackBishops = 0;
    whiteRooks = blackRooks = 0;
    whiteQueens = blackQueens = 0;
    whiteKings = blackKings = 0;

    int square = 0;  // Start at a8 (square 0)
    for (char c : fen) {
        if (c == ' ') break;  // Stop at board description end

        if (isdigit(c)) {
            square += (c - '0');  // Skip empty squares
        } else if (c == '/') {
            continue; // Ignore slashes
        } else {
            uint64_t mask = (1ULL << square);
            if (c == 'P') whitePawns |= mask;
            else if (c == 'p') blackPawns |= mask;
            else if (c == 'N') whiteKnights |= mask;
            else if (c == 'n') blackKnights |= mask;
            else if (c == 'B') whiteBishops |= mask;
            else if (c == 'b') blackBishops |= mask;
            else if (c == 'R') whiteRooks |= mask;
            else if (c == 'r') blackRooks |= mask;
            else if (c == 'Q') whiteQueens |= mask;
            else if (c == 'q') blackQueens |= mask;
            else if (c == 'K') whiteKings |= mask;
            else if (c == 'k') blackKings |= mask;
            square++;
        }
    }
    pawns = whitePawns | blackPawns;
    bishops = whiteBishops | blackBishops;
    knights = whiteKnights | blackKnights;
    rooks = whiteRooks | blackRooks;
    queens = whiteQueens | blackQueens;

    whitePieces = whitePawns | whiteBishops | whiteKnights | whiteRooks | whiteQueens | whiteKings;
    blackPieces = blackPawns | blackBishops | blackKnights | blackRooks | blackQueens | blackKings;
    allPieces = whitePieces | blackPieces;
}

// Update the board by making a move
void Board::makeMove(const Move& move) {
    uint64_t sourceMask = 1ULL << move.sourceSquare;
    uint64_t destMask = 1ULL << move.destinationSquare;

    // Remove piece from source square
    if (whitePawns & sourceMask) { whitePawns &= ~sourceMask; whitePawns |= destMask; }
    else if (blackPawns & sourceMask) { blackPawns &= ~sourceMask; blackPawns |= destMask; }
    else if (whiteKnights & sourceMask) { whiteKnights &= ~sourceMask; whiteKnights |= destMask; }
    else if (blackKnights & sourceMask) { blackKnights &= ~sourceMask; blackKnights |= destMask; }
    else if (whiteBishops & sourceMask) { whiteBishops &= ~sourceMask; whiteBishops |= destMask; }
    else if (blackBishops & sourceMask) { blackBishops &= ~sourceMask; blackBishops |= destMask; }
    else if (whiteRooks & sourceMask) { whiteRooks &= ~sourceMask; whiteRooks |= destMask; }
    else if (blackRooks & sourceMask) { blackRooks &= ~sourceMask; blackRooks |= destMask; }
    else if (whiteQueens & sourceMask) { whiteQueens &= ~sourceMask; whiteQueens |= destMask; }
    else if (blackQueens & sourceMask) { blackQueens &= ~sourceMask; blackQueens |= destMask; }
    else if (whiteKings & sourceMask) { whiteKings &= ~sourceMask; whiteKings |= destMask; }
    else if (blackKings & sourceMask) { blackKings &= ~sourceMask; blackKings |= destMask; }
}

void Board::undoMove(const Move& move) {
    uint64_t sourceMask = 1ULL << move.sourceSquare;
    uint64_t destMask = 1ULL << move.destinationSquare;

    // Move piece back to its original square
    if (whitePawns & destMask) { whitePawns &= ~destMask; whitePawns |= sourceMask; }
    else if (blackPawns & destMask) { blackPawns &= ~destMask; blackPawns |= sourceMask; }
    else if (whiteKnights & destMask) { whiteKnights &= ~destMask; whiteKnights |= sourceMask; }
    else if (blackKnights & destMask) { blackKnights &= ~destMask; blackKnights |= sourceMask; }
    else if (whiteBishops & destMask) { whiteBishops &= ~destMask; whiteBishops |= sourceMask; }
    else if (blackBishops & destMask) { blackBishops &= ~destMask; blackBishops |= sourceMask; }
    else if (whiteRooks & destMask) { whiteRooks &= ~destMask; whiteRooks |= sourceMask; }
    else if (blackRooks & destMask) { blackRooks &= ~destMask; blackRooks |= sourceMask; }
    else if (whiteQueens & destMask) { whiteQueens &= ~destMask; whiteQueens |= sourceMask; }
    else if (blackQueens & destMask) { blackQueens &= ~destMask; blackQueens |= sourceMask; }
    else if (whiteKings & destMask) { whiteKings &= ~destMask; whiteKings |= sourceMask; }
    else if (blackKings & destMask) { blackKings &= ~destMask; blackKings |= sourceMask; }
}

// Print board in human-readable format
void Board::print() const {
    for (int rank = 7; rank >= 0; rank--) {  // Print from rank 8 to rank 1
        for (int file = 0; file < 8; file++) {
            int square = ((7 - rank) * 8) + file;
            uint64_t mask = 1ULL << square;

            if (whitePawns & mask) std::cout << "P ";
            else if (blackPawns & mask) std::cout << "p ";
            else if (whiteKnights & mask) std::cout << "N ";
            else if (blackKnights & mask) std::cout << "n ";
            else if (whiteBishops & mask) std::cout << "B ";
            else if (blackBishops & mask) std::cout << "b ";
            else if (whiteRooks & mask) std::cout << "R ";
            else if (blackRooks & mask) std::cout << "r ";
            else if (whiteQueens & mask) std::cout << "Q ";
            else if (blackQueens & mask) std::cout << "q ";
            else if (whiteKings & mask) std::cout << "K ";
            else if (blackKings & mask) std::cout << "k ";
            else std::cout << ". ";

            if (file == 7) std::cout << "\n";
        }
    }
    std::cout << std::endl;
}


// Get any piece at its square
char Board::getPiece(int square) const {
    uint64_t mask = 1ULL << square;
    if (whitePawns & mask) return 'P';
    if (blackPawns & mask) return 'p';
    if (whiteKnights & mask) return 'N';
    if (blackKnights & mask) return 'n';
    if (whiteBishops & mask) return 'B';
    if (blackBishops & mask) return 'b';
    if (whiteRooks & mask) return 'R';
    if (blackRooks & mask) return 'r';
    if (whiteQueens & mask) return 'Q';
    if (blackQueens & mask) return 'q';
    if (whiteKings & mask) return 'K';
    if (blackKings & mask) return 'k';

    return '.';
}