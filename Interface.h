#ifndef INTERFACE
#define INTERFACE
#include "globals.h"
#include "bottomDisplay.h"
#include "Player.h"
#include "Scores.h"


class Interface{
    public:
        Interface(string bindPreferencesPath);

        void print();
        void play();

        friend ostream& operator<<(ostream& os,Interface& game);
        friend istream& operator>>(istream& is,Interface& game);
    private:

        vector<char> keyBindings;
        string setScreenBack;
        bool player;//current player: true is this instance, false is other player's instance
        //if backspace
        ofstream bindingPreferences;
        bool choosingTile;
        Scores score;
        vector<string> message;
        Player guy;
        bottomDisplay bottom;

        string getInitialSize();
        
        void putTileBack();

        void putAllBack();//resets the board to where it was after last submission

        void chooseTile();

        void toggleSelecting();

        void up();

        void down();

        void left();

        void right();


};

#endif//INTERFACE
