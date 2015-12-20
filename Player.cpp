#include "Player.h"
//public:
    Player::Player(){
        int ndx=0;
    }
    vector<vector<string> > Player::toStrs(){
        vector<vector<string> > toReturn;
        toReturn.push_back(board.mat2Str());
        toReturn.push_back(rack.toString());
        return toReturn;
    }
    void Player::chooseTile(){
        Tile currentTile=rack.getCurrentTile();
        if(currentTile.getLetter()!=' '){
            //choose tile letter
            currentTile.setTentative(true);
            currentTile.toggleSelecting();
            board.updateCurrentTile(currentTile);
            rack.clearCurrentTile();
        }
    }
    void Player::refilTiles(){
        int rndx=rack.getNextBlankNdx();
        while(rndx!=-1){
            rack.setTile(rndx,bag.pullTile());
            rndx=rack.getNextBlankNdx();
            cout<<"rndx "<<rndx<<endl;
        }
    }
    void Player::replaceTile(){
        rack.setCurrentTile(bag.pullTile());
    }

    ostream& operator<<(ostream& os,Player& p){
        os<<p.bag<<" ";
        os<<p.board<<" ";
        os<<p.rack<<" ";
        os<<p.otherPlayersRack<<" ";
        return os;
    }
    istream& operator>>(istream& is,Player& p){
        is>>p.bag;
        is>>p.board;
        is>>p.otherPlayersRack;
        is>>p.rack;
        return is;
    }
