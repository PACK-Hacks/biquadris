#ifndef GRAPHICSOBSERVER_H
#define GRAPHICSOBSERVER_H
#include "observer.h"
#include "GameDisplay.h"
#include "subject.h"
#include <iostream>

class GraphicsObserver : public Observer {
    GameDisplay* subject1;
    GameDisplay* subject2;

    int numReserveRows, nextBlockDock, width, height;  // boundary fields
    std::ostream &out = std::cout;

    int determineColor(char c, bool isBlind, int y);
    Xwindow window;

    const int scale = 10;
    const int SEPARATE = 10;
    const int colStart1 = 10;
    const int rowStart =  110;
    const int colStart2 = 320;

    const int blockScale = 19;

    bool active;

    bool playerWasBlind[2]{false};

    void printSeparation();
    void printTopBoundary();
    void reRenderPos();

    int highScore = 0;
public:
    GraphicsObserver(GameDisplay* subject1, GameDisplay* subject2);
    void notify(int blind_status = 0, string message  = " ", int activePlayer = 0) override;

    // requested with render command
    // ~TextObserver() override;
};

#endif
