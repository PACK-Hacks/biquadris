#ifndef __PLAYER__
#define __PLAYER__

#include <memory>
#include "GameDisplay.h"
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
    int id;
    string scriptfile;
    int startLevel;
    GameDisplay gameDisplay;
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

    string runTurn(string special, TextObserver &to);

    bool getLost();

    GameDisplay *getGameDisplay();

};

#endif