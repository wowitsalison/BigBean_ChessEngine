#include <iostream>
#include <cassert>
#include "board.h"
#include "movegen.h"

void testBishopMoves() {
    // Test center bishop moves on empty board (d5 = square 27)
    uint64_t bishop = 1ULL << 27;
    uint64_t empty = ~0ULL;
    uint64_t expectedMoves = 0x8041221408000000ULL | 0x0000080402010000ULL;
    uint64_t moves = generateBishopMoves(bishop, empty, 0);
    assert(moves == expectedMoves && "Center bishop moves incorrect");

    // Test bishop blocked by friendly pieces (d6 = square 19)
    uint64_t friendly = 1ULL << 19;
    empty = ~friendly;
    expectedMoves = 0x0041221408000000ULL | 0x0000080402010000ULL;
    moves = generateBishopMoves(bishop, empty, 0);
    assert(moves == expectedMoves && "Bishop blocked by friendly piece test failed");

    // Test bishop captures
    uint64_t enemy = 1ULL << 19;
    empty = ~(bishop | enemy);
    expectedMoves = 0x0041221408000000ULL | 0x0000080402010000ULL | (1ULL << 19);
    moves = generateBishopMoves(bishop, empty, enemy);
    assert(moves == expectedMoves && "Bishop capture test failed");

    // Test corner bishop (a1 = square 56)
    bishop = 1ULL << 56;
    empty = ~0ULL;
    expectedMoves = 0x0040201008040201ULL;
    moves = generateBishopMoves(bishop, empty, 0);
    assert(moves == expectedMoves && "Corner bishop moves incorrect");

    std::cout << "All bishop move tests passed!" << std::endl;
}

int main() {
    testBishopMoves();
    return 0;
}