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

// Update the board by making a move
void Board::makeMove(const Move& move) {
    uint64_t sourceMask = 1ULL << move.sourceSquare;
    uint64_t destMask = 1ULL << move.destinationSquare;

    // Remove piece from source square
    if (move.piece == 'P') pawns &= ~sourceMask;
    else if (move.piece == 'R') rooks &= ~sourceMask;
    else if (move.piece == 'N') knights &= ~sourceMask;
    else if (move.piece == 'B') bishops &= ~sourceMask;
    else if (move.piece == 'Q') queens &= ~sourceMask;
    else if (move.piece == 'K') kings &= ~sourceMask;

    // Place piece on destination square
    if (move.piece == 'P') pawns |= destMask;
    else if (move.piece == 'R') rooks |= destMask;
    else if (move.piece == 'N') knights |= destMask;
    else if (move.piece == 'B') bishops |= destMask;
    else if (move.piece == 'Q') queens |= destMask;
    else if (move.piece == 'K') kings |= destMask;

    // Handle special moves (castling, en passant, promotion)
    if (move.isCastling) {
        // Implement castling logic here
    }
    if (move.isEnPassant) {
        // Implement en passant logic here
    }
    if (move.promotionPiece != '\0') {
        // Implement promotion logic here
    }

    // Update piece bitboards
    whitePieces = pawns | rooks | knights | bishops | queens | kings;
    blackPieces = pawns | rooks | knights | bishops | queens | kings;
    allPieces = whitePieces | blackPieces;
}

void Board::undoMove(const Move& move) {
    uint64_t sourceMask = 1ULL << move.sourceSquare;
    uint64_t destMask = 1ULL << move.destinationSquare;

    // Remove piece from destination square
    if (move.piece == 'P') pawns &= ~destMask;
    else if (move.piece == 'R') rooks &= ~destMask;
    else if (move.piece == 'N') knights &= ~destMask;
    else if (move.piece == 'B') bishops &= ~destMask;
    else if (move.piece == 'Q') queens &= ~destMask;
    else if (move.piece == 'K') kings &= ~destMask;

    // Place piece back on source square
    if (move.piece == 'P') pawns |= sourceMask;
    else if (move.piece == 'R') rooks |= sourceMask;
    else if (move.piece == 'N') knights |= sourceMask;
    else if (move.piece == 'B') bishops |= sourceMask;
    else if (move.piece == 'Q') queens |= sourceMask;
    else if (move.piece == 'K') kings |= sourceMask;

    // Handle special moves (castling, en passant, promotion)
    if (move.isCastling) {
        // Implement castling undo logic here
    }
    if (move.isEnPassant) {
        // Implement en passant undo logic here
    }
    if (move.promotionPiece != '\0') {
        // Implement promotion undo logic here
    }
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