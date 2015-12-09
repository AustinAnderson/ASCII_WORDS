#include "bottomDisplay.h"
#include "BindDisplay.h"
//public:
    void bottomDisplay::init(vector<char>* initialBindings,string writePreferencesTo){
        bindPreferencesPath=writePreferencesTo;
        xNdx=0;
        yNdx=0;
        keyBindings=initialBindings;
        contentMat=vector<vector<BindDisplay> >(3,vector<BindDisplay>(4));
        contentMat[0][0].setName("\n  edit keys: ");
        contentMat[0][0].setBound((*keyBindings)[REBIND]);
        contentMat[0][1].setName("           define last word: ");
        contentMat[0][1].setBound((*keyBindings)[DEFINE]);
        contentMat[0][2].setName("   quit: ");
        contentMat[0][2].setBound((*keyBindings)[QUIT]);
        contentMat[1][0].setName("\n         up: ");
        contentMat[1][0].setBound((*keyBindings)[UP]);
        contentMat[1][1].setName(" down: ");
        contentMat[1][1].setBound((*keyBindings)[DOWN]);
        contentMat[1][2].setName("         left: ");
        contentMat[1][2].setBound((*keyBindings)[LEFT]);
        contentMat[1][3].setName("  right: ");
        contentMat[1][3].setBound((*keyBindings)[RIGHT]);
        contentMat[2][0].setName("\n    confirm: ");
        contentMat[2][0].setBound((*keyBindings)[CONFIRM]);
        contentMat[2][1].setName(" back: ");
        contentMat[2][1].setBound((*keyBindings)[BACK]);
        contentMat[2][2].setName("  clear tiles: ");
        contentMat[2][2].setBound((*keyBindings)[CLEAR]);
        contentMat[2][3].setName(" submit: ");
        contentMat[2][3].setBound((*keyBindings)[SUBMIT]);

        headerDefault="\n";
        headerDefault+="                                key bindings:";

        headerHighlighted="\n";
        headerHighlighted+="                 select key to remap with current direction keys\n";
        headerHighlighted+="                         then press confirm to remap\n\n";
        headerHighlighted+="                       press back to return to game\n\n";
        headerHighlighted+="                     press submit to save preferences\n";

        headerError="\n";
        headerError+="                                Can't map key\n\n";
        headerError+="                          Given key already mapped!!\n";
        headerError+="\n\n";
        headerError+="\n";

        mode=DEFAULT;
        header=headerDefault;
    }
    void bottomDisplay::rebind(){
        bool done=false;
        char input;
        contentMat[yNdx][xNdx].setMode(HIGHLIGHTED);
        header=headerHighlighted;
        repaint();
        while(!done){
            input='\0';
            if(kbhit()){
                input=getch();
            }
            if(input==(*keyBindings)[UP]){
                contentMat[yNdx][xNdx].setMode(DEFAULT);
                if(yNdx==1){        // *   * * null
                    if(xNdx<2){     // |\  | |
                        xNdx=0;     // * *|* *
                    }
                    else{
                        xNdx--;
                    }
                }
                if(yNdx>0){
                    yNdx--;
                }
                contentMat[yNdx][xNdx].setMode(HIGHLIGHTED);
                repaint();
            }
            else if(input==(*keyBindings)[DOWN]){
                contentMat[yNdx][xNdx].setMode(DEFAULT);
                if(yNdx==0&&xNdx==1){    //* ** null
                    yNdx=1;              //  |
                    xNdx=2;              //****
                }
                else if(yNdx==0&&xNdx==2){    //* ** null
                    yNdx=1;                   //   |
                    xNdx=3;                   //****
                }
                else if(yNdx<(contentMat.size()-1)){
                    yNdx++;
                }
                contentMat[yNdx][xNdx].setMode(HIGHLIGHTED);
                repaint();
            }
            else if(input==(*keyBindings)[LEFT]){
                contentMat[yNdx][xNdx].setMode(DEFAULT);
                if(xNdx>0){
                    xNdx--;
                }
                contentMat[yNdx][xNdx].setMode(HIGHLIGHTED);
                repaint();
            }
            else if(input==(*keyBindings)[RIGHT]){
                contentMat[yNdx][xNdx].setMode(DEFAULT);
                bool valid=false;
                if(yNdx==0){
                    if(xNdx<2){
                        valid=true;
                    }
                }
                else{
                    if(xNdx<(contentMat[0].size()-1)){
                        valid=true;
                    }
                }
                if(valid){
                    xNdx++;
                }
                contentMat[yNdx][xNdx].setMode(HIGHLIGHTED);
                repaint();
            }
            else if(input==(*keyBindings)[CONFIRM]){//mapping two to same mixes them up make not doable
                header=generateHeaderSelected();
                contentMat[yNdx][xNdx].setMode(SELECTED);
                repaint();
                while(!kbhit());//wait for input
                char newKey=getch();

                BindDisplay* getAlreadyMapped=checkAlreadyMapped(newKey);
                if(newKey!=(*keyBindings)[BACK]){
                    if(getAlreadyMapped!=NULL){
                        getAlreadyMapped->setMode(ERROR);
                        header=headerError;
                        repaint();
                        while(!kbhit());
                        getch();//eat that input so it won't break the next loop
                        getAlreadyMapped->setMode(DEFAULT);
                    }
                    else{
                        setBinding(getKeyNdx(contentMat[yNdx][xNdx].getBound()),newKey);
                        contentMat[yNdx][xNdx].setBound(newKey);
                    }
                }
                contentMat[yNdx][xNdx].setMode(HIGHLIGHTED);
                header=headerHighlighted;
                repaint();
            }
            else if(input==(*keyBindings)[BACK]){
                header=headerDefault;
                contentMat[yNdx][xNdx].setMode(DEFAULT);
                done=true;
            }
            else if(input==(*keyBindings)[SUBMIT]){
                savePreferences();
            }
            else if(input==(*keyBindings)[QUIT]){
                header=headerDefault;
                contentMat[yNdx][xNdx].setMode(DEFAULT);
                done=true;
            }
        }
        header=headerDefault;
    }
    string bottomDisplay::print(){
        string toReturn=header;
        for(int i=0;i<contentMat.size();i++){
            for(int j=0;j<contentMat[0].size();j++){
                toReturn+=contentMat[i][j].print();
            }
        }
        return toReturn;
    }
//private:
    void bottomDisplay::savePreferences(){
        ofstream write;
        write.open(bindPreferencesPath.c_str());
        string filePath=bindPreferencesPath;
        if(bindPreferencesPath==""){
            filePath="(none specified)";
        }
        if(!write||bindPreferencesPath==""){
            cerr<<endl;
            cerr<<"WARNING: Unable to find target file "<<filePath<<endl;
            cerr<<"         Keybindings won't be saved."<<endl;
            cerr<<"         Press any key to continue..."<<endl;
            while(!kbhit());
            getch();
        }
        else{
            for(int i=0;i<keyBindings->size();i++){
            //needs to be spaceless for read in to work
                write<<(*keyBindings)[i];
            }
            write.close();
            cout<<"preferences saved"<<endl;
        }
    }
    void bottomDisplay::repaint(){
        system("clear");
        cout<<print()<<endl;
    }
    void bottomDisplay::setBinding(int key,char keyChar){
        if(!(key<0||key>=NUM_BOUND_KEYS)){
            (*keyBindings)[key]=keyChar;
        }
    }
    BindDisplay* bottomDisplay::checkAlreadyMapped(char input){
        BindDisplay* toReturn=NULL;
        for(int i=0;i<contentMat.size();i++){
            for(int j=0;j<contentMat[0].size();j++){
                if((i==0&&j<2)||i!=0){//fix jagged matrix seg fault
                    if(contentMat[i][j].getBound()==input){
                        toReturn=&contentMat[i][j];
                    }
                }
            }
        }
        return toReturn;
    }
    string bottomDisplay::generateHeaderSelected(){
        string toReturn="\n";
        toReturn+="                      press desired button for ";
        toReturn+=getKeyName(contentMat[yNdx][xNdx].getBound());
        toReturn+="\n\n\n";
        toReturn+="                     press back to return selection\n\n\n";
        return toReturn;
    }

    int bottomDisplay::getKeyNdx(char key){
        bool found=false;
        int i=0;
        for(;i<NUM_BOUND_KEYS&&!found;i++){
            if((*keyBindings)[i]==key){
                found=true;
            }
        }
        if(i==NUM_BOUND_KEYS+1){
            i=0;
        }
        return i-1;
    }
    string bottomDisplay::getKeyName(char key){
        return KeyNames[getKeyNdx(key)];
    }

/*
    ostream& operator<<(ostream& os,bottomDisplay& bottom){
        for(int i=0;i<bottom.keyBindings->size();i++){
            os<<(*(bottom.keyBindings))[i];
        }
        return os;
    }
*/
