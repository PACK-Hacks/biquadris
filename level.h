#ifndef __LEVEL__
#define __LEVEL__

#include <fstream>
#include "block.h"

using namespace std;

class Level {
    protected:
        bool heavy;
        int level;
        ifstream &blockFile;
        string blockFileString;
        char getNextBlockChar();

    public:
        Level(bool heavy, int level, ifstream &blockFile, string blockFileString);
        virtual ~Level()=0;

        virtual Block *makeBlock()=0;
        Block *makeChosenBlock(char block);
};

class Level0 final: public Level {
    public:
        Level0(ifstream &blockFile, const string &blockFileString);
        ~Level0();

        Block *makeBlock() override;
};

class Level1 final: public Level {
    public:
        Level1(ifstream &blockFile, const string &blockFileString);
        ~Level1();

        Block *makeBlock() override;
};

class Level2 final: public Level {
    public:
        Level2(ifstream &blockFile, const string &blockFileString);
        ~Level2();

        Block *makeBlock() override;
};

class Level3 final: public Level {
    public:
        Level3(ifstream &blockFile, const string &blockFileString);
        ~Level3();

        Block *makeBlock() override;
};

class Level4 final: public Level {
    public:
        Level4(ifstream &blockFile, const string &blockFileString);
        ~Level4();

        Block *makeBlock() override;
};

#endif
