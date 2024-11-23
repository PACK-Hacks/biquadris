#include "cell.h"

Cell::Cell(char letter) : letter{letter} {}

char Cell::getChar() {
    return letter;
}
