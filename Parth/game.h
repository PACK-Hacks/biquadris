#ifndef __GAME__
#define __GAME__

class Game {
    Player p1;
    Player p2;

    public:
    Game(bool text, int seed, string scriptfile1, string scriptfile2, int startlevel);
    
    // Remember to onstruct players with next block in player constructor

    string runGame() {}

};

#endif