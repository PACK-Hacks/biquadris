#include "GameDisplay.h"
#include <fstream>
#include "textobserver.h"
#include <memory>
#include "game.h"
#include "player.h"
#include <sstream>

using namespace std;

int main(int argc, char *argv[]) {
    // Default construct flags
    bool text = false;
    int seed = 0;
    string scriptfile1 = "sequence1.txt";
    string scriptfile2 = "sequence2.txt";
    int startlevel = 0;

    // Read flags
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "-text") {
            text = true;
        } else if (arg == "-scriptfile1") {
            if (i + 1 < argc) {
                scriptfile1 = argv[i + 1];
                i++;
            } 
        } else if (arg == "-scriptfile2") {
            if (i + 1 < argc) {
                scriptfile2 = argv[i + 1];
                i++;
            } 
        } else if (arg == "-seed") {
            if (i + 1 < argc) {
                string s = argv[i + 1];
                istringstream iss {s};
                iss >> seed;
                i++;
            } 
        } else if (arg == "-startlevel") {
            if (i + 1 < argc) {
                string s = argv[i + 1];
                istringstream iss {s};
                iss >> startlevel;
                i++;
            } 
        }
    }

    // Create game with flags
    Game g{text, seed, scriptfile1, scriptfile2, startlevel}; 
    // Run game
    g.runGame();
}
