/******************************************************
* Filename:       asciiWords.cpp
* Author:         Austin Anderson
* Date Created:   2015-02-20
* Description:    ascii version of words with friends
* 
******************************************************/

#include "Interface.h"

int main(int argc, char** argv){
    string keyBindingsPath="";
    bool newGame=false;
    //thought about using getopt, but I'm not that good with it,
    //plus it's a hassle for only one flag
    if((argc==5||argc==4)&&argv[1][0]=='-'&&argv[1][1]=='n'){//short circuts if
        newGame=true;                                        //[1][0]=='\0', so
        for(int i=1;i<argc-1;i++){                  //safe to dereference [1][1]
            argv[i]=argv[i+1];
        }
        argc--;
    }

    if(argc!=4){
        if(argc!=3){
            cerr<<"Usage: "<<argv[0]<<" <player number> <game file> [key binding file]"<<endl;
            cerr<<"               or, for a new game"<<endl;
            cerr<<"       "<<argv[0]<<" -n 1 <game file> [key binding file]"<<endl;
            exit(1);
        }
    }
    else{
        keyBindingsPath=argv[3];
    }
    char* error;
    int playerNumber=(int) strtol(argv[1],&error,10);
    if(*error!='\0'||(newGame&&playerNumber!=1)||(!newGame&&(playerNumber!=1&&playerNumber!=2))){
        string user="       ";
        user+=argv[0];
        if(newGame){
            user+=" -n";//for the display string, add back in the -n that was deleted
            cerr<<"Error: player number must be 1 for a new game"<<endl;
        }
        else{
            cerr<<"Error: player number must be 1 or 2"<<endl;
        }
        string location(user.size()+1,' ');
        location+="^";
        user+=" ";
        user+=argv[1];
        user+=" ";
        user+=argv[2];
        user+=" ";
        user+=keyBindingsPath;//this is used to work in either case
        cerr<<user<<endl;
        cerr<<location<<endl;
        exit(2);
    }
    // {1,2}-1
    // {0,1} but true for player 1, so
    //!{0,1}
    // {1,0} all good
    bool player=!(playerNumber-1);//true player1 false player 2

    Interface interface(keyBindingsPath,player,newGame);
    string gameFile=argv[2];
    ifstream in;
    in.open(gameFile.c_str());
    if(!newGame){//if its not a new game 
        if(!in){
            cerr<<"Error: unable to open game file"<<endl;
            cerr<<"       file name \""<<gameFile<<"\""<<endl;
            cerr<<"       check the file path and try again"<<endl;
            exit(3);
        }
        in>>interface;
    }
    else{
        if(in){
            cerr<<"Error: save file already exists"<<endl;
            cerr<<"       file name \""<<gameFile<<"\""<<endl;
            cerr<<"       starting a new game requires you to delete"<<endl;
            cerr<<"       the previous save file before starting"<<endl;
            in.close();
            exit(1);
        }
    }
    interface.setOutputFile(gameFile);
    if(player!=interface.isPlayerOnesTurn()){
        cout<<"player "<<int((player))+1<<" hasn't moved yet"<<endl;
        cout<<"wait for them to move before playing"<<endl;
    }
    else{
        interface.play();
    }
    return 0;
}
