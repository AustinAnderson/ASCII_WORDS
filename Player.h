#ifndef PLAYER
#define PLAYER
#include "globals.h"
#include "Board.h"
#include "TileBag.h"
#include "Rack.h"
class Player{
    public:
        vector<vector<string> > toStrs();

        void chooseTile();

        void refilTiles();//all of them

        void replaceTile();//on the rack

        friend class Interface;

        friend ostream& operator<<(ostream& os,Player& p);
        friend istream& operator>>(istream& is,Player& p);

    private:
        Board board;
        TileBag bag;
        Rack rack;
        Rack otherPlayersRack;
};

#endif//PLAYER
