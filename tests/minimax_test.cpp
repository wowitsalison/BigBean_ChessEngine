#include <cassert>
#include <iostream>
#include "utils.h"
#include "board.h"
#include "gameState.h"
#include "search.h"

class ChessTest {
private:
    GameState gs;

    void printTestResult(const std::string& testName, bool passed) {
        std::cout << testName << ": " << (passed ? "PASSED" : "FAILED") << std::endl;
    }

    void printMove(const Move& move) {
        std::cout << "  " << squareToAlgebraic(move.sourceSquare) 
                 << " -> " << squareToAlgebraic(move.destinationSquare) << std::endl;
    }

    bool testOneLegalMove() {
        // Initialize position with one legal move
        gs.initialize("rnbqk2r/ppp4p/7n/4p1p1/1bpPP3/N4P2/PP2BNPP/R2QKR2 w Qkq - 2 11");

        // Run minimax
        MoveEval moveEval = minimax(gs, 2, true);
        std::cout << "\nEvaluating position...\n";
        
        // Only legal move
        Move expectedMove('Q', 59, 51);

        // Compare output with real only legal move
        bool passed = true;
        passed &= (moveEval.bestMove.piece == expectedMove.piece &&
                    moveEval.bestMove.sourceSquare == expectedMove.sourceSquare &&
                    moveEval.bestMove.destinationSquare == expectedMove.destinationSquare);

        std::cout << "\nBest move found: ";
        printMove(moveEval.bestMove);

        printTestResult("\nOne legal move test", passed);
        return passed;
    }

public:
    void runCombinedTests() {
        std::cout << "Running chess engine tests...\n" << std::endl;

        bool allPassed = true;
        allPassed &= testOneLegalMove();
        
        std::cout << "\nOverall test result: " << (allPassed ? "ALL PASSED" : "SOME FAILED") << std::endl;
    }
};

int main() {
    ChessTest tester;
    tester.runCombinedTests();
    return 0;
}