class Display {
    const int width = 11;
    const int height = 15;
    
    clear() {
        // track num of cleared rows
        score += calcScore(numCleared);
    }

    place() {  // runs clearing code, and char conversion, turning the block state 
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
            place();
        }

        // When a block is being moved, store its characters as '\', once it's placed  
        // turn it into the proper characters. Easier to check collisions.
        // charAt decrypts
        right() {
            clearBlockFromBoard()
            
            currentBlock.cell1->addX(1);
            currentBlock.cell2->addX(1);
            currentBlock.cell3->addX(1);
            currentBlock.cell4->addX(1);

            if (currentBlock.heavy) {
                currentBlock.cell1->addY(1);
                currentBlock.cell2->addY(1);
                currentBlock.cell3->addY(1);
                currentBlock.cell4->addY(1);
            }
            
            insertBlockFromBoard()
        }
        void moveNextToCurrent() {
            currentBlock = nextBlock;
        }

        void generateNextBlock(string special) {
            if (special == "") {
                nextBlock = level->makeBlock(file);     // ifstream initialized with file name in the constructor
            } 
            else if (special == "blind") {
                blind = true;
            }
            else if (special == "force") {
                // get the forced shape
                char forcedBlock;
                nextBlock = level->makeChosenBlock(block, shape);
            }

            // else {
            //     stringstream iss{special};
            //     string s;

            //     block = level->getBlock();
            //     heavy = level->getHeavy();
            //     dummy = level->getDummy();


            //     char forcedBlock;

            //     while (iss >> s) {
            //         if (s == "blind") {     // set nextBlind to false in drop method
            //             isBlind = true;
            //         }
            //         if (s == "force") {
            //             iss >> forcedBlock;
            //         } 
            //         if (s == "heavy") {
            //             heavy = true;
            //         }
            //     }
            // }
        }

    


};