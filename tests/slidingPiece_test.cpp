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
    bishop = 1ULL << 63; // Bishop on h1
    moves = generateBishopMoves(bishop, ~0ULL, 0);
    expectedMoves = 0x0040201008040201ULL;
    assert(moves == expectedMoves && "Edge bishop test failed");

    std::cout << "All bishop move tests passed!" << std::endl;
}

void testRookMoves() {
    // Test center rook moves on empty board (d4 = square 35)
    uint64_t rook = 1ULL << 35;
    uint64_t empty = ~0ULL;
    uint64_t expectedMoves = 0x080808f708080808ULL;
    uint64_t moves = generateRookMoves(rook, empty, 0);
    assert(moves == expectedMoves && "Center rook moves incorrect");

    // Test rook blocked by friendly pieces
    uint64_t friendly = 1ULL << 27; // Friendly piece on d5
    empty = ~friendly;
    expectedMoves = 0x080808f700000000ULL;
    moves = generateRookMoves(rook, empty, 0);
    assert(moves == expectedMoves && "Rook blocked by friendly piece test failed");

    // Test rook captures
    uint64_t enemy = 1ULL << 36; // Enemy piece on e4
    empty = ~(rook | enemy);
    expectedMoves = 0x0808081708080808ULL;
    moves = generateRookMoves(rook, empty, enemy);
    assert(moves == expectedMoves && "Rook capture test failed");

    // Test corner rook
    rook = 1ULL << 56; // Rook on a1
    empty = ~0ULL;
    expectedMoves = 0xfe01010101010101ULL;
    moves = generateRookMoves(rook, empty, 0);
    assert(moves == expectedMoves && "Corner rook moves incorrect");

    // Test edge cases
    rook = 1ULL << 5; // Rook on f8
    moves = generateRookMoves(rook, ~0ULL, 0);
    expectedMoves = 0x20202020202020dfULL;
    assert(moves == expectedMoves && "Edge rook test failed");

    std::cout << "All rook move tests passed!" << std::endl;
}

void testQueenMoves() {
    // Test center queen moves on empty board (d4 = square 35)
    uint64_t queen = 1ULL << 35;
    uint64_t empty = ~0ULL;
    uint64_t expectedMoves = 0x492a1cf71c2a4988ULL;
    uint64_t moves = generateQueenMoves(queen, empty, 0);
    assert(moves == expectedMoves && "Center queen moves incorrect");

    // Test queen blocked by friendly pieces
    uint64_t friendly = (1ULL << 27) | (1ULL << 44); // Friendly pieces on d5 and e4
    empty = ~friendly;
    expectedMoves = 0x090a0cf714224180ULL;
    moves = generateQueenMoves(queen, empty, 0);
    assert(moves == expectedMoves && "Queen blocked by friendly piece test failed");

    // Test queen captures
    uint64_t enemy = (1ULL << 36) | (1ULL << 17); // Enemy pieces on e4 and b6
    empty = ~(queen | enemy);
    expectedMoves = 0x492a1c171c2a4888ULL;
    moves = generateQueenMoves(queen, empty, enemy);
    assert(moves == expectedMoves && "Queen capture test failed");

    // Test corner queen
    queen = 1ULL << 56; // Queen on a1
    empty = ~0ULL;
    expectedMoves = 0xfe03050911214181ULL;
    moves = generateQueenMoves(queen, empty, 0);
    assert(moves == expectedMoves && "Corner queen moves incorrect");

    // Test edge cases
    queen = 1ULL << 5; // Queen on f8
    moves = generateQueenMoves(queen, ~0ULL, 0);
    expectedMoves = 0x2020212224a870dfULL;
    assert(moves == expectedMoves && "Edge queen test failed");

    std::cout << "All queen move tests passed!" << std::endl;
}

int main() {
    testQueenMoves();
    return 0;
}