#ifndef __CELL__
#define __CELL__

class Cell {
    char letter;            // char rendered by observers
    char realLetter = '/';  // actual state of the char on the board, set as '/' for currentBlock
    int x;
    int y;
    int age;

    public:
        Cell(char letter, int x, int y);
        char getChar();
        char getRealChar();
        void place();
        void addToX(int n);
        void addToY(int n);
        int getX();
        int getY();
        void incrementAge();
};

#endif
