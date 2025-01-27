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
    // placeholder

    sideToMove = (sideToMove == WHITE) ? BLACK : WHITE;
    updateCastlingRights(move);
    updateEnPassantSquare(move);
    moveHistory.push_back(move);
}

// Undo move and update game state
void GameState::undoMove() {
    if (!moveHistory.empty()) {
        // Remove the last move from history
        Move lastMove = moveHistory.back();
        moveHistory.pop_back();

        // placeholder

        sideToMove = (sideToMove == WHITE) ? BLACK : WHITE;
        updateCastlingRightsUndo(lastMove);
        updateEnPassantSquareUndo(lastMove);
    }
}

// Update who has what castling rights
void GameState::updateCastlingRights(const Move& move) {
    // placeholder
}

// Update possible en passant square
void GameState::updateEnPassantSquare(const Move& move) {
    // placeholder}
}

void GameState::updateCastlingRightsUndo(const Move& move) {
    // placeholder}
}

void GameState::updateEnPassantSquareUndo(const Move& move) {
    // placeholder}
}