#include "gameState.h"

struct MoveEval {
    Move bestMove;
    int eval;
};

MoveEval minimax(GameState gs, int depth, bool maximizingPlayer);