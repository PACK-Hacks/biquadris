#include <iostream>
#include <vector>
#include "textobserver.h"

using namespace std;

int main() {
    ifstream blockFile{"blank.txt"};

    Display d{4, blockFile};


    d.print();
}


