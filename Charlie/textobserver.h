#ifndef TEXTOBSERVER_H
#define TEXTOBSERVER_H
#include "observer.h"
#include "display.h"
#include <iostream>

class TextObserver : public Observer {
    Display* subject;
    int top, bottom, left, right;  // boundary fields
    std::ostream &out = std::cout;

public:
    TextObserver(Display* subject, int top, int bottom, int left, int right);
    void notify() override;
    // requested with render command
    // ~TextObserver() override;
};

#endif
