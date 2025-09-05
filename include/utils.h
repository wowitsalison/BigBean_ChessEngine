#pragma once
#include <string>
#include <cstdint>

int algebraicToSquare(const std::string& algebraic);
std::string squareToAlgebraic(int square);
void logMoves(uint64_t board);