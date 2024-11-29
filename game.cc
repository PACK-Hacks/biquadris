#include <memory>
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include "GameDisplay.h"
#include "game.h"
#include "player.h"
#include "textobserver.h"

using namespace std;


Game::Game(bool text, int seed, string scriptfile1, string scriptfile2, int startlevel = 0): 
p1{1, text, seed, scriptfile1, startlevel}, p2{2, text, seed, scriptfile2, startlevel}, 
to{p1.getGameDisplay(), p2.getGameDisplay()}, go{p1.getGameDisplay(), p2.getGameDisplay()} {
    go.notify();
}
// Remember to construct players with next block in player constructor

string formatWinner(string winner, int score1, int score2) {
    return winner + " has won by " + to_string(abs(score1 - score2)) + "!\nPlayer 1's Score: " + to_string(score1) + "    Player 2's Score: " + to_string(score2);
}

void Game::runGame() {
    string special;

    // Keep running rounds until both players lose
    while (!p1.getLost() || !p2.getLost()) {
        if (p1.getLost()) {
            cout << "Player 1 has already lost :( Skipping this turn" << endl << endl;
            special = "";   // Reset special to prevent players from passing a special to themselves
        }
        // If Player 1's still alive, run their turn
        else {
            special = p1.runTurn(special, to, go);
            // Restart if Player 1 commands so
            if (special == "restart") {
                restart();
                continue;
            }
        }
        cout << "__________________________________________________________" << endl << endl;
        if (p2.getLost()) {
            cout << "Player 2 has already lost :( Skipping this turn" << endl << endl;
            special = "";   // Reset special to prevent players from passing a special to themselves
        }
        // If Player 2's still alive, run their turn
        else {
            special = p2.runTurn(special, to, go);
            // Restart if Player 1 commands so
            if (special == "restart") {
                restart();
                continue;
            }
        }
        cout << "__________________________________________________________" << endl << endl;
    }

    // Output winner
    string gameOverMessage;

    int score1 = p1.getGameDisplay()->getScore();
    int score2 = p2.getGameDisplay()->getScore();

    if (score1 > score2) {
        gameOverMessage = formatWinner("Player 1", score1, score2);
    }
    else if (score1 < score2) {
        gameOverMessage = formatWinner("Player 2", score1, score2);
    }
    else {
        gameOverMessage = "It's a TIE!\nPlayer 1's Score: " + to_string(score1) + "    Player 2's Score: " + to_string(score2);
    }

    cout << gameOverMessage << endl << endl;
}

void Game::restart() {
    p1.reset();
    p1.getGameDisplay()->moveNextToCurrent();
    p1.getGameDisplay()->generateNextBlock();
    go.notify();
    p2.reset();
}

