#include <memory>
#include "display.h"
#include <string>
#include <sstream>
#include <iostream>
#include "player.h"
#include "textobserver.h"
using namespace std;



Player::Player(bool text, int seed, string scriptfile, int startLevel):
    highScore{0}, lost{false}, text{text}, seed{seed}, scriptfile{scriptfile}, 
    startLevel{startLevel}, display{startLevel, scriptfile} {
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
    for (size_t i = 0; i < blocks.size(); i++) {
        if (blocks[i] == b) {
            return true;
        }
    }
    return false;
}

string Player::runTurn(string special, TextObserver &to) {

    bool status = display.moveNextToCurrent(); // Assume moves it onto the board

    // if (status == false) { // When block was attempted to be placed on board, there was something covering
    //                         // one of the default spots, and so the player automatically loses
    //     lost = true;
    //     // display.render(lost); // ?
    //     return "";
    // }

    display.generateNextBlock();

    to.notify();

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
                iss >> c;
                display.setCurrentBlock(c);
            }
        }
    }
    
    
    bool endTurn = false;

    cout << "Please input a series of commands to move / rotate your block" << endl;

    string command;


    while(!endTurn) {     // fstream >> command

        if (!(*in >> command)) {
            if (in == &sequenceStream) {
                // Sequence file exhausted; switch back to cin
                sequenceStream.clear();      // Clear EOF flag
                sequenceStream.ignore();
                in = &cin;
                cout << "Sequence file exhausted. Switching back to standard input." << endl;
                continue; // Continue the loop to read from cin
            } else {
                // If reading from cin fails, perhaps due to EOF, terminate the turn
                break;
            }
        }

        if (command == left) {
            endTurn = display.left();
            to.notify();
        } else if (command == right) {
            endTurn = display.right();
            to.notify();
        } else if (command == down) {
            endTurn = display.down();
            to.notify();
        } else if (command == clockwise) {
            endTurn = display.clockwise();
            to.notify();
        } else if (command == counterclockwise) {
            endTurn = display.counterClockwise();
            to.notify();
        } else if (command == drop) {
            endTurn = display.drop();
            to.notify();
            break;
        } else if (command == levelup) {
            bool canLevelUp;
            canLevelUp = display.levelUp();
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
            *in >> file_name;
             // Will need to pass the file name to norandom in the case that the block file is read entirely and need to read it again from the top.
            display.norandom(file_name);
        } else if (command == random) {
            // display.random();
        } else if (command.length() == 1 && find_block(string_to_char(command))) {
            char c = string_to_char(command);
            display.setCurrentBlock(c); 
        } else if (command == restart) {
            return "restart";
        } else if (command == sequence) {
            *in >> command;
            sequenceStream = ifstream{command};
            in = &sequenceStream;
        } else {
            cout << "Please enter a valid command" << endl;
        }

    }
    if (display.needDummy()) display.dropDummyCell();

    // Check and set the lost field in Display to that of Player
    lost = display.getLost();

    if (display.getScore() > highScore) highScore = display.getScore();

    // display.resetSpecial();

    if (display.getSpecial() == true) { // change condiiton to display.getSpecial() == true
        display.setSpecial(false);
        
        cout << "You have earned a special!" << endl;
        cout << "What special would you like to place on your opponent? (blind, force, heavy)" << endl;
        string s;
        *in >> s;
        while (s != "heavy" && s != "force" && s != "blind") {
            cout << "There is no such special!" << endl;
            cout << "What special would you like to place on your opponent? (blind, force, heavy)" << endl;
            *in >> s;
        }
        if (s == "force") {
            cout << "Which block would you like to force on your opponent? (I, J, L, O, S, Z, T)?" << endl;
            char b;
            *in >> b;
            while (!find_block(b)) {
                cout << "Incorrect input! Enter a valid block (I, J, L, O, S, Z, T)." << endl;
                *in >> b;
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

Display *Player::getDisplay() {
    return &display;
}


