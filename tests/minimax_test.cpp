#include <cassert>
#include <iostream>
#include "utils.h"
#include "board.h"
#include "gameState.h"

class ChessTest {
private:
    GameState gs;
};

int main() {
    ChessTest tester;
    tester.runCombinedTests();
    return 0;
}