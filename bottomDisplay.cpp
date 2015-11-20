#include "bottomDisplay.h"
#include "BindDisplay.h"
//public:
    void bottomDisplay::init(vector<char>* initialBindings){
        xNdx=0;
        yNdx=0;
        keyBindings=initialBindings;
        contentMat=vector<vector<BindDisplay> >(3,vector<BindDisplay>(4));
        contentMat[0][0].setName("\n  edit keys: ");
        contentMat[0][0].setBound((*keyBindings)[REBIND]);
        contentMat[0][1].setName("                                       quit: ");
        contentMat[0][1].setBound((*keyBindings)[QUIT]);
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
                if(yNdx==1){        //*     * null null
                    if(xNdx>1){     // \   /
                        xNdx=1;     //* *|* *
                    }
                    else{
                        xNdx=0;
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
                if(yNdx==0&&xNdx==1){    //*  * null null
                    yNdx=1;              //  \|/
                    xNdx=3;              //****
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
                    if(xNdx==0){
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
                contentMat[yNdx][xNdx].setMode(HIGHLIGHTED);
                if(newKey!=(*keyBindings)[BACK]){
                    setBinding(getKeyNdx(contentMat[yNdx][xNdx].getBound()),newKey);
                    contentMat[yNdx][xNdx].setBound(newKey);
                }
                header=headerHighlighted;
                repaint();
            }
            else if(input==(*keyBindings)[BACK]){
                header=headerDefault;
                contentMat[yNdx][xNdx].setMode(DEFAULT);
                done=true;
            }
            else if(input==(*keyBindings)[QUIT]){
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
    void bottomDisplay::repaint(){
        system("clear");
        cout<<print()<<endl;
    }
    void bottomDisplay::setBinding(int key,char keyChar){
        if(!(key<0||key>=NUM_BOUND_KEYS)){
            (*keyBindings)[key]=keyChar;
        }
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
        return i-1;
    }
    string bottomDisplay::getKeyName(char key){
        return KeyNames[getKeyNdx(key)];
    }
