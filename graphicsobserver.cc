#include "graphicsobserver.h"

// Graphics Observer Constructor
GraphicsObserver::GraphicsObserver(GameDisplay* subject1, GameDisplay* subject2)
    :subject1{subject1}, subject2{subject2}, numReserveRows{subject1->getNumReserveRows()}, nextBlockDock{subject1->getNextBlockDock()},
    width{subject1->getWidth()}, height{subject1->getHeight()} {
        subject1->attach(this);
        subject2->attach(this);
}

// Print separation
void GraphicsObserver::printSeparation() {
    for (int i = 0; i < SEPARATE; ++i) out << ' ';
}

void GraphicsObserver::notify(int id, std::string message) {

    //  int xOffset = colStart2;
    // int yOffset = rowStart;

    // // Clear window
    // window.fillRectangle(0, 0, window.getWidth(), window.getHeight());

    // // High Score
    // window.drawString(colStart1, 10, "High Score: " + std::to_string(highScore));
    // yOffset += 20;

    // // Player Levels
    // window.drawString(colStart1, yOffset, "Level: " + std::to_string(subject1->getLevel()));
    // window.drawString(xOffset, yOffset, "Level: " + std::to_string(subject2->getLevel()));
    // yOffset += 20;

    // // Player Scores
    // window.drawString(colStart1, yOffset, "Score: " + std::to_string(subject1->getScore()));
    // window.drawString(xOffset, yOffset, "Score: " + std::to_string(subject2->getScore()));
    // yOffset += 30;

    // // Player Boards
    // for (int i = 0; i < height; ++i) {
    //     for (int j = 0; j < width; ++j) {
    //         // Player 1 Board
    //         char c1 = subject1->getState(i, j);
    //         int color1 = determineColor(c1, id == 1 && i >= 3 && i <= 11 && j >= 2 && j <= 8);
    //         window.fillRectangle(colStart1 + j * blockScale, yOffset + i * blockScale, blockScale, blockScale, color1);

    //         // Player 2 Board
    //         char c2 = subject2->getState(i, j);
    //         int color2 = determineColor(c2, id == 2 && i >= 3 && i <= 11 && j >= 2 && j <= 8);
    //         window.fillRectangle(xOffset + j * blockScale, yOffset + i * blockScale, blockScale, blockScale, color2);
    //     }
    // }
    // yOffset += height * blockScale;

    // // Bottom Margin
    // yOffset += 10;

    // // Next Block
    // window.drawString(colStart1, yOffset, "Next:");
    // window.drawString(xOffset, yOffset, "Next:");
    // yOffset += 20;

    // for (int i = 0; i < nextBlockDock; ++i) {
    //     for (int j = 0; j < width; ++j) {
    //         // Player 1 Next Block
    //         char c1 = subject1->getState(i + height, j);
    //         int color1 = determineColor(c1, false);
    //         window.fillRectangle(colStart1 + j * blockScale, yOffset + i * blockScale, blockScale, blockScale, color1);

    //         // Player 2 Next Block
    //         char c2 = subject2->getState(i + height, j);
    //         int color2 = determineColor(c2, false);
    //         window.fillRectangle(xOffset + j * blockScale, yOffset + i * blockScale, blockScale, blockScale, color2);
    //     }
    // }
}

int GraphicsObserver::determineColor(char c, bool isBlind) {
    if (isBlind) {
        return 5; // Blind color
    }
    if ('a' <= c && c <= 'z') {
        return 2; // Red for lowercase letters
    } else if ('A' <= c && c <= 'Z') {
        return 3; // Green for uppercase letters
    } else if ('0' <= c && c <= '9') {
        return 4; // Blue for digits
    } else if (c == ' ') {
        return 0; // White for spaces
    } else {
        return 1; // Black for everything else
    }
}


void GraphicsObserver::printTopBoundary() {
    window.drawString(colStart1, rowStart - 20, "Top Boundary");
}


// void TextObserver::notify(int id) {
//     out << endl;

//     // High Score 
//     out << "High Score:     " << highScore << endl;

//     int scoreP1 = subject1->getScore();
//     int levelP1 = subject1->getLevel();
//     int scoreP2 = subject2->getScore();
//     int levelP2 = subject2->getLevel();

//     // level
//     out << "Level:    " << subject1->getLevel();

//     printSeparation(); // reserve three extra rows

//     out << "Level:    " << subject2->getLevel() << endl;

//     // score
//     out << "Score:    " << scoreP1;
    

//     printSeparation(); // reserve three extra rows

//     out << "Score:    " << scoreP2 << endl;


//     // top margin for player1
//     for (int i = 0; i < width; ++i) out << '-'; // reserve three extra rows

//     // seperate
//     printSeparation(); // reserve three extra rows

//     // top margin for player1
//     for (int i = 0; i < width; ++i) out << '-'; // reserve three extra rows

//     cout << endl;
//     // board
//         for (int i = 0; i < height; ++i) {

//             // when blind is active cover row 3 to 12 column 3 to 9
//             if ( 3 + 2 <= i && i <= 11 + 3 ) {
//                 for (int j = 0; j < width; ++j) {
//                     if (id == 1 && 2 <= j && j <= 8) {
//                         out << '?';
//                         continue;
//                     }
//                     out << subject1->getState(i, j); // retrieved from GameDisplay 
//                 }

//                 // seperate
//                 printSeparation(); // reserve three extra rows

//                 // plaer2 board
//                 for (int j = 0; j < width; ++j) {
//                     if (id == 2  && 2 <= j && j <= 8) {
//                         out << '?';
//                         continue;
//                     }
//                     out << subject2->getState(i, j); // retrieved from GameDisplay 
//                 }
//                 out << endl;
//                 continue;
//             }
//             // plaer1 board
//             for (int j = 0; j < width; ++j) {
//                 out << subject1->getState(i, j); // retrieved from GameDisplay 
//             }

//             // seperate
//             printSeparation(); // reserve three extra rows


//             // plaer2 board
//             for (int j = 0; j < width; ++j) {
//                 out << subject2->getState(i, j); // retrieved from GameDisplay 
//             }
//             out << endl;
//         }

//     // bottom margin for player1
//     for (int i = 0; i < width; ++i) out << '-'; // reserve three extra rows

//     // seperate
//     printSeparation(); // reserve three extra rows

//     // bottom margin for player2
//     for (int i = 0; i < width; ++i) out << '-'; // reserve three extra rows
    
//     out << endl;
    
//     out << "Next:      "; 

//     printSeparation(); // reserve three extra rows

//     out << "Next:      " << endl;


//     // Printing the next block dock
//     for (int i = 0; i < nextBlockDock; ++i) {
//         for (int j = 0; j < width; ++j) {
//             out << subject1->getState(i + height, j); // retrieved from GameDisplay
//         }
//         for (int i = 0; i < SEPARATE; i++) out << " ";
//         for (int j = 0; j < width; ++j) {
//             out << subject2->getState(i + height, j); // retrieved from GameDisplay
//         }
//         out << endl;
//     }
//     out << endl << endl;
//     // where is generateNextBlock() called?  
//     // should there be a nextBlock field? 
// }