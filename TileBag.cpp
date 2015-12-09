#include "TileBag.h"
//public:
    TileBag::TileBag(){      //@ A B C D E  F G H I J K L M N O P Q R S T U V W X Y Z
        int initTilesLeft[27]={2,9,2,2,4,12,2,3,2,9,1,1,4,2,6,8,2,1,6,4,6,4,2,2,1,2,1};
        for(int i=0;i<27;i++){
            tilesLeft[i]=initTilesLeft[i];
        }
        srand(time(0));
        empty=false;
    }
    //used for when two clients are active over multiplayer
    void TileBag::update(TileBag other){
        bool newer=true;
        for(int i=0;i<27;i++){
            if(other.tilesLeft[i]>tilesLeft[i]){
                newer=false;
            }
        }
        if(newer){
            for(int i=0;i<27;i++){
                tilesLeft[i]=other.tilesLeft[i];
            }
        }
    }
    //get the number of tiles
    //for the letter "key" that are left
    int TileBag::getNumLeft(char key){
        if(validLetters.find(key)==string::npos||key==' '){
            cerr<<"in getNumLeft, invalid key, -"<<key<<"-"<<endl;
        }
        return tilesLeft[int(key)-int('@')];
    }
    bool TileBag::isEmpty(){
        return empty;
    }
    /**
     * gets a letter for a new tile, and decrements the number of those
     * tiles available at the same time
     * returns the char to use, or ' ' if the bag is empty
     */
    char TileBag::pullTile(){
        vector<char> tileList;
        char toReturn=' ';
        for(int i=0;i<27;i++){
            for(int j=0;j<tilesLeft[i];j++){
                tileList.push_back(char(i+int('@')));
            }
        }
        if(tileList.size()==0){
            empty=true;
        }
        else{
            int ndx=rand()%tileList.size();
            toReturn=tileList[ndx];
            tilesLeft[int(toReturn)-int('@')]--;//remove tile from bag
        }
        return toReturn;
    }
    ostream& operator<<(ostream& os,TileBag& tb){
        for(int i=0;i<27;i++){
            os<<tb.tilesLeft[i]<<" ";
        }
        return os;
    }
    istream& operator>>(istream& is,TileBag& tb){
        for(int i=0;i<27;i++){
            is>>tb.tilesLeft[i];
        }
        return is;
    }
