#ifndef __LEVEL__
#define __LEVEL__

#include <fstream>
#include "block.h"

using namespace std;

class Level {
    protected:
        bool heavy;
        ifstream &blockFile;

    public:
        Level(bool heavy, ifstream &blockFile);
        virtual ~Level()=0;

        virtual Block *makeBlock(bool forceHeavy)=0;
        Block *makeChosenBlock(char c, bool forceHeavy);
};

class Level0 final: public Level {
    public:
        Level0(ifstream &blockFile);
        ~Level0();

        Block *makeBlock(bool forceHeavy) override;
};

class Level1 final: public Level {
    public:
        Level1(ifstream &blockFile);
        ~Level1();

        Block *makeBlock(bool forceHeavy) override;
};

class Level2 final: public Level {
    public:
        Level2(ifstream &blockFile);
        ~Level2();

        Block *makeBlock(bool forceHeavy) override;
};

class Level3 final: public Level {
    public:
        Level3(ifstream &blockFile);
        ~Level3();

        Block *makeBlock(bool forceHeavy) override;
};

class Level4 final: public Level {
    public:
        Level4(ifstream &blockFile);
        ~Level4();

        Block *makeBlock(bool forceHeavy) override;
};

#endif
