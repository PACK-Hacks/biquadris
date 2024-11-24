#include "block.h"

// Block constructor
Block::Block(bool active, bool heavy, int bottomLeftX, int bottomLeftY, int rotationLen,
    Cell *cell1, Cell *cell2, Cell *cell3, Cell *cell4) :
    active{active}, heavy{heavy},  bottomLeftX{bottomLeftX}, bottomLeftY{bottomLeftY}, rotationLen{rotationLen} {
        cells.emplace_back(shared_ptr<Cell>{cell1});
        cells.emplace_back(shared_ptr<Cell>{cell2});
        cells.emplace_back(shared_ptr<Cell>{cell3});
        cells.emplace_back(shared_ptr<Cell>{cell4});
}

// get all cells in the Block
vector<shared_ptr<Cell>> Block::getAllCells() const {
    return cells;
}

// Block::Block(bool active, bool heavy, int rotationLen, int bottomLeftX, int bottomLeftY, 
//     unique_ptr<Cell> cell1, unique_ptr<Cell> cell2, unique_ptr<Cell> cell3, unique_ptr<Cell> cell4) :
//     active{active}, heavy{heavy}, rotationLen{rotationLen}, bottomLeftX{bottomLeftX}, bottomLeftY{bottomLeftY} {}
