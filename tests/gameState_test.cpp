#include <cassert>
#include <iostream>
#include "gameState.h"
#include "board.h"
#include "movegen.h"
#include "utils.h"

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
    
    bool testPawnMove() {
        gs.initialize();
        
        // Test white pawn single push e2-e3
        Move pawnMove('P', algebraicToSquare("e2"), algebraicToSquare("e3"));
        std::cout << "\nTesting pawn move:";
        printMove(pawnMove);
        
        gs.makeMove(pawnMove);
        
        bool passed = true;
        // Verify board state
        passed &= (gs.board.getPiece(algebraicToSquare("e2")) == '?'); // Source square empty
        passed &= (gs.board.getPiece(algebraicToSquare("e3")) == 'P'); // Destination has pawn
        passed &= (gs.sideToMove == BLACK); // Side to move changed
        passed &= (gs.enPassantSquare == -1); // No en passant for single push
        
        // Test undo
        gs.undoMove();
        passed &= (gs.board.getPiece(algebraicToSquare("e2")) == 'P'); // Pawn back
        passed &= (gs.board.getPiece(algebraicToSquare("e3")) == '?'); // Square empty again
        passed &= (gs.sideToMove == WHITE);
        
        printTestResult("Pawn Single Push Test", passed);
        return passed;
    }
    
    bool testPawnDoubleMove() {
        gs.initialize();
        
        // Test white pawn double push e2-e4
        Move pawnMove('P', algebraicToSquare("e2"), algebraicToSquare("e4"));
        std::cout << "\nTesting pawn double move:";
        printMove(pawnMove);
        
        gs.makeMove(pawnMove);
        
        bool passed = true;
        // Verify board state
        passed &= (gs.board.getPiece(algebraicToSquare("e2")) == '?'); // Source square empty
        passed &= (gs.board.getPiece(algebraicToSquare("e4")) == 'P'); // Destination has pawn
        passed &= (gs.enPassantSquare == algebraicToSquare("e3")); // e3 is en passant square
        
        // Test undo
        gs.undoMove();
        passed &= (gs.board.getPiece(algebraicToSquare("e2")) == 'P'); // Pawn back
        passed &= (gs.board.getPiece(algebraicToSquare("e4")) == '?'); // Square empty again
        passed &= (gs.enPassantSquare == -1); // En passant square cleared
        
        printTestResult("Pawn Double Push Test", passed);
        return passed;
    }
    
    bool testCastlingRights() {
        gs.initialize();
        
        bool passed = true;
        // Initial castling rights should be all enabled
        passed &= (gs.castlingRights == (WHITE_KINGSIDE | WHITE_QUEENSIDE | BLACK_KINGSIDE | BLACK_QUEENSIDE));
        
        // Move king's rook h1-h2
        Move rookMove('R', algebraicToSquare("h1"), algebraicToSquare("h2"));
        std::cout << "\nTesting castling rights with move:";
        printMove(rookMove);
        
        gs.makeMove(rookMove);
        
        // Should lose white kingside castling rights
        passed &= ((gs.castlingRights & WHITE_KINGSIDE) == 0);
        passed &= ((gs.castlingRights & WHITE_QUEENSIDE) != 0); // Should still have queenside
        
        // Undo and verify rights restored
        gs.undoMove();
        passed &= (gs.castlingRights == (WHITE_KINGSIDE | WHITE_QUEENSIDE | BLACK_KINGSIDE | BLACK_QUEENSIDE));
        
        printTestResult("Castling Rights Test", passed);
        return passed;
    }
    
    bool testMoveHistory() {
        gs.initialize();
        
        bool passed = true;
        // Make a sequence of moves
        Move move1('P', algebraicToSquare("e2"), algebraicToSquare("e4")); // e2-e4
        Move move2('P', algebraicToSquare("e7"), algebraicToSquare("e5")); // e7-e5
        
        std::cout << "\nTesting move history with sequence:";
        printMove(move1);
        printMove(move2);
        
        gs.makeMove(move1);
        passed &= (gs.moveHistory.size() == 1);
        passed &= (gs.moveHistory.back().sourceSquare == algebraicToSquare("e2"));
        
        gs.makeMove(move2);
        passed &= (gs.moveHistory.size() == 2);
        passed &= (gs.moveHistory.back().sourceSquare == algebraicToSquare("e7"));
        
        // Debug output for move history
        std::cout << "  Current move history:" << std::endl;
        for (const auto& move : gs.moveHistory) {
            std::cout << "    " << squareToAlgebraic(move.sourceSquare) 
                     << " -> " << squareToAlgebraic(move.destinationSquare) << std::endl;
        }
        
        // Undo moves
        gs.undoMove();
        passed &= (gs.moveHistory.size() == 1);
        
        gs.undoMove();
        passed &= (gs.moveHistory.empty());
        
        printTestResult("Move History Test", passed);
        return passed;
    }
    
    bool testBoardVisualization() {
        gs.initialize();
        
        std::cout << "\nInitial position bitboards:" << std::endl;
        std::cout << "White pieces:" << std::endl;
        logMoves(gs.board.whitePieces);
        std::cout << "Black pieces:" << std::endl;
        logMoves(gs.board.blackPieces);
        gs.board.print();
        
        // Make a move and show updated board
        Move move('P', algebraicToSquare("e2"), algebraicToSquare("e4"));
        gs.makeMove(move);
        
        std::cout << "\nAfter e2-e4:" << std::endl;
        std::cout << "White pieces:" << std::endl;
        logMoves(gs.board.whitePieces);
        std::cout << "Black pieces:" << std::endl;
        logMoves(gs.board.blackPieces);
        gs.board.print();
        
        return true;
    }

public:
    void runAllTests() {
        std::cout << "Running chess engine tests...\n" << std::endl;
        
        bool allPassed = true;
        allPassed &= testPawnMove();
        allPassed &= testPawnDoubleMove();
        allPassed &= testCastlingRights();
        allPassed &= testMoveHistory();
        allPassed &= testBoardVisualization();
        
        std::cout << "\nOverall test result: " << (allPassed ? "ALL PASSED" : "SOME FAILED") << std::endl;
    }
};

// Main function to run tests
int main() {
    ChessTest tester;
    tester.runAllTests();
    return 0;
}