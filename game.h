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
#include "graphicsobserver.h"
using namespace std;

class Game {
    Player p1;
    Player p2;
    TextObserver to;
    GraphicsObserver go;


    public:
    Game(bool text, int seed, string scriptfile1, string scriptfile2, int startlevel);
    
    // Remember to onstruct players with next block in player constructor

    void runGame();
    void restart();

};





#endif