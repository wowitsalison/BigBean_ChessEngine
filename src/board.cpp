#include "board.h"
#include <iostream>
using namespace std;

// Initialize empty board
Board::Board() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            squares[i][j] = ' ';
        }
    }
}

// Place pieces on board
void Board::initialize() {
    // Place pawns
    for (int i = 0; i < 8; i++) {
        squares[1][i] = 'P';
        squares[6][i] = 'p';
    }

    // Place major pieces
    const char white_pieces[] = {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'};
    const char black_pieces[] = {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'};
    for (int i = 0; i < 8; i++) {
        squares[0][i] = white_pieces[i];
        squares[7][i] = black_pieces[i];
    }
}

// Display the board
void Board::display() const {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cout << squares[i][j] << ' ';
        }
        cout << endl;
    }
}