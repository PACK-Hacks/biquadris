#include "player.h"
using namespace std;

Player(bool text, int seed, string scriptfile, int startLevel, unique_ptr<Game> game):
    highScore{0}, lost{false}, text{text}, seed{seed}, scriptfile1{scriptfile1}, 
    startLevel{startLevel}, display{startLevel, scriptfile}, game{game} {
    display.generateNextBlock("");
}

string Player::runTurn(string special) {
    bool status = display.moveNextToCurrent(); // Assume moves it onto the board

    if (status == false) { // When block was attempted to be placed on board, there was something covering
                           // one of the default spots, and so the player automatically loses
        lost = true;
        display.render(lost); // ?
        return "";
    }

    display.generateNextBlock(special);

    bool endTurn = false;

    cout << "Please input a series of commands to move / rotate your block" << endl;

    string command;

    while(cin >> command && !endTurn) {     // fstream >> command
        if (command == left) {
            endTurn = display.left();
            display.render();
        } else if (command == right) {
            endTurn = display.right();
            display.render();
        } else if (command == down) {
            endTurn = display.down();
            display.render();
        } else if (command == clockwise) {
            endTurn = display.clockwise();
            display.render();
        } else if (command == counterclockwise) {
            endTurn = display.counterclockwise();
            display.render();
        } else if (command == drop) {
            endTurn = display.drop();
            display.render();
            break;
        } else if (command == levelup) {
            bool canLevelUp;
            canLevelUp = levelup();
            if (canLevelUp == false) {
                cout << "You cannot level up! You are already at level 4!" << endl;
            }
        } else if (command == leveldown) {
            bool canLevelDown;
            canLevelDown = levelDown();
            if (canLevelUp == false) {
                cout << "You cannot level down! You are already at level 0!" << endl;
                ifstream 
            }
        } else if (command == norandom) {
            string file_name;
            cin >> file_name;
            ifstream f{file_name};
            display.norandom(f);
        } else if (command == random) {
            display.random();
        } else if (command == restart) {
            game->restart();
        }
    }

    // Player's turn is over

    if (display.getScore() > highScore) highScore = display.getScore();


    
    
    if (special == "") {

        


    } else {
        istringstream iss{special};
        string s;

        block = level->getBlock();
        heavy = level->getHeavy();
        dummy = level->getDummy();

        while (iss >> s) {
            if (s == "blind") {     // set nextBlind to false in drop method
                isBlind = true;
            }
            if (s == "force") {
                iss >> isBlock;
            } 
            if (s == "heavy") {
                heavy = true;
            }
        }

        // display.board() = new Board{block, isHeavy, isBlind, dummy, ...};
    }

    

    // string command;
    // // create variables for each command, which can be modified by the user 
    // Level *lvl = 

    
    
    // Decorator currentBlock{nextHeavy}
}
