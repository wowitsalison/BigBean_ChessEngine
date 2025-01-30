#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include "board.h"
#include "utils.h"

enum Side { WHITE, BLACK };
enum CastlingRights { NO_CASTLING = 0, WHITE_OO = 1, WHITE_OOO = 2, BLACK_OO = 4, BLACK_OOO = 8 };

struct GameState {
    Side sideToMove;
    uint8_t castlingRights;
    int enPassantSquare;
    std::vector<Move> moveHistory;
    Board board;

    GameState() : sideToMove(WHITE), castlingRights(NO_CASTLING), enPassantSquare(-1) {}

    void initialize();
    void initialize(const std::string& fen);
    void makeMove(const Move& move);
    void undoMove();

private:
    void updateCastlingRights(const Move& move);
    void updateEnPassantSquare(const Move& move);
    void updateCastlingRightsUndo(const Move& move);
    void updateEnPassantSquareUndo(const Move& move);
};