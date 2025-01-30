#include <iostream>
#include <cassert>
#include "board.h"
#include "movegen.h"

void testInitialPawnMoves() {
    Board board;
    board.initialize();

    // White pawn single push
    uint64_t whiteSinglePush = generatePawnSinglePush(board.pawns & board.whitePieces, ~board.allPieces, true);
    std::cout << "Actual white single push: 0x" << std::hex << whiteSinglePush << std::endl;
    assert(whiteSinglePush == 0x0000ff0000000000ULL && "White initial single push incorrect");

    // Black pawn single push
    uint64_t blackSinglePush = generatePawnSinglePush(board.pawns & board.blackPieces, ~board.allPieces, false);
    std::cout << "Actual black single push: 0x" << std::hex << blackSinglePush << std::endl;
    assert(blackSinglePush == 0x0000000000ff0000ULL && "Black initial single push incorrect");

    // White pawn double push
    uint64_t whiteDoublePush = generatePawnDoublePush(board.pawns & board.whitePieces, ~board.allPieces, true);
    std::cout << "Actual white double push: 0x" << std::hex << whiteDoublePush << std::endl;
    assert(whiteDoublePush == 0x000000ff00000000ULL && "White initial double push incorrect");

    // Black pawn double push
    uint64_t blackDoublePush = generatePawnDoublePush(board.pawns & board.blackPieces, ~board.allPieces, false);
    std::cout << "Actual black double push: 0x" << std::hex << blackDoublePush << std::endl;
    assert(blackDoublePush == 0x00000000ff000000ULL && "Black initial double push incorrect");
    }

void testPawnCaptureBlocking() {
    Board board;
    board.initialize();

    // Simulate a blocking scenario
    uint64_t customBlockingPieces = 0x0000ff0000000000ULL; // Blocking white pawn advances
    board.allPieces |= customBlockingPieces;

    // White pawn single push should now be blocked
    uint64_t whiteSinglePush = generatePawnSinglePush(board.pawns & board.whitePieces, 
                                                      ~board.allPieces, true);
    assert(whiteSinglePush == 0x0000000000000000ULL && "White pawn push not blocked correctly");

    uint64_t whiteCapture = generatePawnCaptures(board.pawns & board.whitePieces, customBlockingPieces, true);
    assert(whiteCapture == 0x0000ff0000000000ULL && "White capture incorrect");

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