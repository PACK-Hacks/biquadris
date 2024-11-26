#include "display.h"
#include <fstream>
#include "textobserver.h"
#include <memory>
using namespace std;

int main() {
    ifstream blockFile1{"blank.txt"};
    ifstream blockFile2{"blank2.txt"};

    Display d1{0, blockFile1};
    Display d2{4, blockFile2};

    d1.insertCurrentBlock();
    d1.setNextBlock();

    d2.insertCurrentBlock();
    d2.setNextBlock();
    // vector obserers for the observer instances
    std::vector<Observer*> observers;

    TextObserver t{&d1, &d2};

    t.notify();

    d1.right(4);
    d2.right(4);
    d2.right(4);
    d2.right(0);
    d2.right(0);
    d2.right(0);
    d2.right(0);
    d2.right(0);
    d2.down();
    t.notify();

    d2.left();
    t.notify();

    // d1.moveNextToCurrent();
    // d1.insertCurrentBlock();
    // d1.generateNextBlock("empty");
    // d1.setNextBlock();
    // t.notify();

    // d1.right();
    // d1.right();
    // d1.drop();
    // d1.moveNextToCurrent();
    // d1.insertCurrentBlock();
    // d1.generateNextBlock("empty");
    // d1.setNextBlock();
    // t.notify();
  }
