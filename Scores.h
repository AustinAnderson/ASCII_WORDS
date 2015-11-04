#ifndef SCORES
#define SCORES
#include "globals.h"
class Scores{
    public:
        Scores();

        Scores(int newP1,int newP2);

        void set(int np1,int np2,bool ncommitting=false);

        void add(bool p,int gain);

        void toggleCommitting();

        void print();

        friend ostream& operator<<(ostream& os,Scores& s){
            os<<s.p1<<" "<<s.p2<<" "<<s.committing<<" ";
            return os;
        }
        friend istream& operator>>(istream& is,Scores& s){
            is>>s.p1>>s.p2>>s.committing;
            return is;
        }
    private:
        string points2Str(int points);

        int p1;
        int p2;
        bool committing;
};

#endif
