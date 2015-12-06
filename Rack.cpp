#include "Rack.h"

//public:
    Rack::Rack(){
        vector<Tile> placeHolder(7);
        tiles=placeHolder;
        selecting=false;
        ndx=0;
        space="        ";
    }
            


    void Rack::setCurrentTile(char let){
        setTile(ndx,let);
    }
    void Rack::clearCurrentTile(){
        clearTile(ndx);
    }
    char Rack::getCurrentTile(){
        return tiles[ndx].getLetter();
    }
    int Rack::getNextBlankNdx(){
        int ndx=0;
        while(ndx<7&&tiles[ndx].getLetter()!=' '){
            ndx++;
        }
        if(ndx==7){
            ndx=-1;
        }
        return ndx;
    }
    bool Rack::isSelecting(){
        return selecting;
    }
    void Rack::toggleSelecting(){
        selecting=!selecting;
        tiles[ndx].toggleSelecting();
    }
    void Rack::up(){
        tiles[ndx].toggleSelecting();
        if(ndx>0){
            ndx--;
        }
        tiles[ndx].toggleSelecting();
    }
    void Rack::down(){
        tiles[ndx].toggleSelecting();
        if(ndx<tiles.size()-1){
            ndx++;
        }
        tiles[ndx].toggleSelecting();
    }
    vector<string> Rack::toString(){
        vector<string> out;
        out.push_back(space+" ____");
        string l1=space;
        for(int i=0;i<tiles.size();i++){
            if(selecting&&i==ndx){
                l1[l1.size()-1]='>';
            }
            l1+="|"+tiles[i].line1();
            out.push_back(l1);
            out.push_back(space+"|"+tiles[i].line2());
            l1=space;
        }
        
        return out;
    }
    
    void Rack::setTile(int ndx,char let){
        tiles[ndx].set(let,false,false);
    }
//private:
    void Rack::clearTile(int ndx){
        tiles[ndx].set(' ',false,false);
        tiles[ndx].setMod("__");
    }

    ostream& operator<<(ostream& os,Rack& r){
        for(int i=0;i<r.tiles.size();i++){
            os<<r.tiles[i]<<" ";
        }
        return os;
    }
    istream& operator>>(istream& is,Rack& r){
        for(int i=0;i<r.tiles.size();i++){
            is>>r.tiles[i];
        }
        return is;
    }
