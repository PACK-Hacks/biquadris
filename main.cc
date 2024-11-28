#include "GameDisplay.h"
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

    cout << text << endl;
    cout << seed << endl;
    cout << scriptfile1 << endl;
    cout << scriptfile2 << endl;
    cout << startlevel << endl;


    Game g{text, seed, scriptfile1, scriptfile2, startlevel}; // Game(bool text, int seed, string scriptfile1, string scriptfile2, int startlevel);
    string winner = g.runGame();
    cout << "Congratulations! " << winner << " has won!" << endl;
}

