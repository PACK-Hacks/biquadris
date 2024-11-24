#include "textobserver.h"
#include "subject.h"
#include "display.h"

// top = left = 0; botoom = HEIGHT; right = WIDTH
// TextObserver::TextObserver(Display* subject, int top, int bottom, int left, int right) 
//     :subject{subject}, top{top}, bottom{bottom}, left{left}, right{right} {
//         subject->attach(this);
// }

int seperate = 10;
int highScore = 100;
int levelIndex = 0;
int score = 0;

// reserve three extra rows for different cell types at top of the baord for rotationn
void TextObserver::notify() {
    // Hisch Score 
    out << "High Score:     " << highScore;

    // level
    out << "Level:     " << levelIndex;

    for (int i = 0; i <= seperate; ++i) out << ' '; // reserve three extra rows

    out << "Level:     " << levelIndex;

    // score
    out << "Score:     " << score;

    for (int i = 0; i <= seperate; ++i) out << ' '; // reserve three extra rows

    out << "Score:     " << score;


    // top margin for player1
    for (int i = left; i <= right; ++i) out << '-'; // reserve three extra rows

    // seperate
    for (int i = 0; i <= seperate; ++i) out << ' '; // reserve three extra rows

    // top margin for player1
    for (int i = left; i <= right; ++i) out << '-'; // reserve three extra rows

    // board
    for (int i = top; i <= bottom; ++i) {

        // plaer1 board
        for (int j = left; j <= right; ++j) {
            out << subject->getState(i, j); // retrieved from Display 
        }

        // seperate
        for (int i = 0; i <= seperate; ++i) out << ' '; // reserve three extra rows

        // plaer2 board
        for (int j = left; j <= right; ++j) {
            out << subject->getState(i, j); // retrieved from Display 
        }

    }

    // bottom margin for player1
    for (int i = left; i <= right; ++i) out << '-'; // reserve three extra rows

    // seperate
    for (int i = 0; i <= seperate; ++i) out << ' '; // reserve three extra rows

    // bottom margin for player2
    for (int i = left; i <= right; ++i) out << '-'; // reserve three extra rows
    
    
    out << "Next:       "; 

    for (int i = 0; i <= seperate; ++i) out << ' '; // reserve three extra rows

    out << "Next:       ";

    // bottom margin
    out << "getNextBook()";
    
    out << "          ";

    out << "getNextBook()";

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
