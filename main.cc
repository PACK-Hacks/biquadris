#include "display.h"
#include <fstream>
#include "textobserver.h"
#include <memory>
using namespace std;

int main() {
    ifstream blockFile1{"blank.txt"};
    ifstream blockFile2{"blank2.txt"};

    Display d1{0, blockFile1};
    Display d2{0, blockFile2};

    d1.insertCurrentBlock();
    d1.setNextBlock();

    d2.insertCurrentBlock();
    d2.setNextBlock();
    // d.print();

    // d.right();
    // d.print();

    // d.down();
    // d.print();

    // d.left();
    // d.print();

    // d.drop();
    // d.print();

    // vector obserers for the observer instances
    std::vector<Observer*> observers;

    // auto d1 = std::make_unique<Display>(d);

    TextObserver t{&d1, &d2};

    t.notify();

    d1.drop();
    t.notify();

    d2.drop();
    t.notify();

    // Moving next to current and generating next
    d1.moveNextToCurrent();
    d2.moveNextToCurrent();

    t.notify();

    d1.insertCurrentBlock();
    d1.generateNextBlock();
    d1.setNextBlock();

    d2.insertCurrentBlock();
    d2.generateNextBlock();
    d2.setNextBlock();

    t.notify();

    d1.drop();
    t.notify();

    d1.moveNextToCurrent();
    d1.insertCurrentBlock();
    d1.generateNextBlock();
    d1.setNextBlock();
    t.notify();

    d1.right(4);
    t.notify();

    d1.down(11);
    t.notify();

    d1.left(5);
    d1.right();
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
