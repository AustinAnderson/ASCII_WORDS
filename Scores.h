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

        void print(bool p);

        friend ostream& operator<<(ostream& os,Scores& s);
        friend istream& operator>>(istream& is,Scores& s);

    private:
        string points2Str(int points);

        int p1;
        int p2;
        bool committing;
};

#endif
