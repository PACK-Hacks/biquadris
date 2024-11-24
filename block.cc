#include "block.h"
#include "display.h"
void Block::clearBlockFromBoard() {
    for (int i = 6; i < 16; i++) {
        for (int j = 0; j < 11*2 + 10; j++) {
            board[i][j] = ' '; // needs fix
        }
    }
}
void Block::insertBlockFromBoard() {
    for
}
vector<Cell*> Block::getAllCells() {
    
}
void Block::clockwise() {

}
void Block::counterClockwise() {

}
