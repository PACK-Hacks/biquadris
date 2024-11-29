#include "graphicsobserver.h"

// Graphics Observer Constructor
GraphicsObserver::GraphicsObserver(GameDisplay* subject1, GameDisplay* subject2)
    :subject1{subject1}, subject2{subject2}, active{active}, nextBlockDock{subject1->getNextBlockDock()},
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
    // // Checking for blindness
    // bool player1Blind = blind_status == 1;
    // bool player2Blind = blind_status == 2;

    // // Check whether the display still has lingering black squares from previous blind
    // bool player1AlreadyBlind = player1Blind && subject1->getWasBlind();
    // bool player2AlreadyBlind = player1Blind && subject2->getWasBlind();


    int xOffset = colStart2;
    int yOffset = rowStart - 30;

    int gap = 2; // Gap between cells
    int adjustedBlockScale = blockScale - gap; // Adjusted size of each cell

    // Clear window
    // window.fillRectangle(0, 0, window.getWidth(), window.getHeight(), 0); // Clear entire screen to background color (white)

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

        // Horizontal grid
        // for (int i = 0; i < width; ++i) {
        //     if (i < width - 1) { 
        //             window.fillRectangle(colStart1 + (i + 1) * blockScale,
        //                                 yOffset,
        //                                 2, 
        //                                 height * 20,
        //                                 Xwindow::Black);
        //     }
        // }
        // // Vertical grid
        // for (int i = 1; i < height; ++i) {
        //     if (i < height ) {
        //             window.fillRectangle(width,
        //                                 yOffset + i * blockScale + gap / 2, 
        //                                 width * 20, 
        //                                 2, 
        //                                 Xwindow::Black);
        //     }
        // }

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

    if (blind_status) {
        playerWasBlind[blind_status - 1] = true;
    }

    if (blind_status == 2) {
        cout << "Player 2 is blind" << endl;
    }
    else if (playerWasBlind[activePlayer - 1]) {
        cout << "Player 2 was blind" << endl;
    }
    else if (activePlayer == 2) {
        cout << "Player 2 has not been blinded" << endl;
    }


    if (blind_status == 2) {
        for (int i = 3; i < 12; ++i) {
            for (int j = 2; j < 9; ++j) {
                window.fillRectangle(xOffset + j * blockScale + gap / 2, yOffset + i * blockScale + gap / 2,
                                    adjustedBlockScale, adjustedBlockScale, Xwindow::Blind);
            }
        }
    }
    else if (playerWasBlind[activePlayer - 1]) {
        for (int i = 3; i < 12; ++i) {
            for (int j = 2; j < 9; ++j) {
                char c2 = subject1->getState(i, j);
                int color2 = determineColor(c2, blind_status == 2 && i >= 3 && i <= 11 && j >= 2 && j <= 8, i);
                window.fillRectangle(xOffset + j * blockScale + gap / 2, yOffset + i * blockScale + gap / 2,
                                    adjustedBlockScale, adjustedBlockScale, color2);
            }
        }
    }

    
    set<pair<int,int>> rerenderedCoordinates; 

    if (activePlayer == 0) {
        // for (int i = 0; i < height; ++i) {
        //     // window.fillRectangle(colStart1, yOffset + i * blockScale, 
        //     //     adjustedBlockScale, adjustedBlockScale, 1);

        //     for (int j = 0; j < width; ++j) {
        //         int initColor;
        //         if (i < 3) initColor = 12; // NonPlayable Board
        //         if (i >=3) initColor = 11;   // Playable Board


        //         window.fillRectangle(colStart1 + j * blockScale + gap / 2, yOffset + i * blockScale + gap / 2,
        //                             adjustedBlockScale, adjustedBlockScale, 12);
                
        //         window.fillRectangle(xOffset + j * blockScale + gap / 2, yOffset + i * blockScale + gap / 2,
        //                             adjustedBlockScale, adjustedBlockScale, 12);
                
 

        //         // // Draw the gap (horizontal and vertical rectangles)
        //         // if (j < width - 1) { // Horizontal gap
        //         //     window.fillRectangle(colStart1 + (j + 1) * blockScale, 
        //         //                         yOffset + i * blockScale + gap / 2, 
        //         //                         gap, 
        //         //                         adjustedBlockScale, 
        //         //                         Xwindow::Black);
        //         // }
        //         // if (i < height - 1) { // Vertical gap
        //         //     window.fillRectangle(colStart1 + j * blockScale + gap / 2, 
        //         //                         yOffset + (i + 1) * blockScale, 
        //         //                         adjustedBlockScale, 
        //         //                         gap, 
        //         //                         Xwindow::Black);
        //         // }
                
        //         // // Draw the gap (horizontal and vertical rectangles)
        //         // if (j < width - 1) { // Horizontal gap
        //         //     window.fillRectangle(xOffset + (j + 1) * blockScale, 
        //         //                         yOffset + i * blockScale + gap / 2, 
        //         //                         gap, 
        //         //                         adjustedBlockScale, 
        //         //                         Xwindow::Black);
        //         // }
        //         // if (i < height - 1) { // Vertical gap
        //         //     window.fillRectangle(xOffset + j * blockScale + gap / 2, 
        //         //                         yOffset + (i + 1) * blockScale, 
        //         //                         adjustedBlockScale, 
        //         //                         gap, 
        //         //                         Xwindow::Black);
        //         // }

        //     }
        // }
    }
    else if (activePlayer == 1) {
        rerenderedCoordinates = subject1->getMovedCells();
    }
    else if (activePlayer == 2) {
        rerenderedCoordinates = subject2->getMovedCells();
    }

    // Player Boards
    for (auto c: rerenderedCoordinates) {
        int j = c.first; // j = x
        int i = c.second; // i = y;

        // Player 1 Board
        if (activePlayer == 1 || activePlayer == 0){
            char c1 = subject1->getState(i, j);
            int color1 = determineColor(c1, blind_status == 1 && i >= 3 && i <= 11 && j >= 2 && j <= 8, i);            
        
            window.fillRectangle(colStart1 + j * blockScale + gap / 2, yOffset + i * blockScale + gap / 2,
                                    adjustedBlockScale, adjustedBlockScale, color1);
        }

        // Player 2 Board
        if (activePlayer == 2 || activePlayer == 0){
            char c2 = subject2->getState(i, j);
            int color2 = determineColor(c2, blind_status == 2 && i >= 3 && i <= 11 && j >= 2 && j <= 8, i);
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

    // for (auto c: nextBlockPixcels) {
    //     int i = c.first;
    //     int j = c.second;

    //     // Player 1 Next Block
    //     if (activePlayer == 1 || activePlayer == 0) {
    //         char c1 = subject1->getState(i + height, j);
    //         int color1 = determineColor(c1, false);
    //         window.fillRectangle(colStart1 + j * blockScale + gap / 2, yOffset + i * blockScale + gap / 2,
    //                              adjustedBlockScale, adjustedBlockScale, color1);
    //     }

    //     // Player 2 Next Block
    //     if (activePlayer == 2 || activePlayer == 0) {
    //         char c2 = subject2->getState(i + height, j);
    //         int color2 = determineColor(c2, false);
    //         window.fillRectangle(xOffset + j * blockScale + gap / 2, yOffset + i * blockScale + gap / 2,
    //                              adjustedBlockScale, adjustedBlockScale, color2);
    //     }
    // }


    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 4; ++j) {
            // Player 1 Next Block
            if (activePlayer == 1 || activePlayer == 0) {
                char c1 = subject1->getState(i + height, j);
                int color1 = determineColor(c1, false, i);
                window.fillRectangle(colStart1 + j * blockScale + gap / 2, yOffset + i * blockScale + gap / 2,
                                    adjustedBlockScale, adjustedBlockScale, color1);
            }

            // Player 2 Next Block
            if (activePlayer == 2 || activePlayer == 0) {
                char c2 = subject2->getState(i + height, j);
                int color2 = determineColor(c2, false, i);
                window.fillRectangle(xOffset + j * blockScale + gap / 2, yOffset + i * blockScale + gap / 2,
                                    adjustedBlockScale, adjustedBlockScale, color2);
            }
        }
    }

    if (activePlayer) {
        playerWasBlind[activePlayer - 1] = (bool) blind_status;
    }
}

// int Graphics
// rerender  the position the block was in and the position the block moves to. 
void GraphicsObserver::reRenderPos() {
    // for (auto c: )

}




int GraphicsObserver::determineColor(char c, bool isBlind, int y) {
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


void GraphicsObserver::printTopBoundary() {
    window.drawString(colStart1, rowStart - 20, "Top Boundary");
}
