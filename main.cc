#include "display.h"
#include <fstream>
#include "textobserver.h"
#include <memory>
#include "game.h"
#include "player.h"

using namespace std;

int main() {
    Game g{true, 0, "blank.txt", "blank2.txt", 0}; // Game(bool text, int seed, string scriptfile1, string scriptfile2, int startlevel);
    g.runGame();

}

