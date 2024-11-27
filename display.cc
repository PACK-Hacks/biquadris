#include "display.h"

// Display::Display(int levelIndex, ifstream &blockFile) : levelIndex{levelIndex}, level{levels[levelIndex]}, blockFile{blockFile} {};
Display::Display(int levelIndex, string blockFileString) : levelIndex{levelIndex}, blockFileString{blockFileString},
blockFile{blockFileString} {
    string file_name = "file.txt";
    
    levels.emplace_back(make_unique<Level0>(blockFile, blockFileString, f, file_name));
    levels.emplace_back(make_unique<Level1>(blockFile, blockFileString, f, file_name));
    levels.emplace_back(make_unique<Level2>(blockFile, blockFileString, f, file_name));
    levels.emplace_back(make_unique<Level3>(blockFile, blockFileString, f, file_name));
    levels.emplace_back(make_unique<Level4>(blockFile, blockFileString, f, file_name));

    level = levels[levelIndex].get();
};

Display::~Display() {

}
bool Display::getSpecial() {
    return special;
}
void Display::setSpecial(bool sp) {
    special = sp;
}



// Returns the character of the
char Display::getState(int row, int col) const {
    // If there is a cell at that position on the board, return its character
    if (board[row][col]) {
        return board[row][col]->getChar();
    }

    // Otherwise, return blank
    return ' ';
}

// Gets the score of the display
int Display::getScore() {
    return score;
}

// Gets the level of the Display
int Display::getLevel() {
    return levelIndex;
}

// Gets number of turns since last clear
int Display::getTurnsSinceClear() {
    return turnsSinceClear;
}

// Returns true if Dummy is needed in Level 4
bool Display::needDummy() {
    turnsSinceClear++;
    if (turnsSinceClear%5 == 0 && turnsSinceClear != 0) return true;
    return false;
}


// Sets the heavy field
void Display::setHeavy(bool heavy) {
    specialHeavy = heavy;
}

// Sets the blind field
void Display::setBlind(bool blind) {
    blind = blind;
}

// It teleports through right now
// Drops a 1x1 block on the center column
void Display::dropDummyCell() {
    const int centerX = WIDTH / 2;

    // Find the lowest empty row in the center column
    int destY = 0;
    while (board[destY][centerX] == nullptr && destY < HEIGHT) {
        destY++;
    }
    destY--;

    // Populate it with a dummy cell
    board[destY][centerX] = make_shared<Cell>('*', centerX, destY);
}

// Sets nextBlock on the next block dock
void Display::setNextBlock() {
    // Clear next block dock
    for (int i = 0; i < NEXT_BLOCK_DOCK; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            board[i + HEIGHT][j] = nullptr;
        }
    }

    for (auto cell : nextBlock->getAllCells()) {
        board[cell->getY() + HEIGHT][cell->getX()] = cell;
    }
}

// // Level up, returns true if successful, false otherwise
// bool Display::levelUp() {
//     // Return false if the user is already at the max level
//     if (levelIndex == MAXLEVEL) {
//         return false;
//     }

//     // Otherwise, update the level accordingly
//     levelIndex++;
//     level = levels[levelIndex];
//     return true;
// }

// // Level down, returns true if successful, false otherwise
// bool Display::levelDown() {
//     // Return false if the user is already at the min level
//     if (levelIndex == MINLEVEL) {
//         return false;
//     }

//     // Otherwise, update the level accordingly
//     levelIndex--;
//     level = levels[levelIndex];
//     return true;
// }

// Set the nextBlock as the currentBlock, returns true if successful, false otherwise
bool Display::moveNextToCurrent() {
    currentBlock = move(nextBlock);
    insertCurrentBlock();
    return true;
}

// Generate the nextBlock
void Display::generateNextBlock() {
    nextBlock = unique_ptr<Block>(level->makeBlock());
    // Clear next block dock
    for (int i = 0; i < NEXT_BLOCK_DOCK; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            board[i + HEIGHT][j] = nullptr;
        }
    }

    for (auto cell : nextBlock->getAllCells()) {
        board[cell->getY() + HEIGHT][cell->getX()] = cell;
    }
}


// Override the currentBlock
void Display::setCurrentBlock(char block) {
    currentBlock = unique_ptr<Block>(level->makeChosenBlock(block));
    insertCurrentBlock();
}

// Override the currentBlock's heavy field
void Display::setCurrentHeavy(bool heavy) {
    // currentBlock->setHeavy(heavy);
    specialHeavy = heavy;
}


// Check the validity of a block operation. Returns true if operation leaves the block in a valid destination and false otherwise
bool Display::operationIsValid(int changeInX, int changeInY) {
    // Check to see if any of the cell coordinates obtained by moving the block is invalid
    for (auto cell : currentBlock->getAllCells()) {
        int destinationX = cell->getX() + changeInX;
        int destinationY = cell->getY() + changeInY;

        // Invalid if the destination is out of bounds
        if (destinationX < 0 || WIDTH <= destinationX) return false;
        if (destinationY < 0 || HEIGHT <= destinationY) return false;

        // Invalid if the destination is already occupied by a cell on the board that is not part of currentBlock
        if (board[destinationY][destinationX] &&
            board[destinationY][destinationX]->getRealChar() != '/') return false;
    }

    // Otherwise, destination is valid
    return true;
}
bool Display::validPos() {

    // // Invalid if the destination is already occupied by a cell on the board that is not part of currentBlock
    // for (int i = 0; i < 4; i++) {
    //     int x = (currentBlock->getAllCells())[i]->getX();
    //     int y = (currentBlock->getAllCells())[i]->getY();
    //     if (board[x][y] && board[x][y]->getRealChar() != '/') return false;
    // }
    
    // // Otherwise, destination is valid
    // return true;

    for (auto cell : currentBlock->getAllCells()) {
        int x = cell->getX();
        int y = cell->getY();
  
        // Invalid if the destination is out of bounds
        if (x < 0 || WIDTH <= x) return false;
        if (y < 0 || HEIGHT <= y) return false;

        // Invalid if the destination is already occupied by a cell on the board that is not part of currentBlock
        if (board[y][x] && board[y][x]->getRealChar() != '/') {cout << "cccccccc" << endl; return false;}
    }
    return true;
}


// Insert the currentBlock on the board by filling positions on the board with corresponding Cell pointers
void Display::insertCurrentBlock() {
    for (auto cell : currentBlock->getAllCells()) {
        board[cell->getY()][cell->getX()] = cell;
    }
}

// Remove the currentBlock on the board by ridding positions on the board of corresponding Cell pointers
void Display::removeCurrentBlock() {
    for (auto cell : currentBlock->getAllCells()) {
        board[cell->getY()][cell->getX()] = nullptr;
    }
}

// Confirm placing currentBlock on the board, and reflecting the change in the state of currentBlock
void Display::place() {
    for (auto cell : currentBlock->getAllCells()) {
        cell->place();
    }

    int currentBlockFloor = currentBlock->getBottomLeftCoor().second;
    int currentBlockRotationLen = currentBlock->getRotationLen();

    // Move currentBlock to activePlacedBlocks
    activePlacedBlocks.emplace_back(move(currentBlock));

    clear(currentBlockFloor, currentBlockRotationLen);

    // Reset display to default values
    blind = false;
    specialHeavy = false;

    // If there are any cells in the reserve rows, set lost to true
    for (int i = 0; i < WIDTH; ++i) {
        if (board[2][i]) {
            lost = true;
            break;
        }
    }
}


// Move the currentBlock to the left n units. Return true if operation places block and false otherwise
bool Display::left(int n) {
    removeCurrentBlock();

    // Determine if what kind of heavy exists, special heavy or block heavy
    int heavy;
    // If the block is heavy, the block will be shifted down by one unit
    heavy = currentBlock->isHeavy();

    // If there is a special heavy, the block will be shifted by two
    if (specialHeavy) {
        heavy = SPECIAL_HEAVY_DROP;
    }

    // Cancel operation if it is invalid to move horizontally, insert currentBlock back to original position
    if (!operationIsValid(-n, 0)) {
        insertCurrentBlock();
        return false;
    }

    // Move block right -n units
    currentBlock->moveBlockX(-n);

    // If it is invalid to move the block down heavy units, drop the block and return true
    if (!operationIsValid(0, heavy)) {
        drop();
        return true;
    }

    // Otherwise, move the block down heavy units
    currentBlock->moveBlockY(heavy);

    // Insert currentBlock on board
    insertCurrentBlock();

    // Successful operation
    return false;
}


// Move the currentBlock to the right n units. Return true if operation places block and false otherwise
bool Display::right(int n) {
    removeCurrentBlock();

    // Determine if what kind of heavy exists, special heavy or block heavy
    int heavy;
    // If the block is heavy, the block will be shifted down by one unit
    heavy = currentBlock->isHeavy();

    // If there is a special heavy, the block will be shifted by two
    if (specialHeavy) {
        cout << "Charlie 2" << endl;
        heavy = SPECIAL_HEAVY_DROP;
    }

    // Cancel operation if it is invalid to move horizontally, insert currentBlock back to original position
    if (!operationIsValid(n, 0)) {
        insertCurrentBlock();
        return false;
    }

    // Move block right n units
    currentBlock->moveBlockX(n);

    // If it is invalid to move the block down heavy units, drop the block and return true
    if (!operationIsValid(0, heavy)) {
        drop();
        return true;
    }

    // Otherwise, move the block down heavy units
    currentBlock->moveBlockY(heavy);

    // Insert currentBlock on board
    insertCurrentBlock();

    // Successful operation
    return false;
}

// Move the currentBlock down n units. Return true if operation places block and false otherwise
bool Display::down(int n) {
    removeCurrentBlock();

    // Cancel operation if invalid, insert currentBlock back to original position
    if (!operationIsValid(0, n)) {
        insertCurrentBlock();
        return false;
    }

    // Move the block down
    currentBlock->moveBlockY(n);

    // Insert currentBlock on board
    insertCurrentBlock();

    // Successful operation
    return false;
}

// Drop the currentBlock. Return true
bool Display::drop() {
    removeCurrentBlock();

    // Try dropping the block down all the way to lowest row. If unsuccesful, try dropping 
    // one row higher until the operation is successful
    int dropHeight = 1;

    while (operationIsValid(0, dropHeight)) {
        dropHeight++;
    }

    currentBlock->moveBlockY(dropHeight - 1);

    // Insert currentBlock on board
    insertCurrentBlock();

    // Place block
    place();

    // Successful operation
    return true;
}


bool Display::clockwise() {
    removeCurrentBlock();

    // If the block is heavy, the block will be shifted down by one unit
    int heavy = currentBlock->isHeavy();

    currentBlock->clockwise();


    // invalid
    if (!validPos()) {
        currentBlock->counterClockwise();
        // Insert currentBlock on board
        insertCurrentBlock();
        return false;
    }

    // If it is invalid to move the block down heavy units, drop the block and return true
    if (!operationIsValid(0, heavy)) {
        drop();
        return true;
    }

    // Otherwise, move the block down heavy units
    currentBlock->moveBlockY(heavy);

    // Insert currentBlock on board
    insertCurrentBlock();

    // valid 
    return false;
}

bool Display::counterClockwise() {
    removeCurrentBlock();

    // If the block is heavy, the block will be shifted down by one unit
    int heavy = currentBlock->isHeavy();

    currentBlock->counterClockwise();

    // invalid
    if (!validPos()) {
        currentBlock->clockwise();
        // Insert currentBlock on board
        insertCurrentBlock();
        return false;
    }

    // Otherwise, move the block down heavy units
    currentBlock->moveBlockY(heavy);

    // Insert currentBlock on board
    insertCurrentBlock();

    // heavy implementation
    // valid 
    return false;
}

// takes in block from the file: relevent in level 3 and 4 only
void Display::norandom(string f_name) {

    levels[3]->setNoRandom(f_name, f);
    levels[4]->setNoRandom(f_name, f);
    
}

// restore randomness: relevent in level 3 and 4 only
void Display::random() {
    
}

void Display::clear(int bottomRowToScan, int numRowstoScan) {
    int numRowsClear = 0; 
    int topRowToScan = bottomRowToScan - numRowstoScan + 1;
    
    // basic clear
    for (int i = topRowToScan; i <= bottomRowToScan; i++) {
        // The row needs to be clear if none of its cells are empty
        bool clear = true; 
        for (int j = 0; j < WIDTH; j++) {
            if (board[i][j] == nullptr) clear = false;
        }
        
        if (clear)  {
            // Clear the row by setting the cells to nullptr
            for  (int j = 0; j < WIDTH; j++) {
                board[i][j] == nullptr;
            }

            // Shift every cell in the rows above down by one
            for (int n = i; n > 0; n--) {
                for (int m = 0; m < WIDTH; m++) {
                    board[n][m] = board[n-1][m]; 
                }
            }

            numRowsClear++;
        }
    }

    // Update score
    score += (levelIndex + numRowsClear) * (levelIndex + numRowsClear); 

    // reset turnsSinceClear if any rows are cleared
    if (numRowsClear >= 1) turnsSinceClear = 0;


    // if clears two or more rows, prompts the player a special action
    cout << numRowsClear << endl;
    if (numRowsClear >= 2) {
        special = true;
    }
}

void Display::insertBlindBlock() {
    for (int i = 3; i < 12; i++) {
        for (int j = 3; j < 9; j++) {
            board[i][j] = make_shared<Cell>('?', j, i); // not valid
        }
    }
}




void Display::print() {
    cout << "+";
    for (int j = 0; j < WIDTH; j++) {
        cout << "-";
    }
    cout << "+" << endl;

    for (int i = 0; i < HEIGHT; i++) {
        cout << "|";
        for (int j = 0; j < WIDTH; j++) {
            if (board[i][j]) {
                cout << board[i][j]->getChar();
            }
            else {
                cout << " ";
            }
        }
        cout << "|" << endl;
    }

    cout << "+";
    for (int j = 0; j < WIDTH; j++) {
        cout << "-";
    }
    cout << "+" << endl;
}

int Display::getNumReserveRows() {
    return NUM_RESERVE_ROWS;
}

int Display::getNextBlockDock() {
    return NEXT_BLOCK_DOCK;
}

int Display::getWidth() {
    return WIDTH;
}

int Display::getHeight() {
    return HEIGHT;
}

bool Display::getLost() {
    return lost;
}
