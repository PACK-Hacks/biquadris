#ifndef __PLAYER__
#define __PLAYER__

#include <memory>
#include "GameDisplay.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "textobserver.h"
#include "graphicsobserver.h"

using namespace std;

class Player {
    int blind_status = 0;
    int id;
    bool lost;
    string text;
    int seed;
    string scriptfile;
    int startLevel;
    GameDisplay gameDisplay;
    istream *in = &cin;
    ifstream sequenceStream;
    int numDrops = 0;

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
    vector<string> commands = {
    left, right, down, drop, clockwise, counterclockwise,
    levelup, leveldown, norandom, random, sequence, restart,
    "I", "J", "L", "S", "O", "Z", "T"
    };

    char string_to_char(string s);

    bool find_block(char b);

    string getUnique(string s);

    pair<int, string> parseCommand(const string &input);


    public:
    Player(int id, bool text, int seed, string scriptfile, int startLevel);

    string runTurn(string special, TextObserver &to, GraphicsObserver &go);

    bool getLost();

    GameDisplay *getGameDisplay();

    void reset();

};

#endif