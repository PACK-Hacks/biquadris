#ifndef __BLOCK__
#define __BLOCK__
#include <memory>
#include "cell.h"

using namespace std;

class Block {
    bool active = false;
    bool heavy = false;
    int bottomLeftX = 0;
    int bottomLeftY = 0;

    int rotationLen;

    unique_ptr<Cell> cell1 = nullptr;
    unique_ptr<Cell> cell2 = nullptr;
    unique_ptr<Cell> cell3 = nullptr;
    unique_ptr<Cell> cell4 = nullptr;

    public:
        Block(bool active, bool heavy, int bottomLeftX, int bottomLeftY, int rotationLen,
        unique_ptr<Cell> cell1, unique_ptr<Cell> cell2, unique_ptr<Cell> cell3, unique_ptr<Cell> cell4);

        // Block(bool active = false, bool heavy = false, int rotationLen, int bottomLeftX = 0, int bottomLeftY = 0);
};


#endif
