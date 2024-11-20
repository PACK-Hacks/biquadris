Player::runTurn(string special) {
    // if (special == "") {

    // } else {
    //     istringstream iss{special};
    //     string s;

    //     block = level->getBlock();
    //     heavy = level->getHeavy();
    //     dummy = level->getDummy();

    //     while (iss >> s) {
    //         if (s == "blind") {     // set nextBlind to false in drop method
    //             isBlind = true;
    //         }
    //         if (s == "force") {
    //             iss >> isBlock;
    //         } 
    //         if (s == "heavy") {
    //             heavy = true;
    //         }
    //     }
    //     display.board() = new Board{block, isHeavy, isBlind, dummy, ...};
    // }

    display.moveNextToCurrent();
    display.generateNextBlock(special);

    string command;
    // create variables for each command, which can be modified by the user 
    Level *lvl = 

    while(cin >> command) {     // fstream >> command
        if (command == left) {
            display.board->left();
            display.render();
        } else if (command == right) {
            display.board->right();
            display.render();
        } else if (command == down) {
            display.board->down();
            display.render();
        } else if (command == drop) {
            display.board->drop();
            display.render();
            break;
        } else if (command == clockwise) {
            display.board->clockwise();
            display.render();
        } else if (command == counterclockwise) {
            display.board->counterclockwise();
            display.render();
        } else if (command == levelup) {
            levelup()
        } else if (command == sequence) {
            string file_name;
            cin >> file_name;
            ifstream f{file_name};
            while (f >> command) {
                // run lines 34 to 54 somehow
            }
        }
    }

    

    
    Decorator currentBlock{nextHeavy}
}