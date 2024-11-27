#ifndef __DISPLAY__
#define __DISPLAY__
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <memory>
#include <algorithm>
#include "level.h"
#include "block.h"
#include "cell.h"
#include "subject.h"

using namespace std;

class Display: public Subject {
    const int NUM_RESERVE_ROWS = 3;
    const int NEXT_BLOCK_DOCK = 4;
    const int HEIGHT = 18;          // height includes the 15 rows of the board and 3 reserve rows
    const int WIDTH = 11;
    const int MAXLEVEL = 4;
    const int MINLEVEL = 0;

    // vector<Cell *> board(11, nullptr);

    shared_ptr<Cell> board[22][11]{nullptr};  // Board of cells resulting from placed blocks
    unique_ptr<Block> nextBlock = nullptr;
    unique_ptr<Block> currentBlock = nullptr;

    int score = 0;
    bool blind = false;
    bool lost = false;  // maybe
    int turnsSinceClear = 0;

    vector<unique_ptr<Level>> levels; // something
    int levelIndex;
    Level *level;
    ifstream &blockFile;

    bool clear();
    bool operationIsValid(int changeInX, int changeInY);
    // bool validRotate(vector<shared_ptr<Cell>> allCell);
    bool validPos();

    public:
        Display(int levelIndex, ifstream &blockFile);
        ~Display();

        char getState(int row, int col) const override;
        int getScore();
        int getNumReserveRows();
        int getNextBlockDock();
        int getWidth();
        int getHeight();
        int getTurnsSinceClear();

        void setNextBlock();
        void setHeavy(bool heavy=true);
        void setBlind(bool blind=true);

        void dropDummyCell();
        bool needDummy();


        bool levelUp();
        bool levelDown();
        void norandom(ifstream &f);
        void random();

        // returns true if the action causes the block to be dropped
        bool moveNextToCurrent();
        void generateNextBlock();
        Block *getCurrentBlock();
        void setCurrentBlock(char block);
        void setCurrentHeavy(bool heavy=true);

        // returns true if the action causes the block to be dropped
        bool left(int n=1);
        bool right(int n=1);
        bool down(int n=1);
        bool drop();
        bool clockwise();
        bool counterClockwise();


        // development functions
        void print();
    
        // functions to be private
        void insertCurrentBlock();
        void removeCurrentBlock();
        void place();
};


#endif
