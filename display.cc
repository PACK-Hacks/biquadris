class Display {
    const int width = 11;
    const int height = 15;
    
    clear() {
        // track num of cleared rows
        score += calcScore(numCleared);
    }

    placed() {  // runs clearing code, and char conversion, turning the block state 
                // from moving to placed
        clear();    // check rows of each cell 1, 2, 3, 4, for each distinct row,
                    // check if it's clearable, make all cells on row nullptr use getCellAt,
                    // call fall with row and shift num
    }


    public:
        render();
        drop() {
            // move block down
            // once you hit the bottom
            placed();
        }

        right() {
            // move block right
            // if heavy, you hit the bottom
                //  placed();
        }

    // When a block is being moved, store its characters as '\', once it's placed  
    // turn it into the proper characters. Easier to check collisions.
    // charAt decrypts


};