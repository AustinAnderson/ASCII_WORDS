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

        char getCurrentTile();

        vector<string> mat2Str();

        bool currentPlacementValid();

        //computes the sum of the tiles added
        //and returns the tentative string
        vector<string> computeSum();

        bool currentWordsValid();

        int checkAndCommit();

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
