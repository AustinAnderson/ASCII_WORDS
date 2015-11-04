#include "Player.h"
//public:
    Player::Player(){
        int ndx=0;
        while((ndx=rack.getNextBlankNdx())!=-1){
            rack.setTile(ndx,bag.pullTile());
        }
    }
    vector<vector<string> > Player::toStrs(){
        vector<vector<string> > toReturn;
        toReturn.push_back(board.mat2Str());
        toReturn.push_back(rack.toString());
        return toReturn;
    }
    void Player::chooseTile(){
        char currentTile=rack.getCurrentTile();
        if(currentTile!=' '){
            //choose tile letter
            board.updateCurrentTile(currentTile);
            rack.clearCurrentTile();
        }
    }
    void Player::refilTiles(){
        int rndx=rack.getNextBlankNdx();
        while(rndx!=-1){
            rack.setTile(rndx,bag.pullTile());
            rndx=rack.getNextBlankNdx();
        }
    }
    void Player::replaceTile(){
        rack.setCurrentTile(bag.pullTile());
    }
