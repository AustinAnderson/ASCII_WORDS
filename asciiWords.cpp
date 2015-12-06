/******************************************************
* Filename:       asciiWords.cpp
* Author:         Austin Anderson
* Date Created:  2015-02-20
* Description:    ascii version of words with friends
* 
******************************************************/

#include "Interface.h"

int main(int argc, char** argv){
    string keyBindingsPath="";
    if(argc>1){
        keyBindingsPath=argv[1];
    }
    Interface interface(keyBindingsPath);
    interface.play();
    return 0;
}
