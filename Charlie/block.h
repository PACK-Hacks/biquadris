#ifndef __BLOCK__
#define __BLOCK__
#include <memory>
#include <vector>
#include "cell.h"

using namespace std;

class Block {
    bool active = false;
    bool heavy = false;
    int bottomLeftX = 0;
    int bottomLeftY = 0;

    int rotationLen;

    vector<shared_ptr<Cell>> cells;

    public:
        Block(bool active, bool heavy, int bottomLeftX, int bottomLeftY, int rotationLen,
            Cell *cell1, Cell *cell2, Cell *cell3, Cell *cell4);

        vector<shared_ptr<Cell>> getAllCells() const;

        // Block(bool active = false, bool heavy = false, int rotationLen, int bottomLeftX = 0, int bottomLeftY = 0);
};


#endif
