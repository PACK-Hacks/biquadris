#include <memory>
#include <iostream>
#include "cell.h"

using namespace std;

void hmm(Cell *p) {
    cout << p->getChar();
}

int main() {
    unique_ptr<Cell> p = make_unique<Cell>('T');

    Cell *p1 = p.get();
    unique_ptr<Cell> p2 = move(p);
    hmm(p.get());
}
