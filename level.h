#ifndef __LEVEL__
#define __LEVEL__

#include <fstream>
#include "block.h"

using namespace std;

class Level {
    protected:
        bool heavy;
<<<<<<< HEAD
        bool norandom = false;
=======
        int level;
>>>>>>> 450a986f955c38820580f11bb8f02427aafb6455
        ifstream &blockFile;
        string blockFileString;
        ifstream &norandomFile;
        string norandomFileString;
        char getNextBlockChar();
        char getNextBlockCharNoRandom();
        

    public:
<<<<<<< HEAD
        Level(bool heavy, ifstream &blockFile, string blockFileString, ifstream &norandomFile, string norandomFileString);
=======
        Level(bool heavy, int level, ifstream &blockFile, string blockFileString);
>>>>>>> 450a986f955c38820580f11bb8f02427aafb6455
        virtual ~Level()=0;

        virtual Block *makeBlock() = 0;
        Block *makeChosenBlock(char block);
        void setNoRandom(string file_name, ifstream &f);
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
