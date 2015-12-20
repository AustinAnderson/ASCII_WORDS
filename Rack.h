#ifndef RACK
#include "globals.h"
#include "Tile.h"
class Rack{
    
    public:
        Rack();

        void setCurrentTile(Tile otherTile);

        void clearCurrentTile();

        Tile getCurrentTile();

        int getNextBlankNdx();

        bool isSelecting();

        void toggleSelecting();

        void up();

        void down();

        vector<string> toString();

        void setTile(int ndx,Tile tile);

        friend ostream& operator<<(ostream& os,Rack& r);
        friend istream& operator>>(istream& is,Rack& r);
    private:
        void clearTile(int ndx);
        Tile blank;//pass blank tiles by value to allow separate blanks
        string space;
        vector<Tile> tiles; 
        bool selecting;
        int ndx;

};

#define RACK
#endif//RACK
