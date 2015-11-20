#include "Interface.h"
//public:
    Interface::Interface(){
        player=true;
        keyBindings=vector<char>(NUM_BOUND_KEYS);
        keyBindings[UP]='i';
        keyBindings[DOWN]='k';
        keyBindings[LEFT]='j';
        keyBindings[RIGHT]='l';
        keyBindings[CONFIRM]='f';
        keyBindings[SUBMIT]='\n';
        keyBindings[BACK]='d';
        keyBindings[CLEAR]='c';
        keyBindings[REBIND]='b';
        keyBindings[QUIT]='q';
        bottom.init(&keyBindings);
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
        cout<<bottom.print()<<endl;
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
                pressed=getch();
                if(pressed==keyBindings[UP]){
                    up();
                }
                else if(pressed==keyBindings[DOWN]){
                    down();
                }
                else if(pressed==keyBindings[LEFT]){
                    left();
                }
                else if(pressed==keyBindings[RIGHT]){
                    right();
                }
                else if(pressed==keyBindings[SUBMIT]){
                    system("clear");
                    if(player){
                        score.toggleCommitting();
                        print();//use kbhit instead of cin, allows us to
                        while(!kbhit());//block until answered, but not depend on enter key
                        pressed=getch();
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
                else if(pressed==keyBindings[CONFIRM]){
                    if(!choosingTile){
                        toggleSelecting();
                    }
                    else{
                        chooseTile();
                    }
                }
                else if(pressed==keyBindings[BACK]){
                    if(choosingTile){
                        toggleSelecting();
                    }
                    else{
                        putTileBack();
                    }
                }
                else if(pressed==keyBindings[CLEAR]){
                    putAllBack();
                }
                else if(pressed==keyBindings[REBIND]){
                    bottom.rebind();//takes over control with similar structure
                    system("clear");
                    print();
                }
                else if(pressed==keyBindings[QUIT]){
                    done=true;
                }
            }
        }
        system(setScreenBack.c_str());
        cout<<TXTCLRRST<<endl;
        system("clear");
    }
//private:
    
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
    void Interface::putAllBack(){
        string tentatives=guy.board.clearAll();
        for(int i=0;i<tentatives.size();i++){
            int blankspot=guy.rack.getNextBlankNdx();
            if(blankspot!=-1){
                guy.rack.setTile(blankspot,tentatives[i]);
            }
        }
        guy.board.setTentative(false);
        system("clear");
        print();

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

