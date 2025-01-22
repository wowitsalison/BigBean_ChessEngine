#pragma once

struct Board {
    char squares[8][8]; // Placeholder for board representation

    Board(); // Constructor
    void initialize(); // Set up the initial position
    void display() const; // Display the board
};
