#ifndef __PLAYER__
#define __PLAYER__

#include <memory>
#include "display.h"
#include <string>
#include "game.h"
#include <sstream>
#include <iostream>
using namespace std;

class Player {
    int highScore;
    bool lost;
    string text;
    int seed;
    string scriptfile;
    int startLevel;
    Display display;
    Game *game;

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
    Player(bool text, int seed, string scriptfile, int startLevel, Game *game);

    string runTurn(string special);

    bool getLost();

};

#endif