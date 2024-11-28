#include "GameDisplay.h"
#include <fstream>
#include "textobserver.h"
#include "graphicsobserver.h"
#include <memory>
#include "game.h"
#include "player.h"
#include <sstream>

using namespace std;

// int main(int argc, char *argv[]) {
//     bool text = false;
//     int seed = 0;
//     string scriptfile1 = "blank.txt";
//     string scriptfile2 = "blank.txt";
//     int startlevel = 0;

//     for (int i = 0; i < argc; i++) {
//         if (argv[i] == "-text") {
//             text = true;
//         } else if (argv[i] == "-scriptfile1") {
//             if (i + 1 < argc) {
//                 scriptfile1 = argv[i + 1];
//                 i++;
//             } 
//         } else if (argv[i] == "-scriptfile2") {
//             if (i + 1 < argc) {
//                 scriptfile2 = argv[i + 1];
//                 i++;
//             } 
//         } else if (argv[i] == "-seed") {
//             if (i + 1 < argc) {
//                 string s = argv[i + 1];
//                 istringstream iss {s};
//                 iss >> seed;
//                 i++;
//             } 
//         } else if (argv[i] == "-startlevel") {
//             if (i + 1 < argc) {
//                 string s = argv[i + 1];
//                 istringstream iss {s};
//                 iss >> startlevel;
//                 i++;
//             } 
//         }
//     }

//     Game g{true, 0, "blank.txt", "blank2.txt", 0}; // Game(bool text, int seed, string scriptfile1, string scriptfile2, int startlevel);
//     g.runGame();

// }



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

    Game g{text, seed, scriptfile1, scriptfile2, startlevel}; // Game(bool text, int seed, string scriptfile1, string scriptfile2, int startlevel);
    g.runGame();
}


//  ifstream blockFile{"blank.txt"};

//     GameDisplay d1{4, "blank.txt"};
//     GameDisplay d2{4, "blank.txt"};

//     d1.generateNextBlock();
//     d1.moveNextToCurrent();
//     d1.insertCurrentBlock();
//     d1.generateNextBlock();
//     d1.setNextBlock();
//     d1.levelDown();


//     d2.generateNextBlock();
//     d2.moveNextToCurrent();
//     d2.insertCurrentBlock();
//     d2.generateNextBlock();




//     d2.setNextBlock();
//     // d.print();

//     // d.right();
//     // d.print();

//     // d.down();
//     // d.print();

//     // d.left();
//     // d.print();

//     // d.drop();
//     // d.print();

//     // vector obserers for the observer instances
//     std::vector<Observer*> observers;

//     // auto d1 = std::make_unique<Display>(d);

//     GraphicsObserver t{&d1, &d2};

//     t.notify();

//     d1.right();
//     d1.clockwise();

//     d2.levelDown();
//     d2.levelDown();
//     d2.levelDown();

//     t.notify();

//     // for (auto p : observers) {
//     //     delete p;
//     // }
    









