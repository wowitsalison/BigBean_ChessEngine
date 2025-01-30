#include <iostream>
#include "board.h"
#include "movegen.h"

// Initialize board with starting position
void Board::initialize(const std::string& fen) {
    // Clear the board first
    pawns = rooks = knights = bishops = queens = kings = 0;
    whitePieces = blackPieces = allPieces = 0;

    int square = 0;  // Start at a8 (square 0)
    for (char c : fen) {
        if (c == ' ') break;  // Stop at board description end

        if (isdigit(c)) {
            square += (c - '0');  // Skip empty squares
        } else if (c == '/') {
            continue; // Ignore slashes
        } else {
            uint64_t mask = (1ULL << square);
            if (c == 'P') { pawns |= mask; whitePieces |= mask; }
            else if (c == 'p') { pawns |= mask; blackPieces |= mask; }
            else if (c == 'R') { rooks |= mask; whitePieces |= mask; }
            else if (c == 'r') { rooks |= mask; blackPieces |= mask; }
            else if (c == 'N') { knights |= mask; whitePieces |= mask; }
            else if (c == 'n') { knights |= mask; blackPieces |= mask; }
            else if (c == 'B') { bishops |= mask; whitePieces |= mask; }
            else if (c == 'b') { bishops |= mask; blackPieces |= mask; }
            else if (c == 'Q') { queens |= mask; whitePieces |= mask; }
            else if (c == 'q') { queens |= mask; blackPieces |= mask; }
            else if (c == 'K') { kings |= mask; whitePieces |= mask; }
            else if (c == 'k') { kings |= mask; blackPieces |= mask; }
            square++;
        }
    }
    allPieces = whitePieces | blackPieces;
}

// Update the board by making a move
void Board::makeMove(const Move& move) {
    uint64_t sourceMask = 1ULL << move.sourceSquare;
    uint64_t destMask = 1ULL << move.destinationSquare;

    // Determine if the piece being moved is white or black
    bool isWhite = whitePieces & sourceMask;

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

    // Update white and black piece bitboards correctly
    if (isWhite) {
        whitePieces &= ~sourceMask;
        whitePieces |= destMask;
        blackPieces &= ~destMask; // Remove any captured black piece
    } else {
        blackPieces &= ~sourceMask;
        blackPieces |= destMask;
        whitePieces &= ~destMask; // Remove any captured white piece
    }

    // Update all pieces bitboard
    allPieces = whitePieces | blackPieces;
}

void Board::undoMove(const Move& move) {
    uint64_t sourceMask = 1ULL << move.sourceSquare;
    uint64_t destMask = 1ULL << move.destinationSquare;

    // Determine if the piece being moved was white or black
    bool isWhite = whitePieces & destMask; // The moved piece is now at destination

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

    // Restore white and black piece bitboards
    if (isWhite) {
        whitePieces &= ~destMask;
        whitePieces |= sourceMask;
    } else {
        blackPieces &= ~destMask;
        blackPieces |= sourceMask;
    }

    // Restore all pieces
    allPieces = whitePieces | blackPieces;
}

// Print board in human-readable format
void Board::print() const {
    for (int rank = 7; rank >= 0; rank--) {
        for (int file = 0; file < 8; file++) {
            int square = (7 - rank) * 8 + file;
            uint64_t mask = 1ULL << square;
            bool isWhite = whitePieces & mask;

            if (pawns & mask) std::cout << (isWhite ? 'P' : 'p') << " ";
            else if (rooks & mask) std::cout << (isWhite ? 'R' : 'r') << " ";
            else if (knights & mask) std::cout << (isWhite ? 'N' : 'n') << " ";
            else if (bishops & mask) std::cout << (isWhite ? 'B' : 'b') << " ";
            else if (queens & mask) std::cout << (isWhite ? 'Q' : 'q') << " ";
            else if (kings & mask) std::cout << (isWhite ? 'K' : 'k') << " ";
            else std::cout << ". ";

            if (file == 7) std::cout << "\n";
        }
    }
    std::cout << std::endl;
}


// Get any piece at its square
char Board::getPiece(int square) const {
    uint64_t mask = 1ULL << square;
    bool isWhite = whitePieces & mask;

    if (pawns & mask) return isWhite ? 'P' : 'p';
    if (bishops & mask) return isWhite ? 'B' : 'b';
    if (knights & mask) return isWhite ? 'N' : 'n';
    if (rooks & mask) return isWhite ? 'R' : 'r';
    if (queens & mask) return isWhite ? 'Q' : 'q';
    if (kings & mask) return isWhite ? 'K' : 'k';

    return '.';
}
