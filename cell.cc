#include "cell.h"

Cell::Cell(char letter, int x, int y) : letter{letter}, x{x}, y{y} {}

// Get character of cell (Would be / if its moving)
char Cell::getChar() {
    return letter;
}

// Get real cell, used for / to actual character of block
char Cell::getRealChar() {
    return realLetter;
}

// Set the realLetter to letter to reflect the block being placed on the board
void Cell::place() {
    realLetter = letter;
}

// Increment X
void Cell::addToX(int n) {
    x += n;
}

// Increment Y
void Cell::addToY(int n) {
    y += n;
}

// Get X
int Cell::getX() {
    return x;
}

// Get Y
int Cell::getY() {
    return y;
}

// Cell no longer on board
void Cell::kill() {
    alive = false;
}

// Check if cell on board
bool Cell::isAlive() {
    return alive;
}
