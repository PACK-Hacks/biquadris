#include "display.h"
#include "cell.h"
// Display::Display(int levelIndex, ifstream &blockFile) : levelIndex{levelIndex}, level{levels[levelIndex]}, blockFile{blockFile} {};
Display::Display(int levelIndex, ifstream &blockFile) : levelIndex{levelIndex}, blockFile{blockFile} {
    board[5][5] = make_unique<Cell>('T');
};

Display::~Display() {

}

// Returns the character of the
char Display::charAt(int row, int col) {
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
// bool Display::moveNextToCurrent() {

// }

// void Display::print() {
//     cout << "+";
//     for (int j = 0; j < WIDTH; j++) {
//         cout << "-";
//     }
//     cout << "+" << endl;

//     for (int i = 0; i < HEIGHT; i++) {
//         cout << "|";
//         for (int j = 0; j < WIDTH; j++) {
//             if (board[i][j]) {
//                 cout << board[i][j]->getChar();
//             }
//             else {
//                 cout << " ";
//             }
//         }
//         cout << "|" << endl;
//     }

//     cout << "+";
//     for (int j = 0; j < WIDTH; j++) {
//         cout << "-";
//     }
//     cout << "+" << endl;
// }

int seperate = 10;
int highScore = 100;
int levelIndex = 0;
int score = 0;

// reserve three extra rows for different cell types at top of the baord for rotationn
void Display::print() {
    // High Score 
    cout << endl;
    cout << "High Score:     " << highScore << endl;

    // level
    cout << "Level:     " << levelIndex;

    for (int i = 0; i <= seperate; ++i) cout << ' '; // reserve three extra rows

    cout << "Level:     " << levelIndex << endl;

    // score
    cout << "Score:     " << score;

    for (int i = 0; i <= seperate; ++i) cout << ' '; // reserve three extra rows

    cout << "Score:     " << levelIndex << endl;



    // top margin for player1
    for (int i = 0; i <= WIDTH; ++i) cout << '-'; // reserve three extra rows

    // seperate
    for (int i = 0; i <= seperate; ++i) cout << ' '; // reserve three extra rows

    // top margin for player1
    for (int i = 0; i <= WIDTH; ++i) cout << '-'; // reserve three extra rows

    cout << endl;

    // board
    for (int i = 0; i <= HEIGHT; ++i) {

        // plaer1 board
        for (int j = 0; j <= WIDTH; ++j) {
            // out << subject->getState(i, j); // retrieved from Display 
            cout << 'T'; // retrieved from Display 

        }

        // seperate
        for (int i = 0; i <= seperate; ++i) cout << ' '; // reserve three extra rows

        // plaer2 board
        for (int j = 0; j <= WIDTH; ++j) {
            // out << subject->getState(i, j); // retrieved from Display 
            cout << 'L'; // retrieved from Display 
        }

        cout << endl;

    }

    // bottom margin for player1
    for (int i = 0; i <= WIDTH; ++i) cout << '-'; // reserve three extra rows

    // seperate
    for (int i = 0; i <= seperate; ++i) cout << ' '; // reserve three extra rows

    // bottom margin for player2
    for (int i = 0; i <= WIDTH; ++i) cout << '-'; // reserve three extra rows
    
    cout << endl;

    cout << "Next:       "; 

    for (int i = 0; i <= seperate; ++i) cout << ' '; // reserve three extra rows

    cout << "Next:       " << end;

    // bottom margin
    cout << "getNextBook()";
    
    cout << "          ";

    cout << "getNextBook()" << endl;


    // where is generateNextBlock() called?  
    // should there be a nextBlock field? 

}

char Display::getState(int row, int col) const {
    // return Display->charAt(row, col, ticks);
    // return board[row][col].getChar(); 
    // unique_ptr<Cell> board[15][11]{nullptr}; 
    return 'T';
    // return board[15][11].getChar
}




















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