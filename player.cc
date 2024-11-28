#include <memory>
#include "GameDisplay.h"
#include <string>
#include <sstream>
#include <iostream>
#include "player.h"
#include "textobserver.h"
#include <utility>
#include <cctype>

using namespace std;



Player::Player(bool text, int seed, string scriptfile, int startLevel):
    highScore{0}, lost{false}, text{text}, seed{seed}, scriptfile{scriptfile}, 
    startLevel{startLevel}, gameDisplay{startLevel, scriptfile} {
        gameDisplay.generateNextBlock();
        srand(seed);
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

string Player::getUnique(string s) {


    vector<string> matches;

    for (const auto &command : commands) {
        if (command.find(s) == 0) { // Checks if 's' is a prefix of 'cmd', not case sensitive
            matches.push_back(command);
        }

    }

    if (matches.size() == 1){
        return matches[0];
    }

    return "monkeys";

}

pair<int, string> Player::parseCommand(const string &input) {
    int num_len = 0;
    int multiplier;
    int start = 0;
    int len = input.length();
    int pos = 0;

    if (isdigit(input[start])) {
        istringstream iss{input};
        iss >> multiplier;
    }

    while (pos < input.size() && isdigit(input[pos])) {
        pos++;
    }

    if (pos == 0) multiplier = 1;

    string command = getUnique(input.substr(pos));


    return make_pair(multiplier, command);




}

string Player::runTurn(string special, TextObserver &to) {

    bool status = gameDisplay.moveNextToCurrent(); // Assume moves it onto the board

    // if (status == false) { // When block was attempted to be placed on board, there was something covering
    //                         // one of the default spots, and so the player automatically loses
    //     lost = true;
    //     // gameDisplay.render(lost); // ?
    //     return "";
    // }

    gameDisplay.generateNextBlock();

    to.notify();

    if (special != "") { // Check for specials
        istringstream iss{special};
        string curr_special;
        while (iss >> curr_special) {
            if (curr_special == "heavy") {
                gameDisplay.setHeavy(); // sets heavy to true
            } else if (curr_special == "blind") {
                gameDisplay.setBlind();
            } else if (curr_special == "force") {
                char c;
                iss >> c;
                gameDisplay.setCurrentBlock(c);
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
        
        pair<int, string> p = parseCommand(command);

        command = p.second;
        int multiplier = p.first;

        if (command == left) {
            endTurn = gameDisplay.left(multiplier);
            to.notify();
        } else if (command == right) {
            endTurn = gameDisplay.right(multiplier);
            to.notify();
        } else if (command == down) {
            endTurn = gameDisplay.down(multiplier);
            to.notify();
        } else if (command == clockwise) {
            endTurn = gameDisplay.clockwise(multiplier);
            to.notify();
        } else if (command == counterclockwise) {
            endTurn = gameDisplay.counterClockwise(multiplier);
            to.notify();
        } else if (command == drop) {
            endTurn = gameDisplay.drop();
            to.notify();
            break;
        } else if (command == levelup) {
            bool canLevelUp;
            canLevelUp = gameDisplay.levelUp(multiplier);
            if (canLevelUp == false) {
                cout << "You cannot level up! You are already at the max level!" << endl;
            } else {
                cout << "Levelled Up!" << endl;
            }
            to.notify();
        } else if (command == leveldown) {
            bool canLevelDown;
            canLevelDown = gameDisplay.levelDown(multiplier);
            if (canLevelDown == false) {
                cout << "You cannot level down! You are already at the lowest level!" << endl;
            } else {
                cout << "Levelled Down!" << endl;
            }
            to.notify();
        } else if (command == norandom) {
            string file_name;
            if ((*in).fail()) {
                (*in).clear();
                (*in).ignore();
                in = &cin;
            }
            *in >> file_name;
             // Will need to pass the file name to norandom in the case that the block file is read entirely and need to read it again from the top.
            gameDisplay.norandom(file_name);
        } else if (command == random) {
            gameDisplay.random();
        } else if (command.length() == 1 && find_block(string_to_char(command))) {
            char c = string_to_char(command);
            gameDisplay.setCurrentBlock(c);
            to.notify();
        } else if (command == restart) {
            return "restart";
        } else if (command == sequence) {
            if ((*in).fail()) {
                (*in).clear();
                (*in).ignore();
                in = &cin;
            }
            *in >> command;
            sequenceStream = ifstream{command};
            in = &sequenceStream;
        } else {
            cout << "Please enter a valid command" << endl;
        }
    }
    if (gameDisplay.needDummy()) gameDisplay.dropDummyCell();

    // Check and set the lost field in Display to that of Player
    lost = gameDisplay.getLost();

    if (gameDisplay.getScore() > highScore) highScore = gameDisplay.getScore();

    // gameDisplay.resetSpecial();

    if (gameDisplay.getSpecial() == true) { // change condiiton to gameDisplay.getSpecial() == true
        gameDisplay.setSpecial(false);
        
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

GameDisplay *Player::getGameDisplay() {
    return &gameDisplay;
}


