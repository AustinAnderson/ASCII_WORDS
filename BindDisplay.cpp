#include "BindDisplay.h"

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
            if(mode==HIGHLIGHTED){
                open="{";
                close="}";
                color=BKGRND_GRN;
            }
            if(mode==SELECTED){
                open="(";
                close=")";
                color=BKGRND_YLW;
            }

            toReturn=color+toReturn;
            toReturn+=BKGRND_WHT;
            toReturn=open+toReturn;
            toReturn+=close;
        }
        return name+toReturn;
    }
