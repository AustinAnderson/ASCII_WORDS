#ifndef TILE
#define TILE
#include "globals.h"
class Tile{
    public:
        Tile();

        Tile(char let);

        Tile(bool sel,string mod);

        Tile& operator=(const Tile& rhs);
        char getLetter();

        int getPoints();

        string getMod();

        string getColor();
        
        string line1();

        string line2();

        void toggleSelecting();

        //is selecting is true if tile is |_| selector,
        //isTentative is true if the tile is part of a tentative move
        void set(char newLetter, bool isTentative=true,bool isSelecting=true);

        bool isTentative();

        void setTentative(bool newVal);

        void setLetter(char let);

        bool isBlank();

        //only to be called during construction of board
        void setMod(string newMod);

        friend ostream& operator<<(ostream& os,Tile& t);
        friend istream& operator>>(istream& is,Tile& t);
    private:
        string points2Str(int points);

        void setTop();

        void setMap();

        void setValidMods();
        map<char,int>* points;//only read, so just need one
        pair<string,string> previousState;
        vector<string> validModifiers;
        string top;
        
        char letter;
        bool tentative;
        bool selecting;
        bool blank;
        string modifier;
};
#endif
