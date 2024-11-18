Player::runTurn(string special) {
    if (special == "") {

    } else {
        istringstream iss{special};
        string s;

        while (iss >> s) {
            if (s == "blind") {

            }
            if (s == "force") {
                iss >> nextBlock;
            } 
            if (s == "heavy") {

            }
        }
        board  = new Blank;
    }

    string command;
    // create variables for each command, which can be modified by the user 
    Level *lvl = 

    while(cin >> command) {
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
            
        }
    }

    

    
    Decorator currentBlock{nextHeavy}
}