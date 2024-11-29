#include "graphicsobserver.h"

GraphicsObserver::GraphicsObserver(GameDisplay* subject1, GameDisplay* subject2)
    :subject1{subject1}, subject2{subject2}, numReserveRows{subject1->getNumReserveRows()}, nextBlockDock{subject1->getNextBlockDock()},
    width{subject1->getWidth()}, height{subject1->getHeight()}, window{550, 550}
{
        subject1->attach(this);
        subject2->attach(this);
}



// Print separation
void GraphicsObserver::printSeparation() {
    for (int i = 0; i < SEPARATE; ++i) out << ' ';
}



// check message and rerender the message. 

void GraphicsObserver::notify(int blind_status,  string message, int activePlayer, vector<pair<int, int>> blockPixcels, vector<pair<int, int>> nextBlockPixcels) { 
    int xOffset = colStart2;
    int yOffset = rowStart - 30;

    int gap = 2; // Gap between cells
    int adjustedBlockScale = blockScale - gap; // Adjusted size of each cell

    // Clear window
    // window.fillRectangle(0, 0, window.getWidth(), window.getHeight(), 0); // Clear entire screen to background color (white)

    // print the title, high scrore, andtop margin at the beginngin of a new game. 
    if (activePlayer == 0) {
        window.drawString(window.getWidth() / 2 - 30, 30, "BIQUARIS");
        window.drawString(window.getWidth() - 200, 45, "High Score:     " + std::to_string(subject1->getScore()));
        window.drawString(0, 60,"------------------------------------------------------------------------------------------------------------------------");
    }

    // Clearing Player Levels
    if (activePlayer == 1 || activePlayer == 0) window.fillRectangle(colStart1, yOffset - 15, 150, 20, Xwindow::White); // Adjust dimensions and color
    if (activePlayer == 2 || activePlayer == 0) window.fillRectangle(xOffset, yOffset - 15, 150, 20, Xwindow::White);
    // Player Levels
    if (activePlayer == 1 || activePlayer == 0) window.drawString(colStart1, yOffset, "Level:    " + std::to_string(subject1->getLevel()));
    if (activePlayer == 2 || activePlayer == 0) window.drawString(xOffset, yOffset, "Level:    " + std::to_string(subject2->getLevel()));

 
    yOffset += 15;
    // Clearing Player Levels
    if (activePlayer == 1 || activePlayer == 0) window.fillRectangle(colStart1, yOffset - 15, 150, 20, Xwindow::White); // Adjust dimensions and color
    if (activePlayer == 2 || activePlayer == 0) window.fillRectangle(xOffset, yOffset - 15, 150, 20, Xwindow::White);
    // Player Scores
    if (activePlayer == 1 || activePlayer == 0) window.drawString(colStart1, yOffset, "Score:    " + std::to_string(subject1->getScore()));
    if (activePlayer == 2 || activePlayer == 0) window.drawString(xOffset, yOffset, "Score:    " + std::to_string(subject2->getScore()));

    yOffset +=  5;

    // Draw Board Borders
    // Player 1 Board
    if (activePlayer == 0) {
        window.fillRectangle(colStart1, yOffset, width * blockScale + 2, height * blockScale + 2, 1); // black
        window.fillRectangle(colStart1 + 1, yOffset + 1, width * blockScale, height * blockScale, 0); // white

        // Player 2 Board
        window.fillRectangle(xOffset, yOffset, width * blockScale + 2, height * blockScale + 2, 1);
        window.fillRectangle(xOffset + 1, yOffset + 1, width * blockScale , height * blockScale, 0);
    }
    
    // Player Boards
    for (auto c: blockPixcels) {
        int i = c.first;
        int j = c.second;

        // Player 1 Board
        if (activePlayer == 1 || activePlayer == 0){
            char c1 = subject1->getState(i, j);
            int color1 = determineColor(c1, blind_status == 1 && i >= 3 && i <= 11 && j >= 2 && j <= 8);
            window.fillRectangle(colStart1 + j * blockScale + gap / 2, yOffset + i * blockScale + gap / 2,
                                    adjustedBlockScale, adjustedBlockScale, color1);
        }

        // Player 2 Board
        if (activePlayer == 2 || activePlayer == 0){
            char c2 = subject2->getState(i, j);
            int color2 = determineColor(c2, blind_status == 2 && i >= 3 && i <= 11 && j >= 2 && j <= 8);
            window.fillRectangle(xOffset + j * blockScale + gap / 2, yOffset + i * blockScale + gap / 2,
                                 adjustedBlockScale, adjustedBlockScale, color2);
        }
    }

    yOffset += height * blockScale + 10;

    yOffset += 10;

    // Next Block
    window.drawString(colStart1, yOffset, "Next:      ");
    window.drawString(xOffset, yOffset, "Next:      ");
    yOffset += 10;

    for (auto c: nextBlockPixcels) {
        int i = c.first;
        int j = c.second;

        // Player 1 Next Block
        if (activePlayer == 1 || activePlayer == 0) {
            char c1 = subject1->getState(i + height, j);
            int color1 = determineColor(c1, false);
            window.fillRectangle(colStart1 + j * blockScale + gap / 2, yOffset + i * blockScale + gap / 2,
                                 adjustedBlockScale, adjustedBlockScale, color1);
        }

        // Player 2 Next Block
        if (activePlayer == 2 || activePlayer == 0) {
            char c2 = subject2->getState(i + height, j);
            int color2 = determineColor(c2, false);
            window.fillRectangle(xOffset + j * blockScale + gap / 2, yOffset + i * blockScale + gap / 2,
                                 adjustedBlockScale, adjustedBlockScale, color2);
        }
    }
}

// int Graphics
// rerender  the position the block was in and the position the block moves to. 
void GraphicsObserver::reRenderPos() {
    // for (auto c: )

}




int GraphicsObserver::determineColor(char c, bool isBlind) {
    if (isBlind) {
        return Xwindow::Blind; // Blind color
    }
    if (c == 'I') return Xwindow::Cyan;       // 4
    else if (c == 'O') return Xwindow::Yellow; // 5
    else if (c == 'L') return Xwindow::Orange; // 8
    else if (c == 'J') return Xwindow::Blue;   // 7
    else if (c == 'T') return Xwindow::Purple; // 6
    else if (c == 'S') return Xwindow::Green;  // 3
    else if (c == 'Z') return Xwindow::Red;    // 2
    else if (c == '*') return Xwindow::Brown;   // 9
    return Xwindow::White; // Default to white if none match
}


void GraphicsObserver::printTopBoundary() {
    window.drawString(colStart1, rowStart - 20, "Top Boundary");
}

