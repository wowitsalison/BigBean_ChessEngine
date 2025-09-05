#include "gameState.h"

struct MoveEval {
    Move bestMove;
    double eval;
};

MoveEval minimax(GameState gs, int depth, bool maximizingPlayer);