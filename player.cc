#include <memory>
#include "display.h"
#include <string>
#include "game.h"
#include <sstream>
#include <iostream>
#include "player.h"
using namespace std;



Player::Player(bool text, int seed, string scriptfile, int startLevel, Game *game):
    highScore{0}, lost{false}, text{text}, seed{seed}, scriptfile{scriptfile}, 
    startLevel{startLevel}, display{startLevel, ifstream{scriptfile}}, game{game} {
        display.generateNextBlock();
        blocks.emplace_back('I');
        blocks.emplace_back('J');
        blocks.emplace_back('L');
        blocks.emplace_back('O');
        blocks.emplace_back('S');
        blocks.emplace_back('Z');
        blocks.emplace_back('T');
}

char Player::string_to_char(string s) {
    istringstream iss{s};
    char c;
    iss >> c;
    return c;
}

bool Player::find_block(char b) { // Could be more efficient?
    for (int i = 0; i < blocks.size(); i++) {
        if (blocks[i] == b) {
            return true;
        }
    }
    return false;
}

string Player::runTurn(string special) {

    bool status = display.moveNextToCurrent(); // Assume moves it onto the board

    if (status == false) { // When block was attempted to be placed on board, there was something covering
                            // one of the default spots, and so the player automatically loses
        lost = true;
        display.render(lost); // ?
        return "";
    }

    display.generateNextBlock();

    if (special != "") { // Check for specials
        istringstream iss{special};
        string curr_special;
        while (iss >> curr_special) {
            if (curr_special == "heavy") {
                display.setHeavy(); // sets heavy to true
            } else if (curr_special == "blind") {
                display.setBlind();
            } else if (curr_special == "force") {
                char c;
                iss >> curr_special;
                display.setCurrentBlock(c);
            }
        }
    }
    
    
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
            canLevelUp = display.levelup();
            if (canLevelUp == false) {
                cout << "You cannot level up! You are already at the max level!" << endl;
            }
        } else if (command == leveldown) {
            bool canLevelDown;
            canLevelDown = display.levelDown();
            if (canLevelDown == false) {
                cout << "You cannot level down! You are already at the lowest level!" << endl;
            }
        } else if (command == norandom) {
            string file_name;
            cin >> file_name;
            ifstream f{file_name}; // Will need to pass the file name to norandom in the case that the block file is read entirely and need to read it again from the top.
            display.norandom(f);
        } else if (command == random) {
            display.random();
        } else if (command.length() == 1 && find_block(string_to_char(command))) {
            char c = string_to_char(command);
            display.setCurrentBlock(c); 
        } else if (command == restart) {
            game->restart();
        } else {
            cout << "Please enter a valid command" << endl;
        }
    }

    for (int i = 0; i < display.getWidth(); i++) {
        if (display.getState(3,i) != ' ') {
            lost = true;
        }
    } // Check all columns in third row to see if there is a cell there, if so, player loses
    if (display.getScore() > highScore) highScore = display.getScore();

    display.resetSpecial();

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


    


}

bool Player::getLost() {
    return lost;
}


