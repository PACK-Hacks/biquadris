#ifndef __GameDisplay_H__
#define __GameDisplay_H__
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <memory>
#include <algorithm>
#include <utility>
#include <set>
#include "level.h"
#include "block.h"
#include "cell.h"
#include "subject.h"
#include "window.h"


using namespace std;

class GameDisplay: public Subject {
    const int NUM_RESERVE_ROWS = 3;
    const int NEXT_BLOCK_DOCK = 2;
    const int HEIGHT = 18;          // height includes the 15 rows of the board and 3 reserve rows
    const int WIDTH = 11;
    const int MAXLEVEL = 4;
    const int MINLEVEL = 0;

    const int SPECIAL_HEAVY_DROP = 2;

    // vector<Cell *> board(11, nullptr);

    shared_ptr<Cell> board[20][11]{nullptr};  // Board of cells resulting from placed blocks
    unique_ptr<Block> nextBlock = nullptr;
    unique_ptr<Block> currentBlock = nullptr;
    vector<unique_ptr<Block>> activePlacedBlocks;
    
    set<pair<int, int>> movedCells;

    int score = 0;
    int highScore = 0;
    bool specialHeavy = false;
    bool lost = false;  // maybe
    int turnsSinceClear = 0;

    vector<unique_ptr<Level>> levels; // something
    int levelIndex;
    Level *level;

    string blockFileString;
    ifstream blockFile;
    ifstream f{"file.txt"};

    void clear(int bottomRowToScan, int numRowstoScan);
    bool operationIsValid(int changeInX, int changeInY);
    // bool validRotate(vector<shared_ptr<Cell>> allCell);
    bool validPos();

    void addCurrBlockCells();

    bool special = false;

    public:
        GameDisplay(int levelIndex, string blockFileString);
        ~GameDisplay();

        char getState(int row, int col) const override;
        int getScore();
        int getHighScore();
        int getLevel();
        int getNumReserveRows();
        int getNextBlockDock();
        int getWidth();
        int getHeight();
        int getTurnsSinceClear();
        bool getLost();

        // void setNextBlock();
        void setHeavy(bool heavy=true);

        void dropDummyCell();
        bool needDummy();

        void reset();

        void clearMovedCells();
        set<pair<int,int>> getMovedCells();
        


        bool levelUp(int n=1);
        bool levelDown(int n=1);
        void norandom(string f_name);
        void random();
        bool norand = false;

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
        bool clockwise(int n=1);
        bool counterClockwise(int n=1);
        

        // development functions
        void print();
    
        // functions to be private
        void insertCurrentBlock();
        void removeCurrentBlock();
        void place();


        bool getSpecial();
        void setSpecial(bool sp);

        void insertBlindBlock();
        void forceBlock();

};


#endif
