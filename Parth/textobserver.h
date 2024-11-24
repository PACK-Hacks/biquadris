#ifndef TEXTOBSERVER_H
#define TEXTOBSERVER_H
#include "observer.h"
#include "display.h"
#include <iostream>

class TextObserver : public Observer {
    Display* subject;
    int numReserveRows, nextBlockDock, width, height;  // boundary fields
    std::ostream &out = std::cout;

    const int SEPARATE = 6;

    void printSeparation();
    void printTopBoundary();

public:
    TextObserver(Display* subject);
    void notify() override;
    // requested with render command
    // ~TextObserver() override;
};

#endif
