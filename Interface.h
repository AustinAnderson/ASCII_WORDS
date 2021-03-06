#ifndef INTERFACE
#define INTERFACE
#include "globals.h"
#include "bottomDisplay.h"
#include "Player.h"
#include "Scores.h"


class Interface{
    public:
        Interface(string bindPreferencesPath,bool isPlayerOne,bool newGame);

        void print();
        void play();

        bool isPlayerOnesTurn();

        void setOutputFile(string outPath);

        friend ostream& operator<<(ostream& os,Interface& game);
        friend istream& operator>>(istream& is,Interface& game);
    private:

        bool newGame;

        int checkSum;

        vector<char> keyBindings;
        string setScreenBack;

        //this is the player number of this instance
        //doesn't change after constructor is called
        bool playerOne;

        bool playerOnesTurn;//current player's turn: true is p1, false for p2
        bool choosingTile;
        Scores score;
        vector<string> blankTileMessage;
        Player guy;
        bottomDisplay bottom;
        string outputFilePath;

        int saveFileCheckSum();

        void wrongTurnMessage();

        void writeGame();

        void setBlankTileMessage(bool highlight);

        void defineWord();

        void setBlank();

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
