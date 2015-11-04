#ifndef INTERFACE
#define INTERFACE
#include "globals.h"
#include "bottomDisplay.h"
#include "Player.h"
#include "Scores.h"
class Interface{
    public:
        Interface();

        void print();

        void play();

        friend ostream& operator<<(ostream& os,Interface& game){
            os<<game.score;
            os<<game.guy;
        }
    private:
        //void updateGame(){//////////////////////////////////////
        //    if(!true/*p1wordsp2.lck is found*/){
        //        //open gamefile
        //        gamefile>>*this;
        //    }
       // }
        string getInitialSize();

        string setScreenBack;

        bool player;//current player: true is this instance, false is other player's instance
        //if backspace
        
        void putTileBack();

        void chooseTile();

        void toggleSelecting();

        void up();

        void down();

        void left();

        void right();

        char char_up;
        char char_down;
        char char_left;
        char char_right;
        char char_submit;
        char char_enter;
        char char_back;
        char char_quit;

        bool choosingTile;
        Scores score;
        vector<string> message;
        Player guy;
        bottomDisplay bottom;

};

#endif//INTERFACE
