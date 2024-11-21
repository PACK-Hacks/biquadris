#include <string>
#include "player.cc"


class Game {
    Player p1;
    Player p2;

    public:
    Game(bool text, int seed, string scriptfile1, string scriptfile2, int startlevel): 
    p1{text, seed, scriptfile1, startlevel, this}, p2{text, seed, scriptfile2, startlevel, this} {}
    // Remember to onstruct players with next block in player constructor

    Player runGame() {
        string special;


        while (true) {
            special = p1.runTurn(special);
            if (p1.getLost() == true) return p2;
            special = p2.runTurn(special);
            if (p2.getLost() == true) return p1;
        }

        return p1;

    }

};