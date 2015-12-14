#include "Tile.h"
//public
    Tile::Tile(){
        setValidMods();
        setMap();
        set(' ',false,false);
        setMod("__");
    }
    Tile::Tile(bool sel,string mod){
        setValidMods();
        setMap();
        set(' ',false,sel);
        setMod(mod);
    }
    char Tile::getLetter(){
        return letter;
    }
    int Tile::getPoints(){
        return (*points)[letter];
    }
    string Tile::getMod(){
        return modifier;
    }
    string Tile::getColor(){
        string toReturn=BKGRND_YLW;
        if(letter==' '){
            if(modifier=="TL"){
                toReturn=BKGRND_GRN;
            }
            else if(modifier=="DL"){
                toReturn=BKGRND_BLU;
            }
            else if(modifier=="DW"){
                toReturn=BKGRND_RED;
            }
            else if(modifier=="TW"){
                toReturn=BKGRND_ORN;
            }
            else if(modifier=="_+"){
                toReturn=BKGRND_PRL;
            }
            else if(modifier=="__"){
                toReturn=BKGRND_WHT;
            }
        }
        return toReturn;
    }
    string Tile::line1(){
        return getColor()+top+BKGRND_WHT+"|";
    }
    string Tile::line2(){
        string toReturn=modifier+points2Str((*points)[letter]);
        return getColor()+toReturn+BKGRND_WHT+"|";
    }
    void Tile::toggleSelecting(){
        selecting=!selecting;
        setTop();
    }
    //is selecting is true if tile is |_| selector,
    //isTentative is true if the tile is part of a tentative move
    void Tile::set(char newLetter, bool isTentative,bool isSelecting){
        //save previous state here
        if(validLetters.find(newLetter)==string::npos){
            cerr<<"letter "<<newLetter<<" invalid!"<<endl;
            newLetter=' ';
        }
        letter=newLetter;
        selecting=isSelecting;
        tentative=isTentative;
        setTop();
    }
    bool Tile::isTentative(){
        return tentative;
    }
    void Tile::setTentative(bool newVal){
        tentative=newVal;
        setTop();
    }
    //only to be called during construction of board
    void Tile::setMod(string newMod){
        bool modValid=false;
        for(int i=0;i<validModifiers.size();i++){
            if(newMod==validModifiers[i]){
                modValid=true;
            }
        }
        if(!modValid){
            cerr<<"bad mod: -"<<newMod<<"-"<<endl;
        }
        modifier=newMod;
    }



//private
    string Tile::points2Str(int points){
        string toReturn="XX";
        if(points==0){
            toReturn="__";
        }
        else{
            stringstream formatter;
            formatter<<points;
            toReturn=formatter.str();
            if(toReturn.size()!=2){
                toReturn='_'+toReturn;
            }
        }
        return toReturn;
    }
    void Tile::setTop(){
        top="    ";
        //"* / " not selecting, tentative
        //"|*/|" selecting, tentative
        //"*   " not selecting, not tentative
        //"|*_|" selecting, not tentative
        //wher * is dispLet
        char dispLet=letter;
        if(dispLet==' '){
            dispLet='_';
        }
        top[0]=letter;
        top[1]=' ';
        top[2]=' ';
        top[3]=' ';
        if(selecting){
            top[0]='|';
            top[1]=dispLet;
            top[2]='_';
            top[3]='|';
        }
        if(tentative){
            top[2]='/';
        }
    }
    void Tile::setMap(){
        static map<char,int> point;
        point.insert(pair<char,int>(' ',0));
        point.insert(pair<char,int>('@',0));
        point.insert(pair<char,int>('E',1));
        point.insert(pair<char,int>('A',1));
        point.insert(pair<char,int>('I',1));
        point.insert(pair<char,int>('O',1));
        point.insert(pair<char,int>('N',1));
        point.insert(pair<char,int>('R',1));
        point.insert(pair<char,int>('T',1));
        point.insert(pair<char,int>('L',1));
        point.insert(pair<char,int>('S',1));
        point.insert(pair<char,int>('U',1));
        point.insert(pair<char,int>('D',2));
        point.insert(pair<char,int>('G',2));
        point.insert(pair<char,int>('B',3));
        point.insert(pair<char,int>('C',3));
        point.insert(pair<char,int>('M',3));
        point.insert(pair<char,int>('P',3));
        point.insert(pair<char,int>('F',4));
        point.insert(pair<char,int>('H',4));
        point.insert(pair<char,int>('V',4));
        point.insert(pair<char,int>('W',4));
        point.insert(pair<char,int>('Y',4));
        point.insert(pair<char,int>('K',5));
        point.insert(pair<char,int>('J',8));
        point.insert(pair<char,int>('X',8));
        point.insert(pair<char,int>('Q',10));
        point.insert(pair<char,int>('Z',10));
        points=&point;
    }
    void Tile::setValidMods(){
        validModifiers.push_back("_+");
        validModifiers.push_back("__");
        validModifiers.push_back("TW");
        validModifiers.push_back("DW");
        validModifiers.push_back("TL");
        validModifiers.push_back("DL");
    }

    ostream& operator<<(ostream& os,Tile& t){
        if(t.letter==' '){
            os<<"%"<<" ";
        }
        else{
            os<<t.letter<<" ";
        }
        os<<t.tentative<<" "<<t.modifier<<" ";
        return os;
    }
    istream& operator>>(istream& is,Tile& t){
        char letter;
        is>>letter;
        if(letter=='%'){
            letter=' ';
        }
        t.letter=letter;
        is>>t.tentative>>t.modifier;
        t.setTop();
        return is;
    }
