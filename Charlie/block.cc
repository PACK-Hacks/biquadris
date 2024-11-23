#include "block.h"

Block::Block(bool active, bool heavy, int bottomLeftX, int bottomLeftY, int rotationLen,
    unique_ptr<Cell> cell1, unique_ptr<Cell> cell2, unique_ptr<Cell> cell3, unique_ptr<Cell> cell4) :
    active{active}, heavy{heavy},  bottomLeftX{bottomLeftX}, bottomLeftY{bottomLeftY}, rotationLen{rotationLen},
    cell1{move(cell1)}, cell2{move(cell2)}, cell3{move(cell3)}, cell4{move(cell4)} {}

// Block::Block(bool active, bool heavy, int rotationLen, int bottomLeftX, int bottomLeftY, 
//     unique_ptr<Cell> cell1, unique_ptr<Cell> cell2, unique_ptr<Cell> cell3, unique_ptr<Cell> cell4) :
//     active{active}, heavy{heavy}, rotationLen{rotationLen}, bottomLeftX{bottomLeftX}, bottomLeftY{bottomLeftY} {}
