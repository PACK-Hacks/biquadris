#include "level.h"

// Level constructor
Level::Level(bool heavy, ifstream &blockFile) : heavy{heavy}, blockFile{blockFile} {};

// Level destructor
Level::~Level() {};

// Generating a pointer to a choosen block
Block *Level::makeChosenBlock(char block) {
    // create a heavy block if the heavy field of the level is true or if the block is forced to be heavy
    if (block == 'I') {
        return new IBlock{heavy}; 
    }
    else if (block == 'O') {
        return new OBlock{heavy}; 
    }
    else if (block == 'L') {
        return new LBlock{heavy}; 
    }
    else if (block == 'J') {
        return new JBlock{heavy}; 
    }
    else if (block == 'T') {
        return new TBlock{heavy}; 
    }
    else if (block == 'S') {
        return new SBlock{heavy}; 
    }
    else if (block == 'Z') {
        return new ZBlock{heavy}; 
    }
}


// Level0 constructor
Level0::Level0(ifstream &blockFile) : Level{false, blockFile} {};

// Level0 destructor
Level0::~Level0() {}

// Block generation of Level0
Block *Level0::makeBlock() {
    char block;
    blockFile >> block;

    // Create block according to file
    return makeChosenBlock(block);
}

// Level1 constructor
Level1::Level1(ifstream &blockFile) : Level{false, blockFile} {};

// Level1 destructor
Level1::~Level1() {}

// Block generation of Level1
Block *Level1::makeBlock() {
    int randNum = rand() % 12;    // Random number from 0-11

    if (randNum < 1) {
        return new SBlock{false};
    }
    else if (randNum < 2) {
        return new ZBlock{false};
    }
    else if (randNum < 4) {
        return new IBlock{false};
    }
    else if (randNum < 6) {
        return new OBlock{false};
    }
    else if (randNum < 8) {
        return new LBlock{false};
    }
    else if (randNum < 10) {
        return new JBlock{false};
    }
    else if (randNum < 12) {
        return new TBlock{false};
    }
}

// Level2 constructor
Level2::Level2(ifstream &blockFile) : Level{false, blockFile} {};

// Level2 destructor
Level2::~Level2() {}

// Block generation of Level2
Block *Level2::makeBlock() {
    int randNum = rand() % 7;    // Random number from 0-6

    if (randNum == 0) {
        return new SBlock{false};
    }
    else if (randNum == 1) {
        return new ZBlock{false};
    }
    else if (randNum == 2) {
        return new IBlock{false};
    }
    else if (randNum == 3) {
        return new OBlock{false};
    }
    else if (randNum == 4) {
        return new LBlock{false};
    }
    else if (randNum == 5) {
        return new JBlock{false};
    }
    else if (randNum == 6) {
        return new TBlock{false};
    }
}

// Level3 constructor
Level3::Level3(ifstream &blockFile) : Level{true, blockFile} {};

// Level3 destructor
Level3::~Level3() {}

// Block generation of Level3
Block *Level3::makeBlock() {
    int randNum = rand() % 9;    // Random number from 0-8

    if (randNum < 2) {
        return new SBlock{true};
    }
    else if (randNum < 4) {
        return new ZBlock{true};
    }
    else if (randNum < 5) {
        return new IBlock{true};
    }
    else if (randNum < 6) {
        return new OBlock{true};
    }
    else if (randNum < 7) {
        return new LBlock{true};
    }
    else if (randNum < 8) {
        return new JBlock{true};
    }
    else if (randNum < 9) {
        return new TBlock{true};
    }
}

// Level4 constructor
Level4::Level4(ifstream &blockFile) : Level{true, blockFile} {};

// Level4 destructor
Level4::~Level4() {}

// Block generation of Level4
Block *Level4::makeBlock() {
    int randNum = rand() % 9;    // Random number from 0-8

    if (randNum < 2) {
        return new SBlock{true};
    }
    else if (randNum < 4) {
        return new ZBlock{true};
    }
    else if (randNum < 5) {
        return new IBlock{true};
    }
    else if (randNum < 6) {
        return new OBlock{true};
    }
    else if (randNum < 7) {
        return new LBlock{true};
    }
    else if (randNum < 8) {
        return new JBlock{true};
    }
    else if (randNum < 9) {
        return new TBlock{true};
    }
}
