#ifndef __CELL__
#define __CELL__

class Cell {   
    char letter;            // char rendered on observers
    char realLetter = '/';  // char used to represent the cell ('/' for currentBlock)
    int x;
    int y;
    int age;

    public:
        Cell(char letter, int x, int y);
        char getChar();
        char getRealChar();
        void addToX(int n);
        void addToY(int n);
        int getX();
        int getY();
        void incrementAge();
};

#endif
