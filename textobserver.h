#ifndef TEXTOBSERVER_H
#define TEXTOBSERVER_H
#include "observer.h"
#include "GameDisplay.h"
#include "subject.h"
#include <iostream>
#include "window.h"
class TextObserver : public Observer {
    GameDisplay* subject1;
    GameDisplay* subject2;

    int numReserveRows, nextBlockDock, width, height;  // boundary fields
    std::ostream &out = std::cout;

    const int SEPARATE = 10;

    void printSeparation();
    std::string scoreFormating(int score);
    void printTopBoundary();

public:
    TextObserver(GameDisplay* subject1, GameDisplay* subject2);

  virtual void notify(int blind_status = 0, string message  = " ", 
    int activePlayer = 0,set<pair<int, int>> blockPixcels = {}, vector<pair<int, int>> nextBlockPixcels = {}) override;     // void printSeparation();
    // requested with render command
    // ~TextObserver() override;
};

#endif
