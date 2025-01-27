#include "gameState.h"

// Initialize game state at the starting position
void GameState::initialize() {
    board.initialize();
    sideToMove = WHITE;
    castlingRights = WHITE_KINGSIDE | WHITE_QUEENSIDE | BLACK_KINGSIDE | BLACK_QUEENSIDE;
    enPassantSquare = -1;
    moveHistory.clear();
}

// Make move and update game state
void GameState::makeMove(const Move& move) {
    Move& moveWithHistory = const_cast<Move&>(move);
    moveWithHistory.previousCastlingRights = castlingRights;
    moveWithHistory.previousEnPassantSquare = enPassantSquare;
    
    // Make the move on the board
    board.makeMove(move);
    
    // Update game state
    sideToMove = (sideToMove == WHITE) ? BLACK : WHITE;
    updateCastlingRights(move);
    updateEnPassantSquare(move);
    
    // Add to history after all state is updated
    moveHistory.push_back(move);
}

// Undo move and update game state
void GameState::undoMove() {
    if (!moveHistory.empty()) {
        Move lastMove = moveHistory.back();
        moveHistory.pop_back();
        
        // Undo the move on the board
        board.undoMove(lastMove);
        
        // Restore exact previous state
        sideToMove = (sideToMove == WHITE) ? BLACK : WHITE;
        castlingRights = lastMove.previousCastlingRights;
        enPassantSquare = lastMove.previousEnPassantSquare;
    }
}

// Update who has what castling rights
void GameState::updateCastlingRights(const Move& move) {
    // Remove castling rights if king moves
    if (move.piece == 'K') {
        if (sideToMove == WHITE) {
            castlingRights &= ~(WHITE_KINGSIDE | WHITE_QUEENSIDE);
        } else {
            castlingRights &= ~(BLACK_KINGSIDE | BLACK_QUEENSIDE);
        }
    }
    
    // Remove castling rights if rook moves or is captured
    if (move.piece == 'R' || (board.getPiece(move.destinationSquare) == 'R')) {
        // Check source and destination squares for rook positions
        if (move.sourceSquare == 0 || move.destinationSquare == 0) { // a1
            castlingRights &= ~WHITE_QUEENSIDE;
        }
        if (move.sourceSquare == 7 || move.destinationSquare == 7) { // h1
            castlingRights &= ~WHITE_KINGSIDE;
        }
        if (move.sourceSquare == 56 || move.destinationSquare == 56) { // a8
            castlingRights &= ~BLACK_QUEENSIDE;
        }
        if (move.sourceSquare == 63 || move.destinationSquare == 63) { // h8
            castlingRights &= ~BLACK_KINGSIDE;
        }
    }
}

// Update possible en passant square
void GameState::updateEnPassantSquare(const Move& move) {
    // Set en passant square only for pawn double moves
    if (move.piece == 'P') {
        int rankMove = move.destinationSquare / 8 - move.sourceSquare / 8;
        if (abs(rankMove) == 2) {
            // Set en passant square to the square behind the pawn
            enPassantSquare = (move.sourceSquare + move.destinationSquare) / 2;
        } else {
            enPassantSquare = -1;
        }
    } else {
        enPassantSquare = -1;
    }
}

// Restore previous castling rights during moveUndo
void GameState::updateCastlingRightsUndo(const Move& move) {
    castlingRights = move.previousCastlingRights;
}

// Restore previous EnPassantSquare during moveUndo
void GameState::updateEnPassantSquareUndo(const Move& move) {
    enPassantSquare = move.previousEnPassantSquare;
}