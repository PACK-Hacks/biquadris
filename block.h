#ifndef __BLOCK__
#define __BLOCK__
#include <vector>
#include "cell.h"

class Block {
    bool active;
    bool heavy;
    int rotationLen;
    int bottomLeftX;
    int bottomLeftY;

    public:
    void clearBlockFromboard();
    void insertBlockFromBoard();
    vector<Cell*> getAllCells();
    void clockwise();
    void counterClockwise();

    
};


#endif
