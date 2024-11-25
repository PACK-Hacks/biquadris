#include "block.h"

// Block constructor
Block::Block(bool heavy, int rotationLen,
    Cell *cell1, Cell *cell2, Cell *cell3, Cell *cell4) :
     heavy{heavy}, rotationLen{rotationLen} {
        cells.emplace_back(shared_ptr<Cell>{cell1});
        cells.emplace_back(shared_ptr<Cell>{cell2});
        cells.emplace_back(shared_ptr<Cell>{cell3});
        cells.emplace_back(shared_ptr<Cell>{cell4});
}

// Block destructor
Block::~Block() {}

// Sets heavy field
void Block::setHeavy(bool heavy) {
    heavy = heavy;
}

// Gets all cells in the Block
vector<shared_ptr<Cell>> Block::getAllCells() const {
    return cells;
}

// Block::Block(bool active, bool heavy, int rotationLen, int bottomLeftX, int bottomLeftY, 
//     unique_ptr<Cell> cell1, unique_ptr<Cell> cell2, unique_ptr<Cell> cell3, unique_ptr<Cell> cell4) :
//     active{active}, heavy{heavy}, rotationLen{rotationLen}, bottomLeftX{bottomLeftX}, bottomLeftY{bottomLeftY} {}


// IBlock constructor
IBlock::IBlock(bool heavy) : Block{heavy, 4,
    new Cell{'I', 0, 0},
    new Cell{'I', 0, 1},
    new Cell{'I', 0, 2},
    new Cell{'I', 0, 3}} {}

// OBlock constructor
OBlock::OBlock(bool heavy) : Block{heavy, 2,
    new Cell{'O', 0, 2},
    new Cell{'O', 0, 3},
    new Cell{'O', 1, 2},
    new Cell{'O', 1, 3}} {}

// LBlock constructor
LBlock::LBlock(bool heavy) : Block{heavy, 3,
    new Cell{'L', 0, 1},
    new Cell{'L', 0, 2},
    new Cell{'L', 0, 3},
    new Cell{'L', 1, 3}} {}

// JBlock constructor
JBlock::JBlock(bool heavy) : Block{heavy, 3,
    new Cell{'J', 1, 1},
    new Cell{'J', 1, 2},
    new Cell{'J', 1, 3},
    new Cell{'J', 0, 3}} {}

// TBlock constructor
TBlock::TBlock(bool heavy) : Block{heavy, 3,
    new Cell{'T', 0, 2},
    new Cell{'T', 1, 2},
    new Cell{'T', 1, 3},
    new Cell{'T', 2, 2}} {}

// SBlock constructor
SBlock::SBlock(bool heavy) : Block{heavy, 3,
    new Cell{'S', 0, 3},
    new Cell{'S', 1, 3},
    new Cell{'S', 1, 2},
    new Cell{'S', 2, 2}} {}

// ZBlock constructor
ZBlock::ZBlock(bool heavy) : Block{heavy, 3,
    new Cell{'Z', 0, 2},
    new Cell{'Z', 1, 2},
    new Cell{'Z', 1, 3},
    new Cell{'Z', 2, 3}} {}
