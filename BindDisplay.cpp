#include "BindDisplay.h"

//holds a pairing between the button and the key it's mapped to
//as well as the current highlighting
//public:
    BindDisplay::BindDisplay(){
        name="";
        bound='\0';
        mode=DEFAULT;
    }
    void BindDisplay::setMode(int mode){
        this->mode=mode;
    }
    void BindDisplay::setName(string newName){
        name=newName;
    }
    void BindDisplay::setBound(char key){
        bound=key;
    }
    char BindDisplay::getBound(){
        return bound;
    }
    string BindDisplay::print(){
        string toReturn="";
        if(bound!='\0'){
            if(bound=='\n'){
                toReturn="ENTER";
            }
            else{
                toReturn="  ";
                toReturn+=bound;
                toReturn+="  ";
            }
            string open;
            string close;
            string color;
            if(mode==DEFAULT){
                open="(";
                close=")";
                color=BKGRND_WHT;
            }
            else if(mode==HIGHLIGHTED){
                open="{";
                close="}";
                color=BKGRND_GRN;
            }
            else if(mode==SELECTED){
                open="*";
                close="*";
                color=BKGRND_YLW;
            }
            else if(mode==ERROR){
                open="*";
                close="*";
                color=BKGRND_RED;
            }

            toReturn=color+toReturn;
            toReturn+=BKGRND_WHT;
            toReturn=open+toReturn;
            toReturn+=close;
        }
        return name+toReturn;
    }
