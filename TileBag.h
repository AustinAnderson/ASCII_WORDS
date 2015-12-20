#ifndef TILEBAG
#define TILEBAG
#include "globals.h"
#include "Tile.h"
class TileBag{
    public:
        TileBag();

        //get the number of tiles
        //for the letter "key" that are left
        int getNumLeft(char key);

        bool isEmpty();

        Tile pullTile();

        friend ostream& operator<<(ostream& os,TileBag& tb);
        friend istream& operator>>(istream& is,TileBag& tb);
    private:
        Tile blank;
        vector<vector<Tile> > bag;
        bool empty;
};

#endif//TILEBAG
