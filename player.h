#ifndef __PLAYER__
#define __PLAYER__

#include <memory>
#include "display.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "textobserver.h"

using namespace std;

class Player {
    int highScore;
    bool lost;
    string text;
    int seed;
    string scriptfile;
    int startLevel;
    Display display;
    istream *in = &cin;
    ifstream sequenceStream;

    string left = "left"; // Extension, allow users to change command values
    string right = "right";
    string down = "down";
    string drop = "drop";
    string clockwise = "clockwise";
    string counterclockwise = "counterclockwise";
    string levelup = "levelup";
    string leveldown = "leveldown"; 
    string norandom = "norandom";
    string random = "random";
    string sequence = "sequence";
    string restart = "restart";
    vector<char> blocks;

    char string_to_char(string s);

    bool find_block(char b);

    public:
    Player(bool text, int seed, string scriptfile, int startLevel);

    string runTurn(string special, TextObserver &to);

    bool getLost();

    Display *getDisplay();

};

#endif