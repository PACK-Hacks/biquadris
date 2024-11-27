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

// Gets heavy field of Block
bool Block::isHeavy() {
    return heavy;
}

// Gets all cells in the Block
vector<shared_ptr<Cell>> Block::getAllCells() const {
    return cells;
}

// Adds n units to bottomLeftX
void Block::addToBottomLeftX(int n) {
    bottomLeftX += n;
}

// Adds n units to bottomLeftY
void Block::addToBottomLeftY(int n) {
    bottomLeftY += n;
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


// clockwise - returns vector<shared_ptr<Cell>>  of the changed block. 
void Block::clockwise() {
    // Track the how far right the rotation leaves the cell
    // by tracking the leftmost value of the resulting cells
    // these will be used as offsets to translate the cells 
    // to the bottomLeft coordinates
    int relOffsetX = rotationLen;

    for (auto cell : cells) {
        int x = cell->getX();
        int y = cell->getY();

        // Process: take transpose and flip vertically

        // Coordinate values relative to the bottom left coordinates
        int relX = x - bottomLeftX;
        int relY = bottomLeftY - y;

        // Relative transpose taken by swapping the relative coordinates
        int relTransposedX = relY;
        int relTransposedY = relX;

        // Flip the y value to reflect horizontal flip
        int reversedY = (rotationLen - 1) - relTransposedY;

        // Change cells with translation values
        cell->addToX(relTransposedX - relX);
        cell->addToY(relY - reversedY);

        // Update offset
        relOffsetX = min(relOffsetX, cell->getX());
    }

    // Translate cells to preserve bottomLeft coordinates
    for (auto cell : cells) {
        cell->addToX(-relOffsetX);
    }
}

void Block::counterClockwise() {
    // Track the how far right the rotation leaves the cell
    // by tracking the leftmost value of the resulting cells
    // these will be used as offsets to translate the cells 
    // to the bottomLeft coordinates
    int relOffsetX = rotationLen;

    for (auto cell : cells) {
        int x = cell->getX();
        int y = cell->getY();

        // Process: take transpose and flip horizontally

        // Coordinate values relative to the bottom left coordinates
        int relX = x - bottomLeftX;
        int relY = bottomLeftY - y;

        // Relative transpose taken by swapping the relative coordinates
        int relTransposedX = relY;
        int relTransposedY = relX;

        // Flip the x value to reflect horizontal flip
        int reversedX = (rotationLen - 1) - relTransposedX;

        // Change cells with translation values
        cell->addToX(reversedX - relX);
        cell->addToY(relY - relTransposedY);

        // Update offset
        relOffsetX = min(relOffsetX, cell->getX());
    }

    // Translate cells to preserve bottomLeft coordinates
    for (auto cell : cells) {
        cell->addToX(-relOffsetX);
    }
}


// void IBlock::clockwise() {


//     if (!(WIDTH - bottomLeftX >= 3)) {
//             insertCurrentBlock();
//             return false;
//         }
//         // transpose
//         for (int i = bottomLeftY - 3; i <= bottomLeftY; i++) {

//             for (int j = i; j < 4; j++) {
//                 std::swap(board[i][j], board[j][i]);
//             }
//         }

//         // Reverse each row
//         for (int i = bottomLeftY - 3; i <= bottomLeftY; i++) {
//             std::reverse(board[i], board[i] + 4);
//         }

    
//     // returns vector<shared_ptr<Cell>> allCell
    
// }
