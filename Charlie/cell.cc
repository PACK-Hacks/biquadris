#include "cell.h"

Cell::Cell(char letter, int x, int y) : letter{letter}, x{x}, y{y} {}

char Cell::getChar() {
    return letter;
}

void Cell::addToX(int n) {
    x += n;
}

void Cell::addToY(int n) {
    y += n;
}

int Cell::getX() {
    return x;
}

int Cell::getY() {
    return y;
}

void Cell::incrementAge() {
    age++;
}
