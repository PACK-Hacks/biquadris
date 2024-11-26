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

    // vector<shared_ptr<Cell>> testCells;

    // Cell(char letter, int x, int y);

    // Cell *cell1{cells[0]->getChar(), cells[0]->getX(), cells[0]->getY()};
    // Cell *cell2{cells[1]->getChar(), cells[1]->getX(), cells[1]->getY()};
    // Cell *cell3{cells[2]->getChar(), cells[2]->getX(), cells[2]->getY()};
    // Cell *cell4{cells[3]->getChar(), cells[3]->getX(), cells[3]->getY()};

    // testCells.emplace_back(cell1);
    // testCells.emplace_back(cell2);
    // testCells.emplace_back(cell3);
    // testCells.emplace_back(cell4);

    // construct cell 

    for (int i = 0; i < 4; i++) {
        int x = cells[i]->getX();
        int y = cells[i]->getY();

        int localX = x - bottomLeftX; // Convert to 0-based relative to bottom-left
        int localY = y - bottomLeftY; // Convert to 0-based relative to bottom-left

        // Validate i and j are within the 3x3 matrix

        // Transpose: swap localI and localJ
        int transposedX = localY;
        int transposedY = localX;

        // Reverse: Flip the i (row index)
        int reversedX = 2 - transposedX;

        // Convert back to global coordinates
        int newX = bottomLeftX + reversedX;
        int newY = bottomLeftY + transposedY;


        // Cell *cell1{cells[0]->getChar(), cells[0]->getX(), cells[0]->getY()};
        // cells[i]->x = newX;
        // cells[i]->y = newY;
        cells[i]->addToX(newX - x);
        cells[i]->addToY(newY - y);
    }

    // returns vector<shared_ptr<Cell>> allCell
}

void Block::counterClockwise() {
    clockwise();
    clockwise();
    clockwise();
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
