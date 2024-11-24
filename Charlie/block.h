#ifndef __BLOCK__
#define __BLOCK__
#include <memory>
#include <vector>
#include "cell.h"

using namespace std;

class Block {
    bool isNextBlock;
    bool heavy;
    int bottomLeftX = 0;
    int bottomLeftY = 0;

    int rotationLen;

    vector<shared_ptr<Cell>> cells;

    public:
        Block(bool isNextBlock, bool heavy, int rotationLen,
            Cell *cell1, Cell *cell2, Cell *cell3, Cell *cell4);

        vector<shared_ptr<Cell>> getAllCells() const;


        // Block(bool active = false, bool heavy = false, int rotationLen, int bottomLeftX = 0, int bottomLeftY = 0);
};

class IBlock: public Block {
    public:
        IBlock(bool isNextBlock, bool heavy);
};

class OBlock: public Block {
    public:
        OBlock(bool isNextBlock, bool heavy);
};

class LBlock: public Block {
    public:
        LBlock(bool isNextBlock, bool heavy);
};

class JBlock: public Block {
    public:
        JBlock(bool isNextBlock, bool heavy);
};

class TBlock: public Block {
    public:
        TBlock(bool isNextBlock, bool heavy);
};

class SBlock: public Block {
    public:
        SBlock(bool isNextBlock, bool heavy);
};

class ZBlock: public Block {
    public:
        ZBlock(bool isNextBlock, bool heavy);
};


#endif
