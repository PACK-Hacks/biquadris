#ifndef __BLOCK__
#define __BLOCK__
#include <memory>
#include <vector>
#include <algorithm>
#include "cell.h"

using namespace std;

class Block {
    bool isNextBlock;
    bool heavy;
    int rotationLen;
    int level;

    protected:
        int bottomLeftX = 0;
        int bottomLeftY = 3;
        vector<shared_ptr<Cell>> cells;

    public:
        Block(bool heavy, int rotationLen, int level,
            Cell *cell1, Cell *cell2, Cell *cell3, Cell *cell4);
        virtual ~Block()=0;


        void setHeavy(bool heavy);
        bool isHeavy();

        int getLevel();

        vector<shared_ptr<Cell>> getAllCells() const;

        void moveBlockX(int n);
        void moveBlockY(int n);
        
        pair<int, int> getBottomLeftCoor();
        int getRotationLen();
        
        virtual void clockwise();
        virtual void counterClockwise();

};

class IBlock final: public Block {
    public:
        IBlock(bool heavy, int level);
};

class OBlock final: public Block {
    public:
        OBlock(bool heavy, int level);
};

class LBlock final: public Block {
    public:
        LBlock(bool heavy, int level);
};

class JBlock final: public Block {
    public:
        JBlock(bool heavy, int level);
};

class TBlock final: public Block {
    public:
        TBlock(bool heavy, int level);
};

class SBlock final: public Block {
    public:
        SBlock(bool heavy, int level);
};

class ZBlock final: public Block {
    public:
        ZBlock(bool heavy, int level);
};


#endif
