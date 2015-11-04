/******************************************************
* Filename:       asciiWords.cpp
* Author:         Austin Anderson
* Date Created:  2015-02-20
* Description:    ascii version of words with friends
* 
******************************************************/

#include "Interface.h"

int main(int argc, char** argv){

    Interface interface;
    interface.play();
    ofstream bob;
    bob.open("./testOut.txt");
    bob<<interface<<endl;
    bob.close();
    return 0;
}
