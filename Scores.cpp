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
    void Scores::print(bool p){
        string hl1="";
        string hl2=BKGRND_BLU;
        if(p){
            hl1=hl2;
            hl2="";
        }
        if(!committing){
            cout<<" ________________                                         _________________ "<<endl;          
            cout<<hl1<<"|                |"<<BKGRND_WHT<<"                                       "<<hl2<<"|                 |"<<BKGRND_WHT<<endl;           
            cout<<hl1<<"| player 1: "<<points2Str(p1)<<" |"<<BKGRND_WHT<<"                                       "
                <<hl2<<"|  player 2: "<<points2Str(p2)<<" |"<<BKGRND_WHT<<endl;           
            cout<<hl1<<"|________________|"<<BKGRND_WHT<<"                                       "<<hl2<<"|_________________|"<<BKGRND_WHT<<endl;
        }
        else{
            cout<<" ________________                                         _________________   "<<endl;            
            cout<<hl1<<"|                |"<<BKGRND_WHT<<"         =======_______=======         "<<hl2<<"|                 | "<<BKGRND_WHT<<endl;             
            cout<<hl1<<"| player 1: "<<points2Str(p1)<<" |"<<BKGRND_WHT
                <<"          ) Play Move? Y/N (           "<<hl2<<"|  player 2: "<<points2Str(p2)<<" | "<<BKGRND_WHT<<endl;             
            cout<<hl1<<"|________________|"<<BKGRND_WHT<<"         /__====******====__\\          "<<hl2<<"|_________________| "<<BKGRND_WHT<<endl;              
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


    ostream& operator<<(ostream& os,Scores& s){
        os<<s.p1<<" "<<s.p2<<" "<<s.committing<<" ";
        return os;
    }
    istream& operator>>(istream& is,Scores& s){
        is>>s.p1>>s.p2>>s.committing;
        return is;
    }
