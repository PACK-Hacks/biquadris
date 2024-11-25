#ifndef __LEVEL__
#define __LEVEL__

#include <fstream>
#include <cstdlib>
#include "block.h"
// #include "display.h"

using namespace std;

class Level {
    protected:
        Display *display;
        bool heavy;
        ifstream &blockFile;

    public:
        Level(Display *display, bool heavy, ifstream &blockFile);
        virtual ~Level()=0;

        virtual Block *makeBlock();
        Block *makeChosenBlock(char c);
};

class Level0 final: public Level {
    public:
        Level0(Display *display, ifstream &blockFile);

        Block *makeBlock();
};

class Level1 final: public Level {
    public:
        Level1(Display *display, ifstream &blockFile);

        Block *makeBlock();
};

class Level2 final: public Level {
    public:
        Level2(Display *display, ifstream &blockFile);

        Block *makeBlock();
};

class Level3 final: public Level {
    public:
        Level3(Display *display, ifstream &blockFile);

        Block *makeBlock();
};

class Level4 final: public Level {
    public:
        Level4(Display *display, ifstream &blockFile);

        Block *makeBlock();
};

#endif
