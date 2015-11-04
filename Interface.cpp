#include "Interface.h"
//public:
    Interface::Interface(){
        player=true;
        char_up='i';
        char_down='k';
        char_left='j';
        char_right='l';
        char_enter='f';
        char_submit='\n';
        char_back='d';
        char_quit='q';
        choosingTile=false;
        message.push_back("      @ is blank");
        message.push_back("         tile  ");
        message.push_back("             ");
        message.push_back("             ");
        message.push_back("       type the");
        message.push_back("       desired ");
        message.push_back("        letter ");
        message.push_back("");
        system("clear");
        print();
        setScreenBack=getInitialSize();
    }
    void Interface::print(){

        score.print();
        vector<vector<string> > boardRack=guy.toStrs();
        for(int i=0;i<boardRack[0].size();i++){
            cout<<boardRack[0][i];
            if(i>=5&&(i-5)<boardRack[1].size()){
                cout<<boardRack[1][i-5];
            }
            if(i>=(boardRack[0].size()-message.size())){
                cout<<message[i-(boardRack[0].size()-message.size())];
            }
            cout<<endl;
        }
        vector<string> bottomdisp=bottom.print();
        for(int i=0;i<bottomdisp.size();i++){
            cout<<bottomdisp[i]<<endl;
        }
    }
    void Interface::play(){//        r  c
        system("resize -s 44 100");
        cout<<BKGRND_WHT;
        system("clear");
        print();
        bool done=false;
        while(!done){
            char pressed='\0';
            if(kbhit()){
            //    updateGame();///////////////////////////////////////////////////////////////////
                pressed=getchar();
                if(pressed==char_up){
                    up();
                }
                else if(pressed==char_down){
                    down();
                }
                else if(pressed==char_left){
                    left();
                }
                else if(pressed==char_right){
                    right();
                }
                else if(pressed==char_submit){
                    system("clear");
                    if(player){
                        score.toggleCommitting();
                        print();//use kbhit instead of cin, allows us to
                        while(!kbhit()){}//block until answered, but not depend on enter key
                        pressed=getchar();
                        if(pressed=='y'||pressed=='Y'){
                            int newScore=guy.board.checkAndCommit(); 
                            if(newScore>0){
                                score.add(player,newScore);
                                player=!player;
                                guy.refilTiles();
                            }
                        }
                        score.toggleCommitting();
                    }
                    else{
                        cout<<"It's not your turn!"<<endl;
                        system("sleep .6");
                    }
                    system("clear");
                    print();
                }
                else if(pressed==char_enter){
                    if(!choosingTile){
                        toggleSelecting();
                    }
                    else{
                        chooseTile();
                    }
                }
                else if(pressed==char_back){
                    if(choosingTile){
                        toggleSelecting();
                    }
                    else{
                        putTileBack();
                    }
                }
                else if(pressed==char_quit){
                    done=true;
                }
            }
        }
        system(setScreenBack.c_str());
        cout<<TXTCLRRST<<endl;
        system("clear");
    }
//private:
    
    //void updateGame(){//////////////////////////////////////
    //    if(!true/*p1wordsp2.lck is found*/){
    //        //open gamefile
    //        gamefile>>*this;
    //    }
   // }
    string Interface::getInitialSize(){
        stringstream format;
        format<<"resize -s ";

        struct winsize w;//http://stackoverflow.com/questions/1022957/getting-terminal-width-in-c
        ioctl(0, TIOCGWINSZ, &w);//get the terminal size
        format<<w.ws_row<<" "<<w.ws_col;

        return format.str();
    }
    void Interface::putTileBack(){
        if(guy.board.isTentative()){
            int blankspot=guy.rack.getNextBlankNdx();
            if(blankspot!=-1){
                char putBack=guy.board.getCurrentTile();
                guy.board.clearCurrentTile();
                guy.rack.setTile(blankspot,putBack);
                guy.board.setTentative(false);
                system("clear");
                print();
            }

        }
    }
    void Interface::chooseTile(){
        toggleSelecting();
        guy.chooseTile();
        system("clear");
        print();
    }
    void Interface::toggleSelecting(){
        if(' '==guy.board.getCurrentTile()){
            choosingTile=!choosingTile;
            guy.rack.toggleSelecting();
            guy.board.toggleSelecting();
            system("clear");
            print();
        }
    }
    void Interface::up(){
        if(!choosingTile){
            guy.board.up();
        }
        else{
            guy.rack.up();
        }
        system("clear");
        print();
    }
    void Interface::down(){
        if(!choosingTile){
            guy.board.down();
        }
        else{
            guy.rack.down();
        }
        system("clear");
        print();
    }
    void Interface::left(){
        if(!choosingTile){
            guy.board.left();
        }
        system("clear");
        print();
    }
    void Interface::right(){
        if(!choosingTile){
            guy.board.right();
        }
        system("clear");
        print();
    }

