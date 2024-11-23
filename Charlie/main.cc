#include "display.h"
#include <fstream>

using namespace std;

int main() {
    ifstream blockFile{"blank.txt"};

    Display d{4, blockFile};

    d.insertCurrentBlock();
    d.print();
}
