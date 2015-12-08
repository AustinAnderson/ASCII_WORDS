#ifndef INTERFACE
#define INTERFACE
#include "globals.h"
#include "bottomDisplay.h"
#include "Player.h"
#include "Scores.h"


class Interface{
    public:
        Interface(string bindPreferencesPath,bool isPlayerOne);

        void print();
        void play();

        bool isPlayerOnesTurn();

        void setOutputFile(string outPath);

        friend ostream& operator<<(ostream& os,Interface& game);
        friend istream& operator>>(istream& is,Interface& game);
    private:

        vector<char> keyBindings;
        string setScreenBack;

        //this is the player number of this instance
        //doesn't change after constructor is called
        bool playerOne;

        bool playerOnesTurn;//current player's turn: true is p1, false for p2
        bool choosingTile;
        Scores score;
        vector<string> message;
        Player guy;
        bottomDisplay bottom;
        string outputFilePath;

        void wrongTurnMessage();

        void writeGame();

        void defineWord();

        string getInitialSize();
        
        void putTileBack();

        void putAllBack();//resets the board to where it was after last submission

        void chooseTile();

        void toggleSelecting();

        void up();

        void down();

        void left();

        void right();

        void submit();


};

#endif//INTERFACE
