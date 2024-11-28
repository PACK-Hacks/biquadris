#include <memory>
#include "GameDisplay.h"
#include <string>
#include "game.h"
#include <sstream>
#include <iostream>
#include "player.h"
#include "textobserver.h"

using namespace std;


Game::Game(bool text, int seed, string scriptfile1, string scriptfile2, int startlevel = 0): 
p1{text, seed, scriptfile1, startlevel}, p2{text, seed, scriptfile2, startlevel}, 
to{p1.getGameDisplay(), p2.getGameDisplay()} {}
// Remember to construct players with next block in player constructor

string Game::runGame() {
    string special;

    
    while (true) {
        special = p1.runTurn(special, to);
        if (special == "restart") restart();
        if (p1.getLost() == true) return "p2";
        special = p2.runTurn(special, to);
        if (special == "restart") restart();
        if (p2.getLost() == true) return "p1";
    }

    return "p1";

}

void Game::restart() {
    // p1.reset(); // Implement in display
    // p2.reset(); 
}

