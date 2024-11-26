#include "display.h"

// Display::Display(int levelIndex, ifstream &blockFile) : levelIndex{levelIndex}, level{levels[levelIndex]}, blockFile{blockFile} {};
Display::Display(int levelIndex, ifstream &blockFile) : levelIndex{levelIndex}, blockFile{blockFile} {
    levels.emplace_back(make_unique<Level0>(blockFile));
    levels.emplace_back(make_unique<Level1>(blockFile));
    levels.emplace_back(make_unique<Level2>(blockFile));
    levels.emplace_back(make_unique<Level3>(blockFile));
    levels.emplace_back(make_unique<Level4>(blockFile));

    level = levels[levelIndex].get();

    currentBlock = unique_ptr<Block>(level->makeBlock());
    nextBlock = unique_ptr<Block>(level->makeBlock());
};

Display::~Display() {

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
    heavy = heavy;
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
}

// Generate the nextBlock
void Display::generateNextBlock() {
    nextBlock = unique_ptr<Block>(level->makeBlock());
}


// Override the currentBlock
void Display::setCurrentBlock(char block) {
    currentBlock = unique_ptr<Block>(level->makeChosenBlock(block));
}

// Override the currentBlock's heavy field
void Display::setCurrentHeavy(bool heavy) {
    currentBlock->setHeavy(heavy);
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
        if (x < 0 || WIDTH <= x){ cout << "aaaaaaaaaaaa" << endl; return false;}
        if (y < 0 || HEIGHT <= y) {cout << "bbbbbbbbbbb" << endl;  return false;}

        // Invalid if the destination is already occupied by a cell on the board that is not part of currentBlock
        if (board[y][x] && board[y][x]->getRealChar() != '/') {cout << "cccccccc" << endl; return false;}
    }
    return true;
}




// bool Display::ValidRotate(vector<shared_ptr<Cell>> allCell) {
//     for (auto c : allCell) {
//         if (board[c->getX][c->getY] &&
//                 board[c->getX][c->gety]->getRealChar() != '/') return false;
//     }

// int Display::validRotate() {
//     int botLeftConerRow = 0;
//     int botLeftConerCol = 0; 

//     for (auto cell: currentBlock->getAllCells()) {
//         if (botLeftConerRow < cell->getX()) botLeftConerRow = cell->getX();
//         if (botLeftConerCol < cell->getY()) botLeftConerRow = cell->getY();
//     }
//     return left

// }


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

    currentBlock = nullptr;

    // Reset display to default values
    blind = false;
}


// Move the currentBlock to the left n units. Return true if operation places block and false otherwise
bool Display::left(int n) {
    removeCurrentBlock();

    // If the block is heavy, the block will be shifted down by one unit
    int heavy = 2 * currentBlock->isHeavy();

    // Cancel operation if it is invalid to move horizontally, insert currentBlock back to original position
    if (!operationIsValid(-n, 0)) {
        insertCurrentBlock();
        return false;
    }

    // Updated coordinates of the cells in the currentBlock
    for (auto cell : currentBlock->getAllCells()) {
        cell->addToX(-n);
    }

    // Change the block's bottomLeftX
    currentBlock->addToBottomLeftX(-n);

    // If it is invalid to move the block down heavy units, drop the block and return true
    if (!operationIsValid(0, heavy)) {
        this->drop();
        return true;
    }

    // Otherwise, move the block down heavy units
    for (auto cell : currentBlock->getAllCells()) {
        cell->addToY(heavy);
    }

    // Insert currentBlock on board
    insertCurrentBlock();

    // Successful operation
    return false;
}


// Move the currentBlock to the right n units. Return true if operation places block and false otherwise
bool Display::right(int n) {
    removeCurrentBlock();

    // If the block is heavy, the block will be shifted down by one unit
    int heavy = 2 * currentBlock->isHeavy();

    // Cancel operation if it is invalid to move horizontally, insert currentBlock back to original position
    if (!operationIsValid(n, 0)) {
        insertCurrentBlock();
        return false;
    }

    // Updated coordinates of the cells in the currentBlock
    for (auto cell : currentBlock->getAllCells()) {
        cell->addToX(n);
    }

    // Change the block's bottomLeftX
    currentBlock->addToBottomLeftX(n);

    // If it is invalid to move the block down heavy units, drop the block and return true
    if (!operationIsValid(0, heavy)) {
        this->drop();
        return true;
    }

    // Otherwise, move the block down heavy units
    for (auto cell : currentBlock->getAllCells()) {
        cell->addToY(heavy);
    }

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

    // Updated coordinates of the cells in the currentBlock
    for (auto cell : currentBlock->getAllCells()) {
        cell->addToY(n);
    }

    // Change the block's bottomLeftY
    currentBlock->addToBottomLeftY(n);

    // Insert currentBlock on board
    insertCurrentBlock();

    // Successful operation
    return true;
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

    // Updated coordinates of the cells in the currentBlock
    for (auto cell : currentBlock->getAllCells()) {
        cell->addToY(dropHeight - 1);
    }

    // Change the block's bottomLeftY
    currentBlock->addToBottomLeftY(dropHeight - 1);

    // Insert currentBlock on board
    insertCurrentBlock();

    // Place block
    place();

    // Successful operation
    return true;
}


bool Display::clockwise() {
    removeCurrentBlock();
    currentBlock->clockwise();

    // invalid
    if (!validPos()) {
        cout << "fail";
        currentBlock->counterClockwise();
        // Insert currentBlock on board
        insertCurrentBlock();
        return false;
    }
    cout << "success";

    // Insert currentBlock on board
    insertCurrentBlock();

    //valid 
    return true;
}

// takes in block from the file: relevent in level 3 and 4 only
void Display::norandom(ifstream &f) {
    
}

// restore randomness: relevent in level 3 and 4 only
void Display::random() {
    
}



// bool Display::clockwise() {
//     // check boundaries first

//     // Transpose the board
//     // handle 'I' block

//     removeCurrentBlock();

//     // handle 'I' block
//     if (  ) {
//     // check if center is (width - 4) else invalid
//         if (!(WIDTH - bottomLeftX >= 3)) {
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
//     }
    
//     // handle 'O' block
//     else if ( currentBlock->getAllCells() ) {
//         insertCurrentBlock();
//     }

//     else {
//         if (!(WIDTH - bottomLeftX >= 2)) {
//             insertCurrentBlock();
//             return false;
//         }

//         for (int i = bottomLeftY - 2; i <= bottomLeftY; i++) {
//             for (int j = i; j < 3; j++) {
//                 std::swap(board[i][j], board[j][i]);
//             }
//         }

//         // Reverse each row
//         for (int i = bottomLeftY - 2; i <= bottomLeftY; i++) {
//             std::reverse(board[i], board[i] + 3);
//         }
//     }
//     return true;
// }









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

// // reserve three extra rows for different cell types at top of the baord for rotationn
// void Display::print() {
//     // High Score 
//     cout << endl;
//     cout << "High Score:     " << highScore << endl;

//     // level
//     cout << "Level:     " << levelIndex;

//     for (int i = 0; i <= seperate; ++i) cout << ' '; // reserve three extra rows

//     cout << "Level:     " << levelIndex << endl;

//     // score
//     cout << "Score:     " << score;

//     for (int i = 0; i <= seperate; ++i) cout << ' '; // reserve three extra rows

//     cout << "Score:     " << levelIndex << endl;



//     // top margin for player1
//     for (int i = 0; i <= WIDTH; ++i) cout << '-'; // reserve three extra rows

//     // seperate
//     for (int i = 0; i <= seperate; ++i) cout << ' '; // reserve three extra rows

//     // top margin for player1
//     for (int i = 0; i <= WIDTH; ++i) cout << '-'; // reserve three extra rows

//     cout << endl;

//     // board
//     for (int i = 0; i <= HEIGHT; ++i) {

//         // plaer1 board
//         for (int j = 0; j <= WIDTH; ++j) {
//             // out << subject->getState(i, j); // retrieved from Display 
//             cout << 'T'; // retrieved from Display 

//         }

//         // seperate
//         for (int i = 0; i <= seperate; ++i) cout << ' '; // reserve three extra rows

//         // plaer2 board
//         for (int j = 0; j <= WIDTH; ++j) {
//             // out << subject->getState(i, j); // retrieved from Display 
//             cout << 'L'; // retrieved from Display 
//         }

//         cout << endl;

//     }

//     // bottom margin for player1
//     for (int i = 0; i <= WIDTH; ++i) cout << '-'; // reserve three extra rows

//     // seperate
//     for (int i = 0; i <= seperate; ++i) cout << ' '; // reserve three extra rows

//     // bottom margin for player2
//     for (int i = 0; i <= WIDTH; ++i) cout << '-'; // reserve three extra rows
    
//     cout << endl;

//     cout << "Next:       "; 

//     for (int i = 0; i <= seperate; ++i) cout << ' '; // reserve three extra rows

//     cout << "Next:       " << end;

//     // bottom margin
//     cout << "getNextBook()";
    
//     cout << "          ";

//     cout << "getNextBook()" << endl;


//     // where is generateNextBlock() called?  
//     // should there be a nextBlock field? 

// }




// class Display {
//     const int width = 11;
//     const int height = 15;
    
//     clear() {
//         // track num of cleared rows
//         score += calcScore(numCleared);
//     }

//     place() {  // runs clearing code, and char conversion, turning the block state 
//                 // from moving to placed
//         clear();    // check rows of each cell 1, 2, 3, 4, for each distinct row,
//                     // check if it's clearable, make all cells on row nullptr use getCellAt,
//                     // call fall with row and shift num
//     }


//     public:
//         render();
//         drop() {
//             // move block down
//             // once you hit the bottom
//             place();
//         }

//         // When a block is being moved, store its characters as '\', once it's placed  
//         // turn it into the proper characters. Easier to check collisions.
//         // charAt decrypts
//         right() {
//             clearBlockFromBoard()
            
//             currentBlock.cell1->addX(1);
//             currentBlock.cell2->addX(1);
//             currentBlock.cell3->addX(1);
//             currentBlock.cell4->addX(1);

//             if (currentBlock.heavy) {
//                 currentBlock.cell1->addY(1);
//                 currentBlock.cell2->addY(1);
//                 currentBlock.cell3->addY(1);
//                 currentBlock.cell4->addY(1);
//             }
            
//             insertBlockFromBoard()
//         }
//         void moveNextToCurrent() {
//             currentBlock = nextBlock;
//         }

//         void generateNextBlock(string special) {
//             if (special == "") {
//                 nextBlock = level->makeBlock(file);     // ifstream initialized with file name in the constructor
//             } 
//             else if (special == "blind") {
//                 blind = true;
//             }
//             else if (special == "force") {
//                 // get the forced shape
//                 char forcedBlock;
//                 nextBlock = level->makeChosenBlock(block, shape);
//             }

//             // else {
//             //     stringstream iss{special};
//             //     string s;

//             //     block = level->getBlock();
//             //     heavy = level->getHeavy();
//             //     dummy = level->getDummy();


//             //     char forcedBlock;

//             //     while (iss >> s) {
//             //         if (s == "blind") {     // set nextBlind to false in drop method
//             //             isBlind = true;
//             //         }
//             //         if (s == "force") {
//             //             iss >> forcedBlock;
//             //         } 
//             //         if (s == "heavy") {
//             //             heavy = true;
//             //         }
//             //     }
//             // }
//         }

    


// };