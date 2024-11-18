#include "iostream"
#include "vector"
#include "player.h"


using namespace std;



int main(int argc, char *argv[]) {

    int startLevel = 0; //////
    Player *p1 = new Player{};
    Player *p2 = new Player{};

    string special = "";

    void runRound(Player *p1, Player *p2) {
        special = p1->runTurn(special, ...);
        if (p1->lost) return;
        special = p2->runTurn(special, ...);
    }
    
    startGame()
    bool lost = false;
    while(!lost) {
        runRound(p1, p2);
        // for ( auto player : players ) {
        //     if (player->lost) cout << player->name << " loses" << endl;
        //     lost = true;
        //     break;
        // }
    }
}

