#include <iostream>
#include <cassert>
#include "board.h"
#include "movegen.h"

void testInitialPawnMoves() {
    Board board;
    board.initialize();

    // White pawn single push
    uint64_t whiteSinglePush = generatePawnSinglePush(board.pawns & board.whitePieces, 
                                                      ~board.allPieces, true);
    assert(whiteSinglePush == 0x0000000000FF0000ULL && "White initial single push incorrect");

    // Black pawn single push
    uint64_t blackSinglePush = generatePawnSinglePush(board.pawns & board.blackPieces, 
                                                      ~board.allPieces, false);
    assert(blackSinglePush == 0x000000FF00000000ULL && "Black initial single push incorrect");

    // White pawn double push
    uint64_t whiteDoublePush = generatePawnDoublePush(board.pawns & board.whitePieces, 
                                                      ~board.allPieces, true);
    assert(whiteDoublePush == 0x0000000000FF0000ULL && "White initial double push incorrect");

    // Black pawn double push
    uint64_t blackDoublePush = generatePawnDoublePush(board.pawns & board.blackPieces, 
                                                      ~board.allPieces, false);
    assert(blackDoublePush == 0x000000FF00000000ULL && "Black initial double push incorrect");

    std::cout << "Initial pawn moves test passed!" << std::endl;
}

void testPawnCaptureBlocking() {
    Board board;
    board.initialize();

    // Simulate a blocking scenario
    uint64_t customBlockingPieces = 0x0000000000FF0000ULL; // Blocking white pawn advances
    board.allPieces |= customBlockingPieces;

    // White pawn single push should now be blocked
    uint64_t whiteSinglePush = generatePawnSinglePush(board.pawns & board.whitePieces, 
                                                      ~board.allPieces, true);
    assert(whiteSinglePush == 0x0000000000000000ULL && "White pawn push not blocked correctly");

    std::cout << "Pawn capture blocking test passed!" << std::endl;
}

int main() {
    try {
        testInitialPawnMoves();
        testPawnCaptureBlocking();
        
        std::cout << "All pawn move generation tests passed!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }
}