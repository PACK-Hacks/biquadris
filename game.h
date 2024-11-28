#ifndef __GAME__
#define __GAME__
#include <memory>
#include "GameDisplay.h"
#include <string>
#include <sstream>
#include <iostream>
#include "player.h"
#include <fstream>
#include "textobserver.h"
using namespace std;

class Game {
    Player p1;
    Player p2;
    TextObserver to;

    public:
    Game(bool text, int seed, string scriptfile1, string scriptfile2, int startlevel);
    
    // Remember to onstruct players with next block in player constructor

    string runGame();
    void restart();

};





#endif