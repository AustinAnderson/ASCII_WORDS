#ifndef PLAYER
#define PLAYER
#include "globals.h"
#include "Board.h"
#include "TileBag.h"
#include "Rack.h"
class Player{
    public:
        Player();

        vector<vector<string> > toStrs();

        void chooseTile();

        void refilTiles();

        void replaceTile();

        friend class Interface;

        friend ostream& operator<<(ostream& os,Player& p){
            os<<p.board;
            os<<p.bag;
            os<<p.rack;
            return os;
        }
    private:
        Board board;
        TileBag bag;
        Rack rack;
};

#endif//PLAYER
