#include "display.h"
#include <fstream>
#include "textobserver.h"
#include <memory>
#include "game.h"
#include "player.h"
#include <sstream>

using namespace std;

int main(int argc, char *argv[]) {
    bool text = false;
    int seed = 0;
    string scriptfile1 = "blank.txt";
    string scriptfile2 = "blank.txt";
    int startlevel = 0;

    for (int i = 0; i < argc; i++) {
        if (argv[i] == "-text") {
            text = true;
        } else if (argv[i] == "-scriptfile1") {
            if (i + 1 < argc) {
                scriptfile1 = argv[i + 1];
                i++;
            } 
        } else if (argv[i] == "-scriptfile2") {
            if (i + 1 < argc) {
                scriptfile2 = argv[i + 1];
                i++;
            } 
        } else if (argv[i] == "-seed") {
            if (i + 1 < argc) {
                string s = argv[i + 1];
                istringstream iss {s};
                iss >> seed;
                i++;
            } 
        } else if (argv[i] == "-startlevel") {
            if (i + 1 < argc) {
                string s = argv[i + 1];
                istringstream iss {s};
                iss >> startlevel;
                i++;
            } 
        }
    }

    Game g{true, 0, "blank.txt", "blank2.txt", 0}; // Game(bool text, int seed, string scriptfile1, string scriptfile2, int startlevel);
    g.runGame();

}

