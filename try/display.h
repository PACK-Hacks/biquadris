#ifndef __DISPLAY__
#define __DISPLAY__
#include <vector>
#include <fstream>
#include <string>
#include "level.h"
#include "block.h"
#include "cell.h"


using namespace std;

class Display {
    const int WIDTH = 11;
    const int HEIGHT = 15;
    const int MAXLEVEL = 4;
    const int MINLEVEL = 0;

    // vector<Cell *> board(11, nullptr);

    Cell *board[15][11];  // Board of cells resulting from placed blocks
    Block *nextBlock = nullptr;
    Block *currentBlock = nullptr;

    int score = 0;
    bool blind = false;
    bool heavy = false; // maybe
    bool force = false; // maybe
    bool lost = false;  // maybe
    // vector<Level *> levels = {}; // something

    int levelIndex;
    // Level *level;
    ifstream &blockFile;

    bool clear();

    public:
        Display(int levelIndex, ifstream &blockFile);
        ~Display();

        char charAt(int row, int col);
        int getScore();
        bool levelUp();
        bool levelDown();

        // returns true if the action causes the block to be dropped
        bool moveNextToCurrent();
        void generateNextBlock(string special);
        Block *getCurrentBlock();
        void setCurrentBlock(Block *block);

        // returns true if the action causes the block to be dropped
        bool left();
        bool right();
        bool down();
        bool drop();
        bool clockwise();
        bool counterClockwise();
};


#endif
