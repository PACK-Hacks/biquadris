#include "level.h"

// Level constructor
Level::Level(bool heavy, int level, ifstream &blockFile, const string blockFileString, ifstream &norandomFile, string norandomFileString) : 
heavy{heavy}, level{level}, blockFile{blockFile}, blockFileString{blockFileString}, norandomFile{norandomFile}, norandomFileString{norandomFileString} {};

// Level destructor
Level::~Level() {};


// Helper function to read the next block character with reset logic
char Level::getNextBlockChar() {
    char block;
    if (!(blockFile >> block)) { // If reading fails (possibly due to EOF)
        blockFile = ifstream{blockFileString};
        blockFile >> block;
    }
    return block;
}

char Level::getNextBlockCharNoRandom() {
    char block;
    if (!(norandomFile >> block)) { // If reading fails (possibly due to EOF)
        norandomFile = ifstream{norandomFileString};
        norandomFile >> block;
    }
    return block;
}


void Level::setNoRandom(string file_name, ifstream &f) {
    norandom = true;
    norandomFileString = file_name;
}

void Level::setRandom() {
    norandom = false;
}



// Generating a pointer to a choosen block
Block *Level::makeChosenBlock(char block) {
    // create a heavy block if the heavy field of the level is true or if the block is forced to be heavy
    if (block == 'I') {
        return new IBlock{heavy, level}; 
    }
    else if (block == 'O') {
        return new OBlock{heavy, level}; 
    }
    else if (block == 'L') {
        return new LBlock{heavy, level}; 
    }
    else if (block == 'J') {
        return new JBlock{heavy, level}; 
    }
    else if (block == 'T') {
        return new TBlock{heavy, level}; 
    }
    else if (block == 'S') {
        return new SBlock{heavy, level}; 
    }
    else {
        return new ZBlock{heavy, level}; 
    }
}


// Level0 constructor
Level0::Level0(ifstream &blockFile, const string &blockFileString, ifstream &norandomFile, string norandomFileString) : 
Level{false, 0, blockFile, blockFileString, norandomFile, norandomFileString} {};

// Level0 destructor
Level0::~Level0() {}

// Block generation of Level0
Block *Level0::makeBlock() {
    // Create block according to file
    char block = getNextBlockChar();
    return makeChosenBlock(block);
}

// Level1 constructor
Level1::Level1(ifstream &blockFile, const string &blockFileString, ifstream &norandomFile, string norandomFileString) : 
Level{false, 1, blockFile, blockFileString, norandomFile, norandomFileString} {};

// Level1 destructor
Level1::~Level1() {}

// Block generation of Level1
Block *Level1::makeBlock() {
    int randNum = rand() % 12;    // Random number from 0-11

    if (randNum < 1) {
        return new SBlock{false, level};
    }
    else if (randNum < 2) {
        return new ZBlock{false, level};
    }
    else if (randNum < 4) {
        return new IBlock{false, level};
    }
    else if (randNum < 6) {
        return new OBlock{false, level};
    }
    else if (randNum < 8) {
        return new LBlock{false, level};
    }
    else if (randNum < 10) {
        return new JBlock{false, level};
    }
    else {
        return new TBlock{false, level};
    }
}

// Level2 constructor
Level2::Level2(ifstream &blockFile, const string &blockFileString, ifstream &norandomFile, string norandomFileString) : 
Level{false, 2, blockFile, blockFileString, norandomFile, norandomFileString} {};

// Level2 destructor
Level2::~Level2() {}

// Block generation of Level2
Block *Level2::makeBlock() {
    int randNum = rand() % 7;    // Random number from 0-6

    if (randNum == 0) {
        return new SBlock{false, level};
    }
    else if (randNum == 1) {
        return new ZBlock{false, level};
    }
    else if (randNum == 2) {
        return new IBlock{false, level};
    }
    else if (randNum == 3) {
        return new OBlock{false, level};
    }
    else if (randNum == 4) {
        return new LBlock{false, level};
    }
    else if (randNum == 5) {
        return new JBlock{false, level};
    }
    else {
        return new TBlock{false, level};
    }
}

// Level3 constructor
Level3::Level3(ifstream &blockFile, const string &blockFileString, ifstream &norandomFile, string norandomFileString) : 
Level{true, 3, blockFile, blockFileString, norandomFile, norandomFileString} {};

// Level3 destructor
Level3::~Level3() {}

// Block generation of Level3
Block *Level3::makeBlock() {
    if (norandom) {
        char block = getNextBlockCharNoRandom();
        return makeChosenBlock(block);
    }
    int randNum = rand() % 9;    // Random number from 0-8

    if (randNum < 2) {
        return new SBlock{true, level};
    }
    else if (randNum < 4) {
        return new ZBlock{true, level};
    }
    else if (randNum < 5) {
        return new IBlock{true, level};
    }
    else if (randNum < 6) {
        return new OBlock{true, level};
    }
    else if (randNum < 7) {
        return new LBlock{true, level};
    }
    else if (randNum < 8) {
        return new JBlock{true, level};
    }
    else {
        return new TBlock{true, level};
    }
}

// Level4 constructor
Level4::Level4(ifstream &blockFile, const string &blockFileString, ifstream &norandomFile, string norandomFileString) : 
Level{true, 4, blockFile, blockFileString, norandomFile, norandomFileString} {};

// Level4 destructor
Level4::~Level4() {}

// Block generation of Level4
Block *Level4::makeBlock() {
    if (norandom) {
        char block = getNextBlockCharNoRandom();
        return makeChosenBlock(block);
    }
    int randNum = rand() % 9;    // Random number from 0-8

    if (randNum < 2) {
        return new SBlock{true, level};
    }
    else if (randNum < 4) {
        return new ZBlock{true, level};
    }
    else if (randNum < 5) {
        return new IBlock{true, level};
    }
    else if (randNum < 6) {
        return new OBlock{true, level};
    }
    else if (randNum < 7) {
        return new LBlock{true, level};
    }
    else if (randNum < 8) {
        return new JBlock{true, level};
    }
    else {
        return new TBlock{true, level};
    }
}
