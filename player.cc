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

    }

    
    Decorator currentBlock{nextHeavy}
}