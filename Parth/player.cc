#include <memory>
#include "display.h"
#include <string>
#include "game.h"
#include <sstream>
#include <iostream>
using namespace std;

class Player {
    int highScore;
    bool lost;
    string text;
    int seed;
    string scriptfile1;
    int startLevel;
    Display display;
    unique_ptr<Game> game;

    string left = "left"; // Extension, allow users to change command values
    string right = "right";
    string down = "down";
    string drop = "drop";
    string clockwise = "clockwise";
    string counterclockwise = "counterclockwise";
    string levelup = "levelup";
    string leveldown = "leveldown";
    string norandom = "norandom";
    string random = "random";
    string sequence = "sequence";
    string restart = "restart";
    vector<char> blocks;


    Player(bool text, int seed, string scriptfile, int startLevel, unique_ptr<Game> game):
        highScore{0}, lost{false}, text{text}, seed{seed}, scriptfile1{scriptfile1}, 
        startLevel{startLevel}, display{startLevel, scriptfile}, game{game} {
            display.generateNextBlock("");
            blocks.emplace_back('I');
            blocks.emplace_back('J');
            blocks.emplace_back('L');
            blocks.emplace_back('O');
            blocks.emplace_back('S');
            blocks.emplace_back('Z');
            blocks.emplace_back('T');
        }

    bool find_block(char b) { // Could be more efficient?
        for (int i = 0; i < blocks.size(); i++) {
            if (blocks[i] == b) {
                return true;
            }
        }
        return false;
    }

    string runTurn(string special) {




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
                }
            } else if (command == norandom) {
                string file_name;
                cin >> file_name;
                ifstream f{file_name};
                display.norandom(f);
            } else if (command == random) {
                display.random();
            } else if (command == i) {
                display.setCurrentBlock(i); // Find a way to make this so we dont need different else if statements for each block type
            } else if (command == restart) {
                game->restart();
            } 
        }

        for (int i = 0; i < display.getWidth(); i++) {
            if (display.getState(3,i) != ' ') {
                lost = true;
            }
        } // Check all columns in third row to see if there is a cell there, if so, player loses
        if (display.getScore() > highScore) highScore = display.getScore();

        if (display.getSpecial() == true) {
            cout << "You have earned a special!" << endl;
            cout << "What special would you like to place on your opponent? (blind, force, heavy)" << endl;
            string s;
            cin >> s;
            while (s != "heavy" && s != "force" && s != "blind") {
                cout << "There is no such special!" << endl;
                cout << "What special would you like to place on your opponent? (blind, force, heavy)" << endl;
                cin >> s;
            }
            if (s == "force") {
                cout << "Which block would you like to force on your opponent? (I, J, L, O, S, Z, T)?" << endl;
                char b;
                cin >> b;
                while (!find_block(b)) {
                    cout << "Incorrect input! Enter a valid block (I, J, L, O, S, Z, T)." << endl;
                    cin >> b;
                }
                string b_string{b};
                cout << "Your turn is now over" << endl;
                return s + " " + b_string;
            }
            cout << "Your turn is now over" << endl;
            return s;
        } else {
            cout << "You have not achieved a special move" << endl;
            cout << "Your turn is now over" << endl;
            return "";
        }





    //     if (special == "") {

            


    //     } else {
    //         istringstream iss{special};
    //         string s;

    //         block = level->getBlock();
    //         heavy = level->getHeavy();
    //         dummy = level->getDummy();

    //         while (iss >> s) {
    //             if (s == "blind") {     // set nextBlind to false in drop method
    //                 isBlind = true;
    //             }
    //             if (s == "force") {
    //                 iss >> isBlock;
    //             } 
    //             if (s == "heavy") {
    //                 heavy = true;
    //             }
    //         }

    //         // display.board() = new Board{block, isHeavy, isBlind, dummy, ...};
    //     }



    //     string command;
    //     // create variables for each command, which can be modified by the user 
    //     Level *lvl = 


    //     Decorator currentBlock{nextHeavy}


    }

bool getLost() {
    return lost;
}

};

