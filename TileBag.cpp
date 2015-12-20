#include "TileBag.h"
//public:
    TileBag::TileBag(){      //@ A B C D E  F G H I J K L M N O P Q R S T U V W X Y Z
        int initTilesLeft[27]={2,9,2,2,4,12,2,3,2,9,1,1,4,2,6,8,2,1,6,4,6,4,2,2,1,2,1};
        vector<Tile> letterStack;
        for(int i=0;i<27;i++){
            for(int j=0;j<initTilesLeft[i];j++){
                Tile current(char(i+int('@')));
                letterStack.push_back(current);
            }
            bag.push_back(letterStack);
            letterStack.clear();
        }
        srand(time(0));
        empty=false;
    }
    //get the number of tiles
    //for the letter "key" that are left
    int TileBag::getNumLeft(char key){
        if(validLetters.find(key)==string::npos||key==' '){
            cerr<<"in getNumLeft, invalid key, -"<<key<<"-"<<endl;
            cerr<<"press anykey to continue"<<endl;
            while(!kbhit());
            getch();
        }
        return bag[int(key)-int('@')].size();
    }
    bool TileBag::isEmpty(){
        return empty;
    }
    Tile TileBag::pullTile(){
        Tile toReturn=blank;

        //set up a vector of pointers to vectors (used as stacks) of Tiles
        //that are non empty to choose from
        vector<vector<Tile>*> nonEmpty;
        for(int i=0;i<bag.size();i++){
            if(!bag[i].empty()){
                nonEmpty.push_back(&bag[i]);
            }
        }

        //get a letter index
        int ndx=rand()%nonEmpty.size();
        if(nonEmpty.empty()){//check if the bag is empty
            empty=true;
        }
        else{//if not empty
            toReturn=nonEmpty[ndx]->back();
            //cout<<toReturn.getLetter()<<endl;
            //cout<<bag[int(toReturn.getLetter())-int('@')].size()<<endl;
            nonEmpty[ndx]->pop_back();//set the tile to be returned and pop that tile's "stack"
            //cout<<bag[int(toReturn.getLetter())-int('@')].size()<<endl;
        }
        return toReturn;
    }
    ostream& operator<<(ostream& os,TileBag& tb){
        for(int i=0;i<27;i++){
            os<<tb.bag[i].size()<<" ";
            for(int j=0;j<tb.bag[i].size();j++){
                os<<tb.bag[i][j]<<" ";
            }
        }
        return os;
    }
    istream& operator>>(istream& is,TileBag& tb){
        for(int i=0;i<27;i++){
            int size=0;
            is>>size;
            tb.bag[i].clear();
            Tile in;
            for(int j=0;j<size;j++){
                is>>in;
                tb.bag[i].push_back(in);
            }
        }
        return is;
    }
