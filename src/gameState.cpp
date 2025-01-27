#include "gameState.h"

// Initialize game state at the starting position
void GameState::initialize() {
    sideToMove = WHITE;
    castlingRights = WHITE_KINGSIDE | WHITE_QUEENSIDE | BLACK_KINGSIDE | BLACK_QUEENSIDE;
    enPassantSquare = -1;
    moveHistory.clear();
}

// Make move and update game state
void GameState::makeMove(const std::string& move) {
    // placeholder
}

// Undo move and update game state
void GameState::undoMove() {
    // placeholder
}

void GameState::updateCastlingRights(const std::string& move) {
    // placeholder
}

void GameState::updateEnPassantSquare(const std::string& move) {
    // placeholder
}

void GameState::updateCastlingRightsUndo(const std::string& move) {
    // placeholder
}

void GameState::updateEnPassantSquareUndo(const std::string& move) {
    // placeholder
}