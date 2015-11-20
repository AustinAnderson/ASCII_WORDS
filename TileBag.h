#ifndef TILEBAG
#define TILEBAG
#include "globals.h"
#include "Tile.h"
class TileBag{
    public:
        TileBag();

        //used for when two clients are active over multiplayer
        void update(TileBag other);

        //get the number of tiles
        //for the letter "key" that are left
        int getNumLeft(char key);

        bool isEmpty();
        /**
         * gets a letter for a new tile, and decrements the number of those
         * tiles available at the same time
         * returns the char to use, or ' ' if the bag is empty
         */
        char pullTile();

        friend ostream& operator<<(ostream& os,TileBag& tb);
        friend istream& operator>>(istream& is,TileBag& tb);
    private:
        //take advantage of the fact that alphabet in ascii
        //is contiguous from @toZ
        int tilesLeft[27];
        bool empty;
};

#endif//TILEBAG
