#ifndef RACK
#include "globals.h"
#include "Tile.h"
class Rack{
    
    public:
        Rack();

        void setCurrentTile(char let);

        void clearCurrentTile();

        char getCurrentTile();

        int getNextBlankNdx();

        bool isSelecting();

        void toggleSelecting();

        void up();

        void down();

        vector<string> toString();

        void setTile(int ndx,char let);

        friend ostream& operator<<(ostream& os,Rack& r);
    private:
        void clearTile(int ndx);
        string space;
        vector<Tile> tiles; 
        bool selecting;
        int ndx;

};

#define RACK
#endif//RACK
