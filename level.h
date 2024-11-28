#ifndef __LEVEL__
#define __LEVEL__

#include <fstream>
#include "block.h"

using namespace std;

class Level {
    protected:
        bool heavy;
        bool norandom = false;
        int level;
        ifstream &blockFile;
        string blockFileString;
        ifstream &norandomFile;
        string norandomFileString;
        char getNextBlockChar();
        char getNextBlockCharNoRandom();
        

    public:
        Level(bool heavy, int level, ifstream &blockFile, string blockFileString, ifstream &norandomFile, string norandomFileString);
        virtual ~Level()=0;

        virtual Block *makeBlock() = 0;
        Block *makeChosenBlock(char block);
        void setNoRandom(string file_name, ifstream &f);
        void setRandom();
};

class Level0 final: public Level {
    public:
        Level0(ifstream &blockFile, const string &blockFileString, ifstream &norandomFile, string norandomFileString);
        ~Level0();

        Block *makeBlock() override;
};

class Level1 final: public Level {
    public:
        Level1(ifstream &blockFile, const string &blockFileString, ifstream &norandomFile, string norandomFileString);
        ~Level1();

        Block *makeBlock() override;
};

class Level2 final: public Level {
    public:
        Level2(ifstream &blockFile, const string &blockFileString, ifstream &norandomFile, string norandomFileString);
        ~Level2();

        Block *makeBlock() override;
};

class Level3 final: public Level {
    public:
        Level3(ifstream &blockFile, const string &blockFileString, ifstream &norandomFile, string norandomFileString);
        ~Level3();

        Block *makeBlock() override;
};

class Level4 final: public Level {
    public:
        Level4(ifstream &blockFile, const string &blockFileString, ifstream &norandomFile, string norandomFileString);
        ~Level4();

        Block *makeBlock() override;
};

#endif
