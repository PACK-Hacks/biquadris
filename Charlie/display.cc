#include "display.h"

// Display::Display(int levelIndex, ifstream &blockFile) : levelIndex{levelIndex}, level{levels[levelIndex]}, blockFile{blockFile} {};
Display::Display(int levelIndex, ifstream &blockFile) : levelIndex{levelIndex}, blockFile{blockFile} {
    board[5][5] = make_unique<Cell>('T', 5, 5);

    Cell *cell1 = new Cell{'L', 0, 0};
    Cell *cell2 = new Cell{'L', 1, 0};
    Cell *cell3 = new Cell{'L', 2, 0};
    Cell *cell4 = new Cell{'L', 2, 1};
    currentBlock = make_unique<Block>(true, false, 0, 0, 3, cell1, cell2, cell3, cell4);
};

Display::~Display() {

}

// Returns the character of the
char Display::getState(int row, int col) {
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

// Level up, returns true if successful, false otherwise
bool Display::levelUp() {
    // Return false if the user is already at the max level
    if (levelIndex == MAXLEVEL) {
        return false;
    }

    // Otherwise, update the level accordingly
    levelIndex++;
    level = levels[levelIndex];
    return true;
}

// Level down, returns true if successful, false otherwise
bool Display::levelDown() {
    // Return false if the user is already at the min level
    if (levelIndex == MINLEVEL) {
        return false;
    }

    // Otherwise, update the level accordingly
    levelIndex--;
    level = levels[levelIndex];
    return true;
}

// Set the nextBlock as the currentBlock, returns true if successful, false otherwise
bool Display::moveNextToCurrent() {
    
}


// Finds a starting point to begin the a translation operation. Returns a valid pair of <x, y>
// coordinates if operation leaves the block in a valid destination and <-1, -1> otherwise
pair<int, int> Display::operationIsValid(int changeInX, int changeInY) {
    // Check to see if any of the cell coordinates obtained by moving the block is invalid
    for (auto cell : currentBlock->getAllCells()) {
        int destinationX = cell->getX() + changeInX;
        int destinationY = cell->getY() + changeInY;

        // Invalid if the destination is out of bounds
        if (destinationX < 0 || WIDTH <= destinationX) return false;
        if (destinationY < 0 || HEIGHT <= destinationY) return false;

        // Invalid if the destination is already occupied by a cell on the board
        if (board[destinationY][destinationX]) return false;


    }

    // Otherwise, desitination is valid
    return true;
}

// Insert the currentBlock on the board by filling positions on the board with corresponding Cell pointers
void Display::insertCurrentBlock() {
    for (auto cell : currentBlock->getAllCells()) {
        board[cell->getY()][cell->getX()] = unique_ptr<Cell>{cell};
    }
}

// Update the position of currentBlock's cells on the board
void Display::updateCurrentBlock(int changeInX, int changeInY) {
    // Empty destination, this is for moving the cells of the currentBlock one-by-one
    int emptyX, emptyY;

    // Find a currentBlock destination position that is empty on the board, there will be at least one
    for (auto cell : currentBlock->getAllCells()) {
        if (board[cell->getY()][cell->getX()] == nullptr) {
            emptyX = cell->getX();
            emptyY = cell->getY();

            break;
        }
    }

    // Move the cells one-by-one
    for (auto cell : currentBlock->getAllCells()) {
        emptyX = cell->getX();
        emptyY = cell->getY();
    }
}


// Move the currentBlock to the left. Return true if operation is successful and false otherwise
bool Display::left() {
    // Cancel operation if invalid
    if (!operationIsValid(-1, 0)) {
        return false;
    }

    // Updated coordinates of the cells in the currentBlock
    for (auto cell : currentBlock->getAllCells()) {
        cell->addToX(-1);
    }

    // Update currentBlock on board
    updateCurrentBlock(-1, 0);

    // Successful operation
    return true;
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