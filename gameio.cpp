#include "gameio.h"//GameIOController

//This
    void write(){
        interface
        //parse << of game stuff and write string based on player and game name file 
        //to the game name file
        //leaving a space for the other player's data

        return os;
    }
    istream& operator>>(ifstream& is,GameIOController& g){
        //convert readin string back to ready readable format
        //read in file and set all the 
        return is;
    }
 

//Player
    ostream& operator<<(ostream& os,Player& p){

        os<<p.board<<" ";
        os<<p.bag<<" ";
        os<<p.rack<<" ";
        return os;
    }
//Rack
    ostream& operator<<(ostream& os,Rack& r){
        for(int i=0;i<r.tiles.size();i++){
            os<<r.tiles[i]<<" ";
        }
        return os;
    }
//Scores
    ostream& operator<<(ostream& os,Scores& s){
        os<<s.p1<<" "<<s.p2<<" "<<s.committing<<" ";
        return os;
    }
    istream& operator>>(istream& is,Scores& s){
        is>>s.p1>>s.p2>>s.committing;
        return is;
    }
//TileBag
    ostream& operator<<(ostream& os,TileBag& tb){
        for(int i=0;i<27;i++){
            os<<tb.tilesLeft[i]<<" ";
        }
        return os;
    }
    istream& operator>>(istream& is,TileBag& tb){
        int let=0;
        for(int i=0;i<27;i++){
            is>>let;
            tb.tilesLeft[i]=let;
        }
        return is;
    }
//Tile
    ostream& operator<<(ostream& os,Tile& t){
        os<<t.letter<<" "<<t.tentative<<" "<<t.selecting<<" "<<t.modifier<<" ";
        return os;
    }
    istream& operator>>(istream& is,Tile& t){
        is>>t.letter>>t.tentative>>t.selecting>>t.modifier;
        return is;
    }
//Interface
    ostream& operator<<(ostream& os,Interface& game){
        os<<game.score;
        os<<game.guy;
        return os;
    }
//Board
    friend ostream& operator<<(ostream& os,Board& b){
        os<<b.mat.size()<<" "<<b.mat[0].size()<<" ";
        for(int i=0;i<b.mat.size();i++){
            for(int j=0;j<b.mat[0].size();j++){
                os<<b.mat[i][j]<<" ";
            }
        }
        os<<b.tentatives.size()<<" ";
        if(b.tentatives.size()>0){
            os<<b.tentatives[0].size()<<" ";
        }
        else{
            os<<0<<" ";
        }
        for(int i=0;i<b.tentatives.size();i++){
            for(list<pair<int,int> >::iterator j=b.tentatives[0].begin();j!=b.tentatives[0].end();j++){
                os<<j->first<<" "<<j->second<<" ";
            }
        }
        os<<b.xNdx<<" "<<b.yNdx<<" "<<b.currentTentativeSum<<" ";
        return os;
    }
    friend istream& operator>>(istream& is,Board& b){
        int maxi=0;
        int maxj=0;
        b.mat.clear();
        Tile held;
        vector<Tile> row;
        is>>maxi>>maxj;
        for(int i=0;i<maxi;i++){
            for(int j=0;j<maxj;j++){
                is>>held;
                row.push_back(held);
            }
            b.mat.push_back(row);
            row.clear();
        }//players have different tentatives, so this probably wont work
        b.tentatives.clear();
        int heldx; 
        int heldy;
        list<pair<int, int> > trow;
        is>>maxi>>maxj;
        for(int i=0;i<maxi;i++){
            for(int j=0;j<maxj;j++){
                is>>heldx>>heldy;
                trow.push_back(make_pair(heldx,heldy));
            }
            b.tentatives.push_back(trow);
            trow.clear();
        }
        is>>b.xNdx>>b.yNdx>>b.currentTentativeSum;
        return is;
    }
