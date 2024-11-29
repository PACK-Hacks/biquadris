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

// Player constructor
Player::Player(int id, bool text, int seed, string scriptfile, int startLevel):
    id{id}, lost{false}, text{text}, seed{seed}, scriptfile{scriptfile}, 
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

// Converts string to character
char Player::string_to_char(string s) {
    istringstream iss{s};
    char c;
    iss >> c;
    return c;
}

// Check if block of given character exists
bool Player::find_block(char b) { 
    for (size_t i = 0; i < blocks.size(); i++) {
        if (blocks[i] == b) {
            return true;
        }
    }
    return false;
}

// Get unique command from prefix s
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

    return "monkeys"; // No matches

}

// Parse command to return a pair of number of times to run a command, and the command string
pair<int, string> Player::parseCommand(const string &input) {
    int num_len = 0;
    int multiplier;
    int start = 0;
    int len = input.length();
    int pos = 0;

    // Check if start of input is a digit, if so convert to iss and extract number from string
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

string Player::runTurn(string special, TextObserver &to, GraphicsObserver &go) {

    bool status = gameDisplay.moveNextToCurrent(); 

    gameDisplay.generateNextBlock();

    
    int blind_status = 0; // No player is blinded

    if (special != "") { // Check for specials
        istringstream iss{special};
        string curr_special;
        while (iss >> curr_special) {
            if (curr_special == "heavy") {
                gameDisplay.setHeavy(); // sets heavy to true
            } else if (curr_special == "blind") {
                blind_status = id; // Set blind_status to current player's id to blind current player
            } else if (curr_special == "force") {
                char c;
                iss >> c;
                gameDisplay.setCurrentBlock(c);
            }
        }
    }

    // Create player's initial board state
    to.notify(blind_status, "Player " + std::to_string(id) + "'s turn:");
    go.notify(blind_status, "", id);

    bool endTurn = false;

    cout << "Please input a series of commands to move / rotate your block" << endl;

    string command;

    // To accomodate for multiple drops, i.e. 3drop, which would drop player's block immediately for 3 turns
    if (numDrops > 0) {
        gameDisplay.drop();
        numDrops--;
        to.notify(blind_status);
        go.notify(blind_status, "", id);
    } else {
        while(!endTurn) {    
            
            if (!(*in >> command)) { 
                if (in == &sequenceStream) { // in, which points to an ifstream, fails to read
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
            
            // Parse user command
            pair<int, string> p = parseCommand(command);

            command = p.second;
            int multiplier = p.first;

            // Decipher user command
            if (command == left) {
                endTurn = gameDisplay.left(multiplier);
                to.notify(blind_status);
                go.notify(blind_status, "", id);
            } else if (command == right) {
                endTurn = gameDisplay.right(multiplier);
                
                to.notify(blind_status);
                go.notify(blind_status, "", id);
            } else if (command == down) {
                endTurn = gameDisplay.down(multiplier);
                to.notify(blind_status);
                go.notify(blind_status, "", id);
            } else if (command == clockwise) {
                endTurn = gameDisplay.clockwise(multiplier);
                to.notify(blind_status);
                go.notify(blind_status, "", id);
            } else if (command == counterclockwise) {
                endTurn = gameDisplay.counterClockwise(multiplier);
                to.notify(blind_status);
                go.notify(blind_status, "", id);
            } else if (command == drop) {
                numDrops = multiplier - 1;
                if (multiplier >= 1) {
                    gameDisplay.drop();
                    to.notify();
                    go.notify(blind_status, "", id);
                    break;
                }
                
            } else if (command == levelup) {
                bool canLevelUp;
                canLevelUp = gameDisplay.levelUp(multiplier);
                if (canLevelUp == false) {
                    cout << "You cannot level up! You are already at the max level!" << endl;
                } else {
                    to.notify(blind_status, "Levelled Up!");
                    go.notify(blind_status, "Levelled Up!", id);
                }
            } else if (command == leveldown) {
                bool canLevelDown;
                canLevelDown = gameDisplay.levelDown(multiplier);
                if (canLevelDown == false) {
                    cout << "You cannot level down! You are already at the lowest level!" << endl;
                } else {
                    to.notify(blind_status, "Levelled Down!");
                    go.notify(blind_status, "Levelled Down!", id);
                }
            } else if (command == norandom) {
                string file_name;
                if ((*in).fail()) {
                    (*in).clear();
                    (*in).ignore();
                    in = &cin;
                }
                *in >> file_name;
                // Send file name in case random block generation file is read through once already, must be reset
                gameDisplay.norandom(file_name);
                cout << "Switched to reading blocks from " + file_name << endl;
            } else if (command == random) {
                gameDisplay.random();
                cout << "Switched to random block generation" << endl;
            } else if (command.length() == 1 && find_block(string_to_char(command))) { // Change current block to specified block by I, J, T, etc.
                char c = string_to_char(command);
                gameDisplay.setCurrentBlock(c);
                to.notify(blind_status);
                go.notify(blind_status, "", id);
            } else if (command == restart) {
                cout << "Restarting the game!" << endl;
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
                cout << "Switched to reading commands from " + command << endl;
            } else {
                cout << "Please enter a valid command" << endl;
            }
        }
    }
    
    // Drop dummy cell if needed (In level 4 and haven't cleared in 5 turns)
    if (gameDisplay.needDummy()) gameDisplay.dropDummyCell();

    // Check and set the lost field in Display to that of Player
    lost = gameDisplay.getLost();

    blind_status = 0;

    

    if (gameDisplay.getSpecial() == true) { // Check if user attained a special
    // Return the special that the user has attained
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
        cout << "Your turn is now over" << endl;
        return "";
    }
    
}



// Return player lost status
bool Player::getLost() {
    return lost;
}

// Grab the display
GameDisplay *Player::getGameDisplay() {
    return &gameDisplay;
}

// Reset player
void Player::reset() {
    in = &cin;
    blind_status = 0;
    gameDisplay.reset();
}




