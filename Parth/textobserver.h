#ifndef TEXTOBSERVER_H
#define TEXTOBSERVER_H
#include "observer.h"
#include "display.h"
#include <iostream>

class TextObserver : public Observer {
    Display* subject1;
    Display* subject2;

    int numReserveRows, nextBlockDock, width, height;  // boundary fields
    std::ostream &out = std::cout;

    const int SEPARATE = 10;

    void printSeparation();
    void printTopBoundary();

public:
    TextObserver(Display* subject1, Display* subject2);
    void notify() override;
    // requested with render command
    // ~TextObserver() override;
};

#endif
