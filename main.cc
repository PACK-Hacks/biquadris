#include "iostream"
#include "vector"
#include "player.h"


using namespace std;

void runRound(vector<Player*> players) {
    for ( auto p : players ) {
        p->runTurn();

    }
}

int main(int argc, char *argv[]) {

    int startLevel = 0; //////
    vector<Player*> players;
     
    players.emplace_back(new Player{}); //
    players.emplace_back(new Player{}); //

    string command;
    
    startGame()
    bool lost = false;
    while(!lost) {
        runRound(players);
        // for ( auto player : players ) {
        //     if (player->lost) cout << player->name << " loses" << endl;
        //     lost = true;
        //     break;
        // }
    }
}

