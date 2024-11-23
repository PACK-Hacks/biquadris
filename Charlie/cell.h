#ifndef __CELL__
#define __CELL__

class Cell {
    char letter;
    int x;
    int y;
    int age;

    public:
        Cell(char letter, int x, int y);
        char getChar();
        void addToX(int n);
        void addToY(int n);
        int getX();
        int getY();
        void incrementAge();
};

#endif
