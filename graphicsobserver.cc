#include "graphicsobserver.h"

// Graphics Observer Constructor
GraphicsObserver::GraphicsObserver(GameDisplay* subject1, GameDisplay* subject2)
    :subject1{subject1}, subject2{subject2}, active{active}, numReserveRows{subject1->getNumReserveRows()}, nextBlockDock{subject1->getNextBlockDock()},
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

void GraphicsObserver::notify(int blind_status, string message, int activePlayer) { 
    int xOffset = colStart2;
    int yOffset = rowStart - 30;

    int gap = 2; // Gap between cells
    int adjustedBlockScale = blockScale - gap; // Adjusted size of each cell

    // print the title, high scrore, andtop margin at the beginngin of a new game. 
    if (activePlayer == 0) {
        window.drawString(window.getWidth() / 2 - 30, 30, "BIQUARIS");
        window.drawString(20, 45, "P.A.C.K.");

        window.drawString(window.getWidth() - 200, 45, "High Score:     " + std::to_string(subject1->getScore()));
        window.drawString(0, 60,"----------------------------------------------------------------------------------------------------");
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
        window.fillRectangle(colStart1 + 1, yOffset + 1, width * blockScale, height * blockScale, Xwindow::LightGray); // white
        window.fillRectangle(colStart1 + 1, yOffset + 3 * blockScale + gap / 2, width * blockScale, (height-3) * blockScale , Xwindow::WhiteSmoke); // white


        // Player 2 Board
        window.fillRectangle(xOffset, yOffset, width * blockScale + 2, height * blockScale + 2, 1);
        window.fillRectangle(xOffset + 1, yOffset + 1, width * blockScale , height * blockScale, Xwindow::LightGray);
        window.fillRectangle(xOffset + 1, yOffset + 3 * blockScale + gap / 2, width * blockScale, (height-3) * blockScale , Xwindow::WhiteSmoke); // white

        for (int i = 1; i < height; ++i) { // Start at 1 to avoid drawing the top border
            window.fillRectangle(colStart1 + 1, yOffset + i * blockScale - 1, width * blockScale, 1, Xwindow::Black); // Horizontal line
            window.fillRectangle(xOffset + 1, yOffset + i * blockScale - 1, width * blockScale, 1, Xwindow::Black); // Horizontal line for Player 2
        }

        // Vertical grid
        for (int j = 1; j < width; ++j) { // Start at 1 to avoid drawing the left border
            window.fillRectangle(colStart1 + j * blockScale, yOffset, 1, height * blockScale, Xwindow::Black); // Vertical line
            window.fillRectangle(xOffset + j * blockScale, yOffset, 1, height * blockScale, Xwindow::Black); // Vertical line for Player 2
        }
    }
    
    set<pair<int,int>> rerenderedCoordinates; 


    // Pass the current board to the past board and map out new current board
    if (activePlayer == 1 || activePlayer == 0) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                pastBoard1[i][j] = currentBoard1[i][j];

                char c = subject1->getState(i, j);

                if (blind_status == 1 && i >= 2 + numReserveRows && i < 12 + numReserveRows && j >= 2 && j < 9) {
                    currentBoard1[i][j] = 'B';
                }
                else if (c == '.' && i < 3) {
                    currentBoard1[i][j] = ',';
                }
                else {
                    currentBoard1[i][j] = c;
                }

                // Rerender if current board and past board aren't the same
                if (currentBoard1[i][j] != pastBoard1[i][j]) {
                    int color1 = determineColor(currentBoard1[i][j]);            
        
                    window.fillRectangle(colStart1 + j * blockScale + gap / 2, yOffset + i * blockScale + gap / 2,
                                    adjustedBlockScale, adjustedBlockScale, color1);
                }
            }
        }
    }
    else if (activePlayer == 2 || activePlayer == 0) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                pastBoard2[i][j] = currentBoard2[i][j];

                char c = subject2->getState(i, j);

                if (blind_status == 2 && i >= 2 + numReserveRows && i < 12 + numReserveRows && j >= 2 && j < 9) {
                    currentBoard2[i][j] = 'B';
                }
                else if (c == '.' && i < 3) {
                    currentBoard2[i][j] = ',';
                }
                else {
                    currentBoard2[i][j] = c;
                }

                // Rerender if current board and past board aren't the same
                if (currentBoard2[i][j] != pastBoard2[i][j]) {
                    int color2 = determineColor(currentBoard2[i][j]);            
        
                    window.fillRectangle(xOffset + j * blockScale + gap / 2, yOffset + i * blockScale + gap / 2,
                                adjustedBlockScale, adjustedBlockScale, color2);
                }
            }
        }
    }

    yOffset += height * blockScale + 10;

    yOffset += 10;

    // Next Block
    window.drawString(colStart1, yOffset, "Next:      ");
    window.drawString(xOffset, yOffset, "Next:      ");
    yOffset += 10;


    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 4; ++j) {
            // Player 1 Next Block
            if (activePlayer == 1 || activePlayer == 0) {
                char c1 = subject1->getState(i + height, j);
                int color1 = determineColor2(c1, false, i);
                window.fillRectangle(colStart1 + j * blockScale + gap / 2, yOffset + i * blockScale + gap / 2,
                                    adjustedBlockScale, adjustedBlockScale, color1);
            }

            // Player 2 Next Block
            if (activePlayer == 2 || activePlayer == 0) {
                char c2 = subject2->getState(i + height, j);
                int color2 = determineColor2(c2, false, i);
                window.fillRectangle(xOffset + j * blockScale + gap / 2, yOffset + i * blockScale + gap / 2,
                                    adjustedBlockScale, adjustedBlockScale, color2);
            }
        }
    }
}

// int Graphics
// rerender  the position the block was in and the position the block moves to. 
void GraphicsObserver::reRenderPos() {
    // for (auto c: )

}




int GraphicsObserver::determineColor2(char c, bool isBlind, int y) {
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
    else if (y < 3) return Xwindow::LightGray;   // if the cell is empty and in the reserve rows
    return Xwindow::WhiteSmoke; // otherwise, the cell is empty and in the playable rows
}

int GraphicsObserver::determineColor(char c) {
    if (c == 'B') return Xwindow::Blind; // Blind color
    else if (c == 'I') return Xwindow::Cyan;       // 4
    else if (c == 'O') return Xwindow::Yellow; // 5
    else if (c == 'L') return Xwindow::Orange; // 8
    else if (c == 'J') return Xwindow::Blue;   // 7
    else if (c == 'T') return Xwindow::Purple; // 6
    else if (c == 'S') return Xwindow::Green;  // 3
    else if (c == 'Z') return Xwindow::Red;    // 2
    else if (c == '*') return Xwindow::Brown;   // 9
    else if (c == ',') return Xwindow::LightGray;   // if the cell is empty and in the reserve rows
    return Xwindow::WhiteSmoke; // otherwise, the cell is empty and in the playable rows
}


void GraphicsObserver::printTopBoundary() {
    window.drawString(colStart1, rowStart - 20, "Top Boundary");
}
