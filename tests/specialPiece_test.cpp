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

void testKnightMoves() {
    // Test center knight moves on empty board (d4 = square 35)
    uint64_t knight = 1ULL << 35;
    uint64_t empty = ~0ULL;
    uint64_t expectedMoves = 0x0014220022140000ULL;
    uint64_t moves = generateKnightMoves(knight, empty, 0);
    assert(moves == expectedMoves && "Center knight moves incorrect");

    // Test knight blocked by friendly pieces
    uint64_t friendly = 1ULL << 20; // Friendly piece on e6
    empty = ~friendly;
    expectedMoves = 0x0014220022040000ULL;
    moves = generateKnightMoves(knight, empty, 0);
    assert(moves == expectedMoves && "Knight blocked by friendly piece test failed");

    // Test knight captures
    uint64_t enemy = 1ULL << 36; // Enemy piece on e4
    empty = ~(knight | enemy);
    expectedMoves = 0x0014220022140000ULL;
    moves = generateKnightMoves(knight, empty, enemy);
    assert(moves == expectedMoves && "Knight capture test failed");

    // Test corner knight
    knight = 1ULL << 56; // knight on a1
    empty = ~0ULL;
    expectedMoves = 0x0004020000000000ULL;
    moves = generateKnightMoves(knight, empty, 0);
    assert(moves == expectedMoves && "Corner knight moves incorrect");

    // Test edge cases
    knight = 1ULL << 6; // knight on g8
    moves = generateKnightMoves(knight, ~0ULL, 0);
    expectedMoves = 0x0000000000a01000ULL;
    assert(moves == expectedMoves && "Edge knight test failed");

    std::cout << "All knight move tests passed!" << std::endl;
}

int main() {
    testKnightMoves();
    return 0;
}