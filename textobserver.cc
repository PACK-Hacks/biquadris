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
int levelIndex = 0;
int score = 0;

// reserve three extra rows for different cell types at top of the baord for rotationn
void TextObserver::notify() {
    out << endl;

    // High Score 
    out << "High Score:     " << highScore << endl;

    // level
    out << "Level:    " << levelIndex;

    for (int i = 0; i < SEPARATE; ++i) out << ' '; // reserve three extra rows

    out << "Level:    " << levelIndex << endl;

    // score
    out << "Score:    " << score;

    for (int i = 0; i < SEPARATE; ++i) out << ' '; // reserve three extra rows

    out << "Score:    " << score << endl;


    // top margin for player1
    for (int i = 0; i < width; ++i) out << '-'; // reserve three extra rows

    // seperate
    for (int i = 0; i < SEPARATE; ++i) out << ' '; // reserve three extra rows

    // top margin for player1
    for (int i = 0; i < width; ++i) out << '-'; // reserve three extra rows

    cout << endl;
    // board
    for (int i = 0; i < height; ++i) {

        // plaer1 board
        for (int j = 0; j < width; ++j) {
            out << subject1->getState(i, j); // retrieved from Display 
        }

        // seperate
        for (int i = 0; i < SEPARATE; ++i) out << ' '; // reserve three extra rows


        // plaer2 board
        for (int j = 0; j < width; ++j) {
            out << subject2->getState(i, j); // retrieved from Display 
        }
        out << endl;
    }

    // bottom margin for player1
    for (int i = 0; i < width; ++i) out << '-'; // reserve three extra rows

    // seperate
    for (int i = 0; i < SEPARATE; ++i) out << ' '; // reserve three extra rows

    // bottom margin for player2
    for (int i = 0; i < width; ++i) out << '-'; // reserve three extra rows
    
    out << endl;
    
    out << "Next:      "; 

    for (int i = 0; i < SEPARATE; ++i) out << ' '; // reserve three extra rows

    out << "Next:      " << endl;

    // bottom margin
    for (int j = 0; j < width; ++j) {
        out << subject1->getState(height, j); // retrieved from Display
        out << subject2->getState(height, j); // retrieved from Display

    }
    out << endl;
    for (int i = 1; i < nextBlockDock; ++i) {
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

// void TextObserver::notify() {
//     out << '+';
//     for (int j = left; j <= right; ++j) out << '-'; // reserve three extra rows
//     out << '+' << std::endl;

//     for (int i = top; i <= bottom; ++i) {
//         out << '|';
//         for (int j = left; j <= right; ++j) {
//             out << subject->getState(i, j); // retrieved from Display 
//         }
//         out << '|' << std::endl;
//     }
//     out << '+';
//     for (int j = left; j <= right; ++j) out << '-';
//     out << '+' << std::endl;
// }

// memeory deltion is delegated to Observer
// TextObserver::~TextObserver() {
//     subject->detach(this);
// }
