#include <iostream>
#include "board.h"

int main() {
    Board board;
    board.initialize(STARTING_FEN);
    board.print();
    return 0;
}
