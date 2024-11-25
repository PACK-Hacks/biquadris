#include <iostream>
#include <algorithm> // For std::reverse
#include "display.h"

// Function to rotate a 4x4 matrix 

void insertCurrentBlock();
void removeCurrentBlock();
int WIDTH = 0;

int rotateClockwise(int matrix[4][4]) {
    // check boundaries first

    // Transpose the matrix
    // handle 'I' block

    removeCurrentBlock();


    int bottomLeftX = 0;
    int bottomLeftY = 0;

    // handle 'I' block
    if ( currentBlock->getAllCells() ) {
    // check if center is (width - 4) else invalid
        if (!(WIDTH - bottomLeftX >= 3)) {
            insertCurrentBlock();
            return false;
        }
        // transpose
        for (int i = bottomLeftY - 3; i <= bottomLeftY; i++) {

            for (int j = i; j < 4; j++) {
                std::swap(cell[i][j], matrix[j][i]);
            }
        }

        // Reverse each row
        for (int i = bottomLeftY - 3; i <= bottomLeftY; i++) {
            std::reverse(matrix[i], matrix[i] + 4);
        }
    }
    
    // handle 'O' block
    else if ( currentBlock->getAllCells() ) {
        insertCurrentBlock();
    }

    else {
        if (!(WIDTH - bottomLeftX >= 2)) {
            insertCurrentBlock();
            return false;
        }

        for (int i = bottomLeftY - 2; i <= bottomLeftY; i++) {
            for (int j = i; j < 3; j++) {
                std::swap(matrix[i][j], matrix[j][i]);
            }
        }

        // Reverse each row
        for (int i = bottomLeftY - 2; i <= bottomLeftY; i++) {
            std::reverse(matrix[i], matrix[i] + 3);
        }
    }
    return true;
}

// Function to print the matrix
void printMatrix(int matrix[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

int main() {
    // Example tetromino: 'L' shape
    int tetromino[4][4] = {
        {0, 0, 0, 0}, // Row 0
        {0, 0, 0, 0}, // Row 1
        {1, 0, 0, 0}, // Row 2
        {1, 1, 1, 0}  // Row 3
    };

    std::cout << "Original Tetromino:\n";
    printMatrix(tetromino);

    rotateClockwise(tetromino);

    std::cout << "\nRotated Tetromino:\n";
    printMatrix(tetromino);

    return 0;
}
