#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include "board.h"

enum Side { WHITE, BLACK };
enum CastlingRights { NO_CASTLING = 0, WHITE_KINGSIDE = 1, WHITE_QUEENSIDE = 2, BLACK_KINGSIDE = 4, BLACK_QUEENSIDE = 8 };

struct GameState {
    Side sideToMove;
    uint8_t castlingRights;
    int enPassantSquare;
    std::vector<Move> moveHistory;
    Board board;

    GameState() : sideToMove(WHITE), castlingRights(NO_CASTLING), enPassantSquare(-1) {}

    void initialize();
    void makeMove(const Move& move);
    void undoMove();

private:
    void updateCastlingRights(const Move& move);
    void updateEnPassantSquare(const Move& move);
    void updateCastlingRightsUndo(const Move& move);
    void updateEnPassantSquareUndo(const Move& move);
};