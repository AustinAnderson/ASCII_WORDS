#ifndef BOARD
#define BOARD
#include "globals.h"
#include "Tile.h"
class Board{
    public:
        Board();

        bool isTentative();

        void setTentative(bool newVal);

        void toggleSelecting();

        void up();

        void down();

        void left();

        void right();

        void updateCurrentTile(char letter);

        void clearCurrentTile();

        string clearAll();

        char getCurrentTile();

        vector<string> mat2Str();

        bool currentPlacementValid();

        //computes the sum of the tiles added
        //and returns the tentative string
        vector<string> computeSum();

        bool currentWordsValid();

        int checkAndCommit();

        friend ostream& operator<<(ostream& os,Board& b);
        friend istream& operator>>(istream& is,Board& b);
    private:
        set<string> dictionary;
        vector<vector<Tile> > mat;
        vector<list<pair<int, int> > > tentatives;
        int xNdx;
        int yNdx;
        int currentTentativeSum;

        vector<string> formatCurrent();
};

#endif//BOARD
