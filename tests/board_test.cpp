#include <iostream>
#include <cassert>
#include "board.h"
#include "utils.h"

void testBoardInitialization() {
    Board board;
    board.initialize();
    board.print();

    // Check initial positions of pawns
    assert(board.getPiece(8) == 'p' && "Pawn not initialized correctly at square 8");
    assert(board.getPiece(48) == 'P' && "Pawn not initialized correctly at square 48");

    // Check initial positions of rooks
    assert(board.getPiece(0) == 'r' && "Rook not initialized correctly at square 0");
    assert(board.getPiece(56) == 'R' && "Rook not initialized correctly at square 56");

    // Check initial positions of knights
    assert(board.getPiece(1) == 'n' && "Knight not initialized correctly at square 1");
    assert(board.getPiece(6) == 'n' && "Knight not initialized correctly at square 6");
    assert(board.getPiece(62) == 'N' && "Knight not initialized correctly at square 62");
    assert(board.getPiece(57) == 'N' && "Knight not initialized correctly at square 57");

    // Check initial positions of bishops
    assert(board.getPiece(2) == 'b' && "Bishop not initialized correctly at square 2");
    assert(board.getPiece(5) == 'b' && "Bishop not initialized correctly at square 5");
    assert(board.getPiece(61) == 'B' && "Bishop not initialized correctly at square 61");
    assert(board.getPiece(58) == 'B' && "Bishop not initialized correctly at square 58");

    // Check initial positions of queens
    assert(board.getPiece(3) == 'q' && "Queen not initialized correctly at square 3");
    assert(board.getPiece(59) == 'Q' && "Queen not initialized correctly at square 59");

    // Check initial positions of kings
    assert(board.getPiece(4) == 'k' && "King not initialized correctly at square 4");
    assert(board.getPiece(60) == 'K' && "King not initialized correctly at square 60");

    std::cout << "Board initialization test passed!" << std::endl;
}

void testPieceAccess() {
    Board board;
    board.initialize();

    // Test access to specific pieces
    assert(board.getPiece(0) == 'r' && "Failed to access rook at square 0");
    assert(board.getPiece(1) == 'n' && "Failed to access knight at square 1");
    assert(board.getPiece(2) == 'b' && "Failed to access bishop at square 2");
    assert(board.getPiece(3) == 'q' && "Failed to access queen at square 3");
    assert(board.getPiece(4) == 'k' && "Failed to access king at square 4");
    assert(board.getPiece(8) == 'p' && "Failed to access pawn at square 8");

    std::cout << "Piece access test passed!" << std::endl;
}

void testAlgebraicConversions() {
    // Test algebraic to index conversions
    assert(algebraicToSquare("a1") == 56 && "Failed to convert a1 to index 56");
    assert(algebraicToSquare("h1") == 63 && "Failed to convert h1 to index 63");
    assert(algebraicToSquare("a8") == 0 && "Failed to convert a8 to index 0");
    assert(algebraicToSquare("h8") == 7 && "Failed to convert h8 to index 7");
    assert(algebraicToSquare("e2") == 52 && "Failed to convert e2 to index 52");
    assert(algebraicToSquare("d4") == 35 && "Failed to convert d4 to index 35");

    std::cout << "Algebraic conversions test passed!" << std::endl;
}

int main() {
    try {
        testBoardInitialization();
        testPieceAccess();
        testAlgebraicConversions();

        std::cout << "All tests passed!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }
}