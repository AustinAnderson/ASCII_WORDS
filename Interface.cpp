#include "Interface.h"
//public:
    Interface::Interface(string bindPreferencesPath,bool playerOne,bool newGame){
        this->newGame=newGame;
        playerOnesTurn=true;//to be overwritten by >>
        this->playerOne=playerOne;
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
        keyBindings[DEFINE]='y';
        keyBindings[QUIT]='q';
        choosingTile=false;
        message.push_back("      @ is blank");
        message.push_back("         tile  ");
        message.push_back("             ");
        message.push_back("             ");
        message.push_back("       type the");
        message.push_back("       desired ");
        message.push_back("        letter ");
        message.push_back("");
        setScreenBack=getInitialSize();
        //set bindings from file
        ifstream readInBindings;
        readInBindings.open(bindPreferencesPath.c_str());
        if(readInBindings){
            for(int i=0;i<keyBindings.size();i++){
                //using .get to support mapping space and enter
                char next='\0';
                readInBindings.get(next);
                keyBindings[i]=next;
            }
            readInBindings.close();
        }
        else{
            string path=bindPreferencesPath;
            if(bindPreferencesPath==""){
                path="(none specified)";
            }
            cerr<<"WARNING: Unable to read saved key bindings"<<endl;
            cerr<<"         from "<<path<<endl;
            cerr<<"         Using defaults"<<endl;
            cerr<<"         Press any key to continue..."<<endl;
            while(!kbhit());
            getch();
        }
        bottom.init(&keyBindings,bindPreferencesPath);
    }
    void Interface::setOutputFile(string outPath){
        outputFilePath=outPath;
        checkSum=saveFileCheckSum();
    }
    void Interface::wrongTurnMessage(){
        system("clear");
        cout<<"It's not your turn!"<<endl;
        cout<<endl;
        cout<<"you can still plan out your next move,"<<endl;
        cout<<"but to play it, you'll need to exit the program,"<<endl;
        cout<<"and check back after player "<<(int)((playerOne)+1)<<" moves"<<endl;

        while(!kbhit());
        getch();
        putAllBack();
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
    bool Interface::isPlayerOnesTurn(){
        return playerOnesTurn;
    }
    void Interface::play(){//r  c
        system("resize -s 44 100");
        //here and not constructor to allow this to fire after
        //board is read in
        guy.refilTiles();
        cout<<BKGRND_WHT;
        system("clear");
        print();
        system("clear");
        print();
        bool done=false;
        while(!done){
            char pressed='\0';
            if(kbhit()){
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
                    submit();
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
                else if(pressed==keyBindings[DEFINE]){
                    defineWord();
                }
                else if(pressed==keyBindings[QUIT]){
                    putAllBack();
                    if(playerOnesTurn!=playerOne){
                        writeGame();
                    }
                    done=true;
                }
            }
        }
        system(setScreenBack.c_str());
        cout<<TXTCLRRST<<endl;
        system("clear");
    }
    void Interface::submit(){
        system("clear");
        if(playerOnesTurn==playerOne){
            score.toggleCommitting();
            print();//use kbhit instead of cin, allows us to
            while(!kbhit());//block until answered, but not depend on enter key
            char pressed=getch();
            if(pressed=='y'||pressed=='Y'){
                int newScore=guy.board.checkAndCommit(); 
                if(newScore>0){
                    score.add(playerOnesTurn,newScore);
                    playerOnesTurn=!playerOnesTurn;
                    guy.refilTiles();
                }
            }
            score.toggleCommitting();
        }
        else{
            wrongTurnMessage();
        }
        system("clear");
        print();

    }
    void Interface::defineWord(){
        string lastWord=guy.board.getLastWord();
        system("clear");
        cout<<lastWord<<endl;
        string command="curl -s ";
        command+="http://dictionary.reference.com/browse/";
        command+=lastWord;//search dictionary.com for the word
        command+=" |";
        command+="tr '\\n' ' '|";//remove the newlines
        command+="sed 's/<\\/div/@/g'|";//mark all the end div tags
        command+="tr @ '\\n'|";//insert newlines for each tag

        //get all the lines that are part of the div set
        command+="grep '<div class=\"def-set\"'|";

        command+="sed 's/<[^b][^>]*>//g'|";//remove all tags

        //word wrap at the 80 char mark
        command+="sed 's/\\(\\(.\\)\\{80\\}[^ ]*\\)/\\1@/g'|";

        command+="sed 's/\\(      [^ ]*\\)/\\1@/g'|";//format the
        command+="\\tr @ '\\n'";//word type on its own line
        system(command.c_str());
        cout<<endl;
        cout<<"press any key to return to the game"<<endl;
        while(!kbhit());
        getch();
        system("clear");
        print();

    }
    int Interface::saveFileCheckSum(){
        int checksum=-1;
        ifstream in;
        in.open(outputFilePath.c_str(),ios::binary);
        if(in){
            checksum++;
            in.seekg(0,in.end);
            int length=in.tellg();
            in.seekg(0,in.beg);
            char buffer[length];
            in.read(buffer,length);
            for(int i=0;i<length;i++){
                checksum+=int(buffer[i]);
            }
            in.close();
        }
        return checksum;
    }
    void Interface::writeGame(){
        //check newgame file not existing here
        if(newGame){
            ifstream checkExists;
            checkExists.open(outputFilePath.c_str());
            if(checkExists){
                cerr<<"Error: save file already exists"<<endl;
                cerr<<"       file name \""<<outputFilePath<<"\""<<endl;
                cerr<<"       starting a new game requires the "<<endl;
                cerr<<"       previous save file to not exist"<<endl;
                checkExists.close();
                exit(1);
            }
        }
        ///check checksum here
        int secondCheck=saveFileCheckSum();
        if(checkSum!=secondCheck){
            cerr<<"Error: the contents of save file"<<endl;
            cerr<<"       file name \""<<outputFilePath<<"\""<<endl;
            cerr<<"       have changed since the program was started"<<endl;
            cerr<<"       the game cannot be saved"<<TXTCLRRST<<endl;
            cerr<<checkSum<<" "<<secondCheck<<endl;
            exit(2);
        }

        ///check able to open file and write here
        ofstream writeOut;
        writeOut.open(outputFilePath.c_str());
        if(!writeOut){
            cerr<<"WARNING: could not open output"<<endl;
            cerr<<"         file: \""<<outputFilePath<<"\""<<endl;
            cerr<<"         game changes won't be saved"<<endl;
            cerr<<endl;
            cerr<<"         press any key to continue"<<endl;
            while(!kbhit());
            getch();
        }
        writeOut<<*this<<endl;
        writeOut.close();
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
        else if('@'==guy.board.getCurrentTile()){
            /* right now, the game is implemented where a movement of a tile is
             * simulated by the character for the tile on the board or rack
             * being erased and then written over, then the tile looking up it's
             * own new point value. this works ok if the character is the only
             * state information that needs to be saved, as was the case before
             * trying to add blank tiles, but doesn't work with the blank tile,
             * because it needs to have one letter, and remember it is actually
             * a blank tile even when it is moved.

             * a solution to this problem would be to have the tiles as logical
             * units and only move the pointer to the tile between the board and
             * rack and tile bag, but this would require a major rewrite of most
             * of the code. thinking the better route at this point would be to
             * just have movements of tile also hold blank tile bool
             */
            //visual que here
            char in='\0';
            while(!kbhit());
            in=getch();
            if(in>='a'){
                in=char(int(in)-int('a')+int('A'));
            }
            guy.board.updateCurrentTile(in);
            if(guy.board.getCurrentTile()==' '){
                while(!kbhit());
                getch();
                guy.board.updateCurrentTile('@');
            }
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
    ostream& operator<<(ostream& os,Interface& game){
        os<<game.playerOnesTurn<<" ";//the turn
        os<<game.score<<" ";//the score
        os<<game.guy<<" ";//the class with the board and rack and bag
        return os;
    }
    istream& operator>>(istream& is,Interface& game){
        is>>game.playerOnesTurn;
        is>>game.score;
        is>>game.guy;
        return is;
    }
