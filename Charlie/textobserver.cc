#include "textobserver.h"
#include "subject.h"
#include "display.h"

// 0 = 0 = 0; botoom = HEIGHT; width = WIDTH
TextObserver::TextObserver(Display* subject) 
    :subject{subject}, width{subject->getWidth()}, height{subject->getHeight()} {
        subject->attach(this);
}

int seperate = 10;
int highScore = 100;
int levelIndex = 0;
int score = 0;

// reserve three extra rows for different cell types at 0 of the baord for rotationn
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


    // 0 margin for player1
    for (int i = 0; i <= width; ++i) out << '-'; // reserve three extra rows

    // seperate
    for (int i = 0; i <= seperate; ++i) out << ' '; // reserve three extra rows

    // 0 margin for player1
    for (int i = 0; i <= width; ++i) out << '-'; // reserve three extra rows

    // board
    for (int i = 0; i <= height; ++i) {

        // plaer1 board
        for (int j = 0; j <= width; ++j) {
            out << subject->getState(i, j); // retrieved from Display 
        }

        // seperate
        for (int i = 0; i <= seperate; ++i) out << ' '; // reserve three extra rows

        // plaer2 board
        for (int j = 0; j <= width; ++j) {
            out << subject->getState(i, j); // retrieved from Display 
        }

    }

    // height margin for player1
    for (int i = 0; i <= width; ++i) out << '-'; // reserve three extra rows

    // seperate
    for (int i = 0; i <= seperate; ++i) out << ' '; // reserve three extra rows

    // height margin for player2
    for (int i = 0; i <= width; ++i) out << '-'; // reserve three extra rows
    
    
    out << "Next:       "; 

    for (int i = 0; i <= seperate; ++i) out << ' '; // reserve three extra rows

    out << "Next:       ";

    // height margin
    out << "getNextBook()";
    
    out << "          ";

    out << "getNextBook()";

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
