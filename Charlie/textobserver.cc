#include "textobserver.h"
#include "subject.h"
#include "display.h"

// 0 = 0 = 0; botoom = HEIGHT; width = WIDTH
TextObserver::TextObserver(Display* subject) 
    :subject{subject}, numReserveRows{subject->getNumReserveRows()}, nextBlockDock{subject->getNextBlockDock()},
    width{subject->getWidth()}, height{subject->getHeight()} {
        subject->attach(this);
}

int highScore = 100;
int levelIndex = 0;
int score = 0;

void TextObserver::printSeparation() {
    for (int i = 0; i < SEPARATE; i++) {
        out << " ";
    }
}

void TextObserver::printTopBoundary() {
    for (int i = 0; i < SEPARATE; i++) {
        out << "-";
    }
}

// reserve three extra rows for different cell types at 0 of the baord for rotationn
void TextObserver::notify() {
    // High Score 
    out << "High Score:     " << highScore << endl;

    out << "Level:     " << levelIndex << endl;

    // score
    out << "Score:     " << score << endl;

    // Print the reserve rows and top boundary
    for (int i = 0; i < numReserveRows; ++i) {
        printSeparation();
        out << "|";
        // player1 board
        for (int j = 0; j < width; ++j) {
            out << subject->getState(i, j); // retrieved from Display 
        }

        out << "|" << endl;
    }

    // top margin for player1
    printTopBoundary();
    out << "+";
    for (int j = 0; j < width; ++j) {
        out << subject->getState(numReserveRows, j); // retrieved from Display
    }
    // for (int i = 0; i < width; ++i) {
    //     out << " "; // retrieved from Display
    // }
    out << "+";
    printTopBoundary();
    out << endl;

    // board
    for (int i = numReserveRows + 1; i < height; ++i) {
        printSeparation();
        out << "|";
        // player1 board
        for (int j = 0; j < width; ++j) {
            out << subject->getState(i, j); // retrieved from Display 
        }

        out << "|" << endl;
    }

    // height margin for player1
    printSeparation();
    out << "+";
    for (int i = 0; i < width; ++i) out << '-'; // reserve three extra rows
    out << "+" << endl;


    // render nextBlock
    out << "Next: ";

    for (int j = 0; j < width; ++j) {
        out << subject->getState(height, j); // retrieved from Display
    }
    out << endl;
    for (int i = 1; i < nextBlockDock; ++i) {
        printSeparation();
        for (int j = 0; j < width; ++j) {
            out << subject->getState(i + height, j); // retrieved from Display
        }
        out << endl;
    }


    out << endl << endl;

    // where is generateNextBlock() called?  
    // should there be a nextBlock field? 

}

// void TextObserver::notify() {
//     out << '+';
//     for (int j = 0; j <= width; ++j) out << '-'; // reserve three extra rows
//     out << '+' << std::endl;

//     for (int i = top; i <= height; ++i) {
//         out << '|';
//         for (int j = 0; j <= width; ++j) {
//             out << subject->getState(i, j); // retrieved from Display 
//         }
//         out << '|' << std::endl;
//     }
//     out << '+';
//     for (int j = 0; j <= width; ++j) out << '-';
//     out << '+' << std::endl;
// }

// memeory deltion is delegated to Observer
// TextObserver::~TextObserver() {
//     subject->detach(this);
// }
