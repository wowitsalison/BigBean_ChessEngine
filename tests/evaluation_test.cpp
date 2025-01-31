#include <cassert>
#include <iostream>
#include "utils.h"
#include "board.h"
#include "gameState.h"

class ChessTest {
private:
    GameState gs;
    int score = 0;
    
    void printTestResult(const std::string& testName, bool passed) {
        std::cout << testName << ": " << (passed ? "PASSED" : "FAILED") << std::endl;
    }

    void printMove(const Move& move) {
        std::cout << "  " << squareToAlgebraic(move.sourceSquare) 
                 << " -> " << squareToAlgebraic(move.destinationSquare) << std::endl;
    }

    bool testEmptyBoard() {
        gs.initialize("8/8/8/8/8/8/8/8 w - - 0 1"); // Initialize empty board

        // Evaluate board
        score = gs.board.materialEvaluation();
        std::cout << "\nEvaluating board:";

        bool passed = true;
        passed &= (score == 0);

        printTestResult("\nEmpty board test", passed);
        return passed;
    }

    bool testOnePawnUp() {
        gs.initialize("2k5/1p6/8/5P2/6Pp/8/3P4/5K2 w - - 0 1");

        // Evaluate board
        score = gs.board.materialEvaluation();
        std::cout << "\nEvaluating board:";

        bool passed = true;
        passed &= (score == 1);
        std::cout << "\nActual score: " << score;

        printTestResult("\nOne pawn up test", passed);
        return passed;
    }

    bool testRookVKnight() {
        gs.initialize("2k5/1p6/8/5P2/6Pp/3n4/1R1P4/5K2 w - - 0 1");

        // Evaluate board
        score = gs.board.materialEvaluation();
        std::cout << "\nEvaluating board:";

        bool passed = true;
        passed &= (score > 0);
        std::cout << "\nActual score: " << score;

        printTestResult("\nRook vs Knight test", passed);
        return passed;
    }

    bool testInitialBoard() {
        gs.initialize();

        score = gs.board.evaluate();

        bool passed = true;
        passed &= (score == 0);
        std::cout << "\nActual score: " << score;

        printTestResult("\nStarting position test", passed);
        return passed;
    }

    bool testWhiteAdvantage() {
        gs.initialize("1k3r2/2R3pp/5p2/8/8/8/5PPP/6K1 w - - 0 1");

        score = gs.board.evaluate();

        bool passed = true;
        passed &= (score > 1);
        std::cout << "\nActual score: " << score;

        printTestResult("\nWhite Advantage test", passed);
        return passed;
    }

public:
    void runMaterialTests() {
        std::cout << "Running chess engine tests...\n" << std::endl;
        
        bool allPassed = true;
        allPassed &= testEmptyBoard();
        allPassed &= testOnePawnUp();
        allPassed &= testRookVKnight();
        
        std::cout << "\nOverall test result: " << (allPassed ? "ALL PASSED" : "SOME FAILED") << std::endl;
    }

    void runCombinedTests() {
        std::cout << "Running chess engine tests...\n" << std::endl;

        bool allPassed = true;
        allPassed &= testInitialBoard();
        allPassed &= testWhiteAdvantage();
        
        std::cout << "\nOverall test result: " << (allPassed ? "ALL PASSED" : "SOME FAILED") << std::endl;
    }
};

int main() {
    ChessTest tester;
    tester.runCombinedTests();
    return 0;
}