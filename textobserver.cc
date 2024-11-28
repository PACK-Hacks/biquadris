#include "textobserver.h"

// 0 = 0 = 0; botoom = HEIGHT; width = WIDTH
TextObserver::TextObserver(GameDisplay* subject1, GameDisplay* subject2) 
    :subject1{subject1}, subject2{subject2}, numReserveRows{subject1->getNumReserveRows()}, nextBlockDock{subject1->getNextBlockDock()},
    width{subject1->getWidth()}, height{subject1->getHeight()} {
        subject1->attach(this);
        subject2->attach(this);
}


// Print separation
void TextObserver::printSeparation() {
    for (int i = 0; i < SEPARATE; ++i) out << ' ';
}

// Returns a string containing the score preceded by a calculated number of spaces
// to ensure proper formatting even when score has multiple digits
std::string TextObserver::scoreFormating(int score) {
    string output;
    int digits = 1;

    int scoreCopy = score;

    while (scoreCopy / 10 != 0) {
        scoreCopy /= 10;
        digits++;
    }

    for (int i = 0; i < 5 - digits; ++i) {
        output += " ";
    }

    output += std::to_string(score);
    return output;
}

// reserve three extra rows for different cell types at top of the baord for rotationn
void TextObserver::notify(int id, std::string message) {
    out << endl << endl;
    
    // Print the message if there is one
    if (!message.empty()) {
        out << message << endl << endl;
    }


    int scoreP1 = subject1->getScore();
    int highScore1 = subject1->getHighScore();
    int levelP1 = subject1->getLevel();
    int scoreP2 = subject2->getScore();
    int highScore2 = subject2->getHighScore();
    int levelP2 = subject2->getLevel();

    out << "High       ";

    printSeparation();
    
    out << "High       " << endl;

    // High Score 
    out << "Score:" << scoreFormating(highScore1);

    printSeparation();

    // High Score 
    out << "Score:" << scoreFormating(highScore2) << endl;

    // level
    out << "Level:    " << subject1->getLevel();

    printSeparation(); // reserve three extra rows

    out << "Level:    " << subject2->getLevel() << endl;

    // score
    out << "Score:" << scoreFormating(scoreP1);
    

    printSeparation(); // reserve three extra rows

    out << "Score:" << scoreFormating(scoreP2) << endl;


    // top margin for player1
    for (int i = 0; i < width; ++i) out << '-'; // reserve three extra rows

    // seperate
    printSeparation(); // reserve three extra rows

    // top margin for player1
    for (int i = 0; i < width; ++i) out << '-'; // reserve three extra rows

    cout << endl;
    // board
        for (int i = 0; i < height; ++i) {

            // when blind is active cover row 3 to 12 column 3 to 9
            if ( 3 + 2 <= i && i <= 11 + 3 ) {
                for (int j = 0; j < width; ++j) {
                    if (id == 1 && 2 <= j && j <= 8) {  // id = 1 => blind on p1
                        out << '?';                     // id = 2 => blind on p2
                    }                                   // id = 0 => blind on neither
                    // // Print '-' for lid row
                    // else if (i = numReserveRows) {
                    //     out << '-';
                    // }
                    else {
                        out << subject1->getState(i, j); // retrieved from Display 
                    }
                }

                // seperate
                printSeparation(); // reserve three extra rows

                // plaer2 board
                for (int j = 0; j < width; ++j) {
                    if (id == 2  && 2 <= j && j <= 8) {
                        out << '?';
                        continue;
                    }
                    out << subject2->getState(i, j); // retrieved from Display 
                }
                out << endl;
                continue;
            }
            // plaer1 board
            for (int j = 0; j < width; ++j) {
                out << subject1->getState(i, j); // retrieved from Display 
            }

            // seperate
            printSeparation(); // reserve three extra rows


            // plaer2 board
            for (int j = 0; j < width; ++j) {
                out << subject2->getState(i, j); // retrieved from Display 
            }
            out << endl;
        }

    // bottom margin for player1
    for (int i = 0; i < width; ++i) out << '-'; // reserve three extra rows

    // seperate
    printSeparation(); // reserve three extra rows

    // bottom margin for player2
    for (int i = 0; i < width; ++i) out << '-'; // reserve three extra rows
    
    out << endl;
    
    out << "Next:      "; 

    printSeparation(); // reserve three extra rows

    out << "Next:      " << endl;


    // Printing the next block dock
    for (int i = 0; i < nextBlockDock; ++i) {
        for (int j = 0; j < width; ++j) {
            out << subject1->getState(i + height, j); // retrieved from Display
        }
        for (int i = 0; i < SEPARATE; i++) out << " ";
        for (int j = 0; j < width; ++j) {
            out << subject2->getState(i + height, j); // retrieved from Display
        }
        out << endl;
    }
    out << endl << endl;
    // where is generateNextBlock() called?  
    // should there be a nextBlock field? 
}





