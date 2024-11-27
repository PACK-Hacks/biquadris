#include "textobserver.h"
#include "subject.h"
#include "display.h"

// 0 = 0 = 0; botoom = HEIGHT; width = WIDTH
TextObserver::TextObserver(Display* subject1, Display* subject2) 
    :subject1{subject1}, subject2{subject2}, numReserveRows{subject1->getNumReserveRows()}, nextBlockDock{subject1->getNextBlockDock()},
    width{subject1->getWidth()}, height{subject1->getHeight()} {
        subject1->attach(this);
        subject2->attach(this);
}


// top = left = 0; botoom = HEIGHT; right = WIDTH
// TextObserver::TextObserver(Display* subject, int top, int bottom, int left, int right) 
//     :subject{subject}, top{top}, bottom{bottom}, left{left}, right{right} {
//         subject->attach(this);
// }

int highScore = 100;

// Print separation
void TextObserver::printSeparation() {
    for (int i = 0; i < SEPARATE; ++i) out << ' ';
}

// reserve three extra rows for different cell types at top of the baord for rotationn
void TextObserver::notify(int id) {
    out << endl;

    // High Score 
    out << "High Score:     " << highScore << endl;

    int scoreP1 = subject1->getScore();
    int levelP1 = subject1->getLevel();
    int scoreP2 = subject2->getScore();
    int levelP2 = subject2->getLevel();

    out << "Level:    " << levelP1;

    printSeparation(); // reserve three extra rows

    out << "Level:    " << levelP2 << endl;

    // score
    out << "Score:    " << scoreP1;

    printSeparation(); // reserve three extra rows

    out << "Score:    " << scoreP2 << endl;


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
                    if (id == 1 && 2 <= j && j <= 8) {
                        out << '?';
                        continue;
                    }
                    out << subject1->getState(i, j); // retrieved from Display 
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

        // for (int i = 0; i < height; ++i) {

        //     // plaer1 board
        //     for (int j = 0; j < width; ++j) {
        //         out << subject1->getState(i, j); // retrieved from Display 
        //     }

        //     // seperate
        //     printSeparation(); // reserve three extra rows


        //     // plaer2 board
        //     for (int j = 0; j < width; ++j) {
        //         out << subject2->getState(i, j); // retrieved from Display 
        //     }
        //     out << endl;
        // }

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





