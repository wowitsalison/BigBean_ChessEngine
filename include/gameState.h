#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include "board.h"

enum Side { WHITE, BLACK };
enum castlingRights { NO_CASTLING, WHITE_KINGSIDE, WHITE_QUEENSIDE, BLACK_KINGSIDE, BLACK_QUEENSIDE };

struct GameState {
    Side sideToMove;
    uint8_t castlingRights;
    int enPassantSquare;
    std::vector<std::string> moveHistory;
    Board board;

    GameState() : sideToMove(WHITE), castlingRights(NO_CASTLING), enPassantSquare(-1) {}

    void initialize();
    void makeMove(const std::string& move);
    void undoMove();

private:
    void updateCastlingRights(const std::string& move);
    void updateEnPassantSquare(const std::string& move);
    void updateCastlingRightsUndo(const std::string& move);
    void updateEnPassantSquareUndo(const std::string& move);
};