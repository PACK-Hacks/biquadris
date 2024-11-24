#include "display.h"


Display::Display(int levelIndex, ifstream &blockFile) : levelIndex{levelIndex}, level{levels[levelIndex]}, blockFile{blockFile} {};

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

// Let current 



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