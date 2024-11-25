#include "display.h"
#include <fstream>
#include "textobserver.h"
#include <memory>
using namespace std;

int main() {
    ifstream blockFile{"blank.txt"};

    Display d{0, blockFile};

    d.insertCurrentBlock();
    d.setNextBlock();
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

    TextObserver t{&d};

    t.notify();

    d.drop();
    t.notify();

    // Moving next to current and generating next
    d.moveNextToCurrent();
    t.notify();

    d.insertCurrentBlock();
    d.generateNextBlock();
    d.setNextBlock();
    t.notify();

    d.drop();
    t.notify();

    d.moveNextToCurrent();
    d.insertCurrentBlock();
    d.generateNextBlock();
    d.setNextBlock();
    t.notify();

    d.right();
    d.right();
    d.drop();
    d.moveNextToCurrent();
    d.insertCurrentBlock();
    d.generateNextBlock();
    d.setNextBlock();
    t.notify();

    d.right();
    d.right();
    d.right();
    d.right();
    d.right();
    d.right();
    d.right();
    d.right();
    d.right();
    d.right();
    t.notify();
  }
