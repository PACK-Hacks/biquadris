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

    // for (int i = 1; i < argc; i++) {
    //     string arg = argv[i];
    //     if (arg == "-text") {
    //         text = true;
    //     } else if (arg == "-scriptfile1") {
    //         if (i + 1 < argc) {
    //             scriptfile1 = argv[i + 1];
    //             i++;
    //         } 
    //     } else if (arg == "-scriptfile2") {
    //         if (i + 1 < argc) {
    //             scriptfile2 = argv[i + 1];
    //             i++;
    //         } 
    //     } else if (arg == "-seed") {
    //         if (i + 1 < argc) {
    //             string s = argv[i + 1];
    //             istringstream iss {s};
    //             iss >> seed;
    //             i++;
    //         } 
    //     } else if (arg == "-startlevel") {
    //         if (i + 1 < argc) {
    //             string s = argv[i + 1];
    //             istringstream iss {s};
    //             iss >> startlevel;
    //             i++;
    //         } 
    //     }
    // }

    // cout << text << endl;
    // cout << seed << endl;
    // cout << scriptfile1 << endl;
    // cout << scriptfile2 << endl;
    // cout << startlevel << endl;


    // Game g{text, seed, scriptfile1, scriptfile2, startlevel}; // Game(bool text, int seed, string scriptfile1, string scriptfile2, int startlevel);
    // string winner = g.runGame();
    // cout << "Congratulations! " << winner << " has won!" << endl;





 ifstream blockFile{"blank.txt"};

    GameDisplay d1{4, "blank.txt"};
    GameDisplay d2{4, "blank.txt"};

    d1.generateNextBlock();
    d1.moveNextToCurrent();
    d1.insertCurrentBlock();
    d1.generateNextBlock();
    d1.setNextBlock();
    d1.levelDown();


    d2.generateNextBlock();
    d2.moveNextToCurrent();
    d2.insertCurrentBlock();
    d2.generateNextBlock();

    d2.setNextBlock();

    // vector obserers for the observer instances
    std::vector<Observer*> observers;

    // auto d1 = std::make_unique<Display>(d);

    auto p1 = std::make_pair(3, 0);
    auto p2 = std::make_pair(3, 1);
    auto p3 = std::make_pair(2, 1);
    auto p4 = std::make_pair(2, 2);
    
    std::vector<std::pair<int, int>> block1;
    std::vector<std::pair<int, int>> block2;

    block1.emplace_back(p1);
    block1.emplace_back(p2);
    block1.emplace_back(p3);
    block1.emplace_back(p4);

    block2.emplace_back(p1);
    block2.emplace_back(p2);
    block2.emplace_back(p3);
    block2.emplace_back(p4);



    GraphicsObserver t{&d1, &d2};

    t.notify(0, " ", 0, block1, block2);

    d1.right();
    d1.clockwise();

    auto p5 = std::make_pair(3, 1);
    auto p6 = std::make_pair(4, 1);
    auto p7 = std::make_pair(4, 2);
    auto p8 = std::make_pair(5, 2);

    block1.emplace_back(p5);
    block1.emplace_back(p6);
    block1.emplace_back(p7);
    block1.emplace_back(p8);


    t.notify(0, " ", 0, block1, block2);

    // for (auto p : observers) {
    //     delete p;
    // }

    // Game g{text, seed, scriptfile1, scriptfile2, startlevel}; // Game(bool text, int seed, string scriptfile1, string scriptfile2, int startlevel);
    // g.runGame();
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
    









