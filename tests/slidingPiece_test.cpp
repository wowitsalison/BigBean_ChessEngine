#include <iostream>
#include <cassert>
#include "board.h"
#include "movegen.h"

void printMoves(uint64_t bitboard) {
    for (int i = 0; i < 64; i++) {
        if (bitboard & (1ULL << i)) std::cout << "X ";
        else std::cout << ". ";
        if ((i + 1) % 8 == 0) std::cout << "\n";
    }
    std::cout << std::endl;
}

void testBishopMoves() {
    // Test center bishop moves on empty board (d4 = square 35)
    uint64_t bishop = 1ULL << 35;
    uint64_t empty = ~0ULL;
    uint64_t expectedMoves = 0x4122140014224180ULL;
    uint64_t moves = generateBishopMoves(bishop, empty, 0);
    //std::cout << "Generated Moves:" << std::endl;
    //printMoves(moves);
    //std::cout << "Expected Moves:" << std::endl;
    //printMoves(expectedMoves);
    assert(moves == expectedMoves && "Center bishop moves incorrect");

    // Test bishop blocked by friendly pieces
    uint64_t friendly = 1ULL << 28; // Friendly piece on e5
    empty = ~friendly;
    expectedMoves = 0x4122140004020100ULL;
    moves = generateBishopMoves(bishop, empty, 0);
    assert(moves == expectedMoves && "Bishop blocked by friendly piece test failed");

    // Test bishop captures
    uint64_t enemy = 1ULL << 53; // Enemy piece on f2
    empty = ~(bishop | enemy);
    expectedMoves = 0x000122140014224180ULL;
    moves = generateBishopMoves(bishop, empty, enemy);
    assert(moves == expectedMoves && "Bishop capture test failed");

    // Test corner bishop
    bishop = 1ULL << 56; // Bishop on a1
    empty = ~0ULL;
    expectedMoves = 0x0002040810204080ULL;
    moves = generateBishopMoves(bishop, empty, 0);
    assert(moves == expectedMoves && "Corner bishop moves incorrect");

    // Test edge cases
    bishop = 1ULL << 63; // Bishop on h8
    moves = generateBishopMoves(bishop, ~0ULL, 0);
    expectedMoves = 0x0040201008040201ULL;
    assert(moves == expectedMoves && "Edge bishop test failed");

    std::cout << "All bishop move tests passed!" << std::endl;
}

int main() {
    testBishopMoves();
    return 0;
}