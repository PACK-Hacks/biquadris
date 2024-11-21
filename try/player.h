#include <memory>
#include <string>
#include "display.h"
#include "game.h"
using namespace std;

class Player {
    int highScore;
    bool lost;
    string text;
    int seed;
    string scriptfile1;
    int startLevel;
    Display display;
    unique_ptr<Game> game;

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
    string i = "I";
    string j = "J";
    string l = "L";
    string o = "O";
    string s = "S";
    string z = "Z";
    string t = "T";


    Player(bool text, int seed, string scriptfile, int startLevel, unique_ptr<Game> game);

    string runTurn(string special);

};