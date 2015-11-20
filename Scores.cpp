#include "Scores.h"
//public
    Scores::Scores(){
        p1=0;
        p2=0;
        committing=false;
    }
    Scores::Scores(int newP1,int newP2){
        p1=newP1;
        p2=newP2;
        committing=false;
    }
    void Scores::set(int np1,int np2,bool ncommitting){
        p1=np1;
        p2=np2;
        committing=ncommitting;
    }
    void Scores::add(bool p,int gain){
        if(p){
            p1+=gain;
        }
        else{
            p2+=gain;
        }
    }
    void Scores::toggleCommitting(){
        committing=!committing;
    }
    void Scores::print(){
        if(!committing){
            cout<<" ________________                                         _________________ "<<endl;          
            cout<<"|                |                                       |                 |"<<endl;           
            cout<<"| player 1: "<<points2Str(p1)<<" |                                       |  player 2: "<<points2Str(p2)<<" |"<<endl;           
            cout<<"|________________|                                       |_________________|"<<endl;
        }
        else{
            cout<<" ________________                                         _________________   "<<endl;            
            cout<<"|                |         =======_______=======         |                 | "<<endl;             
            cout<<"| player 1: "<<points2Str(p1)<<" |          ) Play Move? Y/N (           |  player 2: "<<points2Str(p2)<<" | "<<endl;             
            cout<<"|________________|         /__====******====__\\          |_________________| "<<endl;              
        }
    }
//private:
    string Scores::points2Str(int points){
        stringstream formatter;
        formatter<<points;
        string toReturn=formatter.str();
        for(int i=0;i<(4-formatter.str().size());i++){
            if(i%2==0){
                toReturn=' '+toReturn;
            }
            else{
                toReturn+=' ';
            }
        }
        return toReturn;
    }


