// #include "iostream"
// #include "vector"
// #include "player.h"


// using namespace std;

// void runRound(vector<Player*> players) {
//     for ( auto p : players ) {
//         p->runTurn();

//     }
// }

// int main(int argc, char *argv[]) {

//     int startLevel = 0; //////
//     vector<Player*> players;
     
//     players.emplace_back(new Player{}); //
//     players.emplace_back(new Player{}); //

//     string command;
    
//     startGame()
//     bool lost = false;
//     while(!lost) {
//         runRound(players);
//         // for ( auto player : players ) {
//         //     if (player->lost) cout << player->name << " loses" << endl;
//         //     lost = true;
//         //     break;
//         // }
//     }
// }




#include "display.h"
#include <fstream>
#include "textobserver.h"
#include <memory>
using namespace std;

int main() {
    ifstream blockFile{"blank.txt"};

    Display d{4, blockFile};

    d.insertCurrentBlock();
    d.setNextBlock();
    // d.print();

    // d.right();
    // d.print();

    // d.down();
    // d.print();

    // d.left();
    // d.print();

    // d.drop();
    // d.print();

    // vector obserers for the observer instances
    std::vector<Observer*> observers;

    // auto d1 = std::make_unique<Display>(d);

    TextObserver t{&d};

    t.notify();

    d.drop();
    t.notify();
  }
