/******************************************************
* Filename:       asciiWords.cpp
* Author:         Austin Anderson
* Date Created:  2015-02-20
* Description:    ascii version of words with friends
* 
******************************************************/

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <list>
#include <ctime>
#include <cstdlib>
#include <set>
#include <sys/ioctl.h>

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

//toggle colors
//*
const string WORD_VALID="\e[1;90;48;5;106m";
const string WORD_INVALID="\e[1;97;41m";
//const string BKGRND_WHT="\e[1;90;47m";//grey
const string BKGRND_WHT="\e[1;90;107m";//bright
const string BKGRND_BLU="\e[1;97;104m";
const string BKGRND_RED="\e[1;97;41m";
const string BKGRND_GRN="\e[1;97;48;5;106m";
const string BKGRND_PRL="\e[1;97;45m";
const string BKGRND_YLW="\e[1;90;103m";//bright
//const string BKGRND_YLW="\e[1;90;43m";
const string BKGRND_ORN="\e[1;97;48;5;166m";
const string TXTCLRRST="\e[0m";
/*/
const string WORD_VALID="";
const string WORD_INVALID="";
const string BKGRND_WHT="";
const string BKGRND_BLU="";
const string BKGRND_RED="";
const string BKGRND_GRN="";
const string BKGRND_PRL="";
const string BKGRND_YLW="";
const string BKGRND_ORN="";
const string TXTCLRRST="";
//*/
const string validLetters="ABCDEFGHIJKLMNOPQRSTUVWXYZ@ ";
 
//from cboard.cprogramming.com/c-programming/63166-kbhit-linux.html
int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;
 
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
    ch = getchar();
 
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
 
    if(ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }
 
    return 0;
}


class Tile{
    public:
        Tile(){
            setValidMods();
            setMap();
            set(' ',false,false);
            setMod("__");
        }
        Tile(bool sel,string mod){
            setValidMods();
            setMap();
            set(' ',false,sel);
            setMod(mod);
        }
        char getLetter(){
            return letter;
        }
        int getPoints(){
            return (*points)[letter];
        }
        string getMod(){
            return modifier;
        }
        string getColor(){
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
        string line1(){
            return getColor()+top+BKGRND_WHT+"|";
        }
        string line2(){
            string toReturn=modifier+points2Str((*points)[letter]);
            return getColor()+toReturn+BKGRND_WHT+"|";
        }
        void toggleSelecting(){
            selecting=!selecting;
            setTop();
        }
        //is selecting is true if tile is |_| selector,
        //isTentative is true if the tile is part of a tentative move
        void set(char newLetter, bool isTentative=true,bool isSelecting=true){
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
        bool isTentative(){
            return tentative;
        }
        void setTentative(bool newVal){
            tentative=newVal;
            setTop();
        }
        //only to be called during construction of board
        void setMod(string newMod){
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
        friend ostream& operator<<(ostream& os,Tile& t){
            os<<t.letter<<" "<<t.tentative<<" "<<t.selecting<<" "<<t.modifier<<" ";
            return os;
        }
        friend istream& operator>>(istream& is,Tile& t){
            is>>t.letter>>t.tentative>>t.selecting>>t.modifier;
            return is;
        }
    private:
        string points2Str(int points){
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
        void setTop(){
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
        void setMap(){
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
        void setValidMods(){
            validModifiers.push_back("_+");
            validModifiers.push_back("__");
            validModifiers.push_back("TW");
            validModifiers.push_back("DW");
            validModifiers.push_back("TL");
            validModifiers.push_back("DL");
        }
        map<char,int>* points;//only read, so just need one
        pair<string,string> previousState;
        vector<string> validModifiers;
        string top;
        
        char letter;
        bool tentative;
        bool selecting;
        string modifier;
};

class Scores{
    public:
        Scores(){
            p1=0;
            p2=0;
            committing=false;
        }
        Scores(int newP1,int newP2){
            p1=newP1;
            p2=newP2;
            committing=false;
        }
        void set(int np1,int np2,bool ncommitting=false){
            p1=np1;
            p2=np2;
            committing=ncommitting;
        }
        void add(bool p,int gain){
            if(p){
                p1+=gain;
            }
            else{
                p2+=gain;
            }
        }
        void toggleCommitting(){
            committing=!committing;
        }
        void print(){
            if(!committing){
                cout<<" ________________                                         _________________ "<<endl;          
                cout<<"|                |                                       |                 |"<<endl;           
                cout<<"| player 1: "<<points2Str(p1)<<" |                                       |  player 2: "<<points2Str(p2)<<" |"<<endl;           
                cout<<"|________________|                                       |_________________|"<<endl;
                cout<<endl;
            }
            else{
                cout<<" ________________                                         _________________   "<<endl;            
                cout<<"|                |         =======_______=======         |                 | "<<endl;             
                cout<<"| player 1: "<<points2Str(p1)<<" |          ) Play Move? Y/N (           |  player 2: "<<points2Str(p2)<<" | "<<endl;             
                cout<<"|________________|         /__====******====__\\          |_________________| "<<endl;              
                cout<<endl;
            }
        }
        friend ostream& operator<<(ostream& os,Scores& s){
            os<<s.p1<<" "<<s.p2<<" "<<s.committing<<" ";
            return os;
        }
        friend istream& operator>>(istream& is,Scores& s){
            is>>s.p1>>s.p2>>s.committing;
            return is;
        }
    private:
        string points2Str(int points){
            stringstream formatter;
            formatter<<points;
            string toReturn=formatter.str();
            for(int i=0;i<(4-formatter.str().size());i++){
                if(i%2==0){
                    toReturn=' '+toReturn;
                }
                else{
                    toReturn+=' ';
                }
            }
            return toReturn;
        }
        int p1;
        int p2;
        bool committing;
};

class Board{
    public:
        Board(){
            //*
            cout<<"Loading..."<<endl;
            ifstream dictFile;
            //string filePath="/home/csi/a/andersonau/game/asciiWords/dictionary";
            string filePath="./dictionary";
            string word;
            dictFile.open(filePath.c_str());
            while(dictFile>>word){
                dictionary.insert(word);
            }
            dictFile.close();
            //*/
            currentTentativeSum=0;
            xNdx=7;
            yNdx=7;
            Tile blank(false,"__");
            vector<vector<Tile> > alloc(15,vector<Tile>(15,blank));
            mat=alloc;
            mat[0][3].setMod("TW");
            mat[0][6].setMod("TL");
            mat[1][2].setMod("DL");
            mat[1][5].setMod("DW");
            mat[2][1].setMod("DL");
            mat[2][4].setMod("DL");
            mat[3][0].setMod("TW");
            mat[3][3].setMod("TL");
            mat[3][7].setMod("DW");
            mat[4][2].setMod("DL");
            mat[4][6].setMod("DL");
            mat[5][1].setMod("DW");
            mat[5][5].setMod("TL");
            mat[6][0].setMod("TL");
            mat[6][4].setMod("DL");
            mat[7][3].setMod("DW");//set a fourth of the board
            //reflect that forth vertically
            for(int i=0;i<8;i++){
                for(int j=8;j<15;j++){
                    mat[i][j]=mat[i][14-j];
                }
            }
            //reflect that half horizontally
            for(int i=8;i<15;i++){
                for(int j=0;j<15;j++){
                    mat[i][j]=mat[14-i][j];
                }
            }
            mat[xNdx][yNdx].set(' ',false,true);
            mat[xNdx][yNdx].setMod("_+");
        }
        bool isTentative(){
            return mat[xNdx][yNdx].isTentative();
        }
        void setTentative(bool newVal){
            mat[xNdx][yNdx].setTentative(newVal);
        }
        void toggleSelecting(){
            mat[xNdx][yNdx].toggleSelecting();
        }
        void up(){
            mat[xNdx][yNdx].toggleSelecting();
            if(xNdx>0){
                xNdx--;
            }
            mat[xNdx][yNdx].toggleSelecting();
        }
        void down(){
            mat[xNdx][yNdx].toggleSelecting();
            if(xNdx<mat.size()-1){
                xNdx++;
            }
            mat[xNdx][yNdx].toggleSelecting();
        }
        void left(){
            mat[xNdx][yNdx].toggleSelecting();
            if(yNdx>0){
                yNdx--;
            }
            mat[xNdx][yNdx].toggleSelecting();
        }
        void right(){
            mat[xNdx][yNdx].toggleSelecting();
            if(yNdx<mat[0].size()-1){
                yNdx++;
            }
            mat[xNdx][yNdx].toggleSelecting();
        }
        void updateCurrentTile(char letter){
            mat[xNdx][yNdx].set(letter);
            if(currentPlacementValid()){
                if(!currentWordsValid()){
                    currentTentativeSum=0;
                }
            }
            else{
                currentTentativeSum=0;
            }
        }
        void clearCurrentTile(){
            mat[xNdx][yNdx].set(' ',false);
            if(currentPlacementValid()){
                if(!currentWordsValid()){
                    currentTentativeSum=0;
                }
            }
            else{
                currentTentativeSum=0;
            }
        }
        char getCurrentTile(){
            return mat[xNdx][yNdx].getLetter();
        }
        vector<string> mat2Str(){
            vector<string> current=formatCurrent();
            vector<string> out;
            out.push_back(" __________________________________________________________________________ ");
            string l1="|";
            string l2=l1;
            for(int i=0;i<15;i++){
                for(int j=0;j<15;j++){
                    l1+=mat[i][j].line1();
                }
                for(int j=0;j<15;j++){
                    l2+=mat[i][j].line2();
                }
                out.push_back(l1);
                out.push_back(l2);
                l1="|";
                l2=l1;
            }
            out[0]+=current[0];
            out[1]+=current[1];
            out[2]+=current[2];
            out[3]+=current[3];
            return out;
        }
        bool currentPlacementValid(){
            bool isValid=true;
            //these numbers need to start different so that if there are all blank tiles the startx!=seedx&&starty!=seedy check
            //will change it isValid to false
            int seedx=-1;//seedx and y are the coordinates of the last tentative tile found
            int seedy=-1;
            int startx=-2;//startx and y are the coordinates of the first tentative tile found
            int starty=-2;
            for(int i=0;i<15;i++){
                for(int j=0;j<15;j++){
                    if((mat[i][j].getLetter()!=' ')&&mat[i][j].isTentative()){
                        if(seedx!=-1&&seedy!=-1){//if seedx and seedy have something,
                            if(i!=seedx&&j!=seedy){//and this new tile is not inline horizontally or vertically with the old tile...
                                isValid=false;//then placement is not valid
                            }
                        }
                        else{//if it is the first iteration where a tentative tile is found
                            startx=i;
                            starty=j;
                        }
                        seedx=i;
                        seedy=j;
                    }
                }
            }
            if(seedx!=startx&&seedy!=starty){//if the last tile is not inline with the first
                isValid=false;
            }
            if(isValid){
                bool vert=true;//determine direction
                if(startx!=seedx){
                    vert=false;
                }
                else{//if tentatives is a single tile aligned horizontally with a non tentative, assumption is wrong
                    int checkdown=seedy-1;
                    if(checkdown<0){
                        checkdown=seedy+1;//if out of bounds, check same spot
                    }
                    int checkup=seedy+1;
                    if(checkup>14){
                        checkup=seedy-1;//if out of bounds check same spot
                    }
                    if(mat[seedx][checkup].getLetter()==' '&&mat[seedx][checkdown].getLetter()==' '){//if both up and down from
                        vert=false;//single seed tile is blank, its actually horizontal
                    }
                }
//DEBUG
//cout<<"startx:"<<startx<<" seedx:"<<seedx<<" starty:"<<starty<<" seedy:"<<seedy<<" vert:"<<vert;
                list<pair<int, int> > currentTentatives;//push back and front from seed tile and add finished list to tentatives
                currentTentatives.push_back(make_pair(seedx,seedy));//add initial seed
                bool foundSpace=false;
                if(!vert){//find the string containing all the tentatives
                    for(int i=seedx+1;i<15;i++){
                        if(foundSpace&&mat[i][seedy].isTentative()){//if a space has been found and the current tile is tentative
                            isValid=false;                         //that means there are multiple 'words' in the line, so not valid
                        }
                        if(mat[i][seedy].getLetter()==' '){
                            foundSpace=true;
                        }
                        else{
                            if(!foundSpace){
                                currentTentatives.push_back(make_pair(i,seedy));
                            }
                        }
                    }
                    foundSpace=false;
                    for(int i=seedx-1;i>=0;i--){
                        if(foundSpace&&mat[i][seedy].isTentative()){
                            isValid=false;
                        }
                        if(mat[i][seedy].getLetter()==' '){
                            foundSpace=true;
                        }
                        else{
                            if(!foundSpace){
                                currentTentatives.push_front(make_pair(i,seedy));
                                startx=i;
                            }
                        }
                    }
                }
                else{
                    foundSpace=false;
                    for(int i=seedy+1;i<15;i++){
                        if(foundSpace&&mat[seedx][i].isTentative()){
                            isValid=false;
                        }
                        if(mat[seedx][i].getLetter()==' '){
                            foundSpace=true;
                        }
                        else{
                            if(!foundSpace){
                                currentTentatives.push_back(make_pair(seedx,i));
                            }
                        }
                    }
                    foundSpace=false;
                    for(int i=seedy-1;i>=0;i--){
                        if(foundSpace&&mat[seedx][i].isTentative()){
                            isValid=false;
                        }
                        if(mat[seedx][i].getLetter()==' '){
                            foundSpace=true;
                        }
                        else{
                            if(!foundSpace){
                                currentTentatives.push_front(make_pair(seedx,i));
                                starty=i;
                            }
                        }
                    }
                }
                if(isValid){//if valid, then current tentatives is the string of tiles played, now need to 
                    tentatives.clear();//add words that cross through the played string
                    tentatives.push_back(currentTentatives);
                    //for each tentative in that string, check the !vert direction's
                    //word
                    int x=startx;
                    int y=starty;
                    isValid=false;
                    list<pair<int, int> > tentatives0=tentatives[0];
                    for(list<pair<int, int> >::iterator i=tentatives0.begin();i!=tentatives0.end();i++){//for each tile played,
                        currentTentatives.clear();
                        currentTentatives.push_back(make_pair(x,y));
                        if(!mat[x][y].isTentative()){//checks incase of [tentativetile][nontentativetile][tentativetile]
                            isValid=true;
                        }
                        else{
                            if(!vert){
                                foundSpace=false;
                                for(int j=y+1;j<15;j++){
                                    if(mat[x][j].getLetter()==' '){
                                        foundSpace=true;
                                    }
                                    else{
                                        if(!foundSpace){
                                            isValid=true;
                                            currentTentatives.push_back(make_pair(x,j));
                                        }
                                    }
                                }
                                foundSpace=false;
                                for(int j=y-1;j>=0;j--){
                                    if(mat[x][j].getLetter()==' '){
                                        foundSpace=true;
                                    }
                                    else{
                                        if(!foundSpace){
                                            isValid=true;
                                            currentTentatives.push_front(make_pair(x,j));
                                        }
                                    }
                                }
                            }
                            else{
                                foundSpace=false;
                                for(int j=x+1;j<15;j++){
                                    if(mat[j][y].getLetter()==' '){
                                        foundSpace=true;
                                    }
                                    else{
                                        if(!foundSpace){
                                            isValid=true;
                                            currentTentatives.push_back(make_pair(j,y));
                                        }
                                    }
                                }
                                foundSpace=false;
                                for(int j=x-1;j>=0;j--){
                                    if(mat[j][y].getLetter()==' '){
                                        foundSpace=true;
                                    }
                                    else{
                                        if(!foundSpace){
                                            isValid=true;
                                            currentTentatives.push_front(make_pair(j,y));
                                        }
                                    }
                                }
                            }
                            //do adding in opposite traversal direction
                            //while not space,
                            //currentTentatives.push_back(tiles)
                            //while not space,
                            //currentTentatives.push_front(tiles)*/
                            if(currentTentatives.size()>1){
                                tentatives.push_back(currentTentatives);
                            }
                        }
                        if(mat[x][y].getMod()=="_+"&&mat[x][y].isTentative()){//or the start tile
                            isValid=true;
                        }
                        if(vert){
                            y++;
                        }
                        else{
                            x++;
                        }
                    }
                }
            }
            return isValid;

        }
        //computes the sum of the tiles added
        //and returns the tentative string
        vector<string> computeSum(){
            currentTentativeSum=0;
            vector<string> toReturn;
            for(int j=0;j<tentatives.size();j++){
                int sum=0;
                int numDW=0;
                int numTW=0;
                string word="";
                for(list<pair<int, int> >::iterator i=tentatives[j].begin();i!=tentatives[j].end();i++){
                    string mod=mat[i->first][i->second].getMod();
                    int mult=1;
                    if(mat[i->first][i->second].isTentative()){
                        if(mod=="DL"){
                            mult=2;
                        }
                        if(mod=="TL"){
                            mult=3;
                        }
                        if(mod=="DW"){
                            numDW++;
                        }
                        if(mod=="TW"){
                            numTW++;
                        }
                    }
                    word+=tolower(mat[i->first][i->second].getLetter());
                    sum+=mat[i->first][i->second].getPoints()*mult;
                }
                for(int i=0;i<numDW;i++){
                    sum*=2;
                }
                for(int i=0;i<numTW;i++){
                    sum*=3;
                }
                currentTentativeSum+=sum;
                toReturn.push_back(word);
            }
            return toReturn;
        }
        bool currentWordsValid(){
            vector<string> toCheck=computeSum();
            bool isValid=true;
            for(int i=0;i<toCheck.size();i++){
                if(dictionary.find(toCheck[i])==dictionary.end()){
                    isValid=false;
                }
            }
            return isValid;
        }
        int checkAndCommit(){
            int toReturn=-1;
            if(currentTentativeSum!=0){//currenttentative sum will always be 0 if words invalid
                toReturn=currentTentativeSum;
                currentTentativeSum=0;
                for(int j=0;j<tentatives.size();j++){
                    for(list<pair<int, int> >::iterator i=tentatives[j].begin();i!=tentatives[j].end();i++){
                        mat[i->first][i->second].setTentative(false);
                    }
                }
            }
            return toReturn;
        }

        friend ostream& operator<<(ostream& os,Board& b){
            os<<b.mat.size()<<" "<<b.mat[0].size()<<" ";
            for(int i=0;i<b.mat.size();i++){
                for(int j=0;j<b.mat[0].size();j++){
                    os<<b.mat[i][j]<<" ";
                }
            }
            os<<b.tentatives.size()<<" ";
            if(b.tentatives.size()>0){
                os<<b.tentatives[0].size()<<" ";
            }
            else{
                os<<0<<" ";
            }
            for(int i=0;i<b.tentatives.size();i++){
                for(list<pair<int,int> >::iterator j=b.tentatives[0].begin();j!=b.tentatives[0].end();j++){
                    os<<j->first<<" "<<j->second<<" ";
                }
            }
            os<<b.xNdx<<" "<<b.yNdx<<" "<<b.currentTentativeSum<<" ";
            return os;
        }
        friend istream& operator>>(istream& is,Board& b){
            int maxi=0;
            int maxj=0;
            b.mat.clear();
            Tile held;
            vector<Tile> row;
            is>>maxi>>maxj;
            for(int i=0;i<maxi;i++){
                for(int j=0;j<maxj;j++){
                    is>>held;
                    row.push_back(held);
                }
                b.mat.push_back(row);
                row.clear();
            }//players have different tentatives, so this probably wont work
            b.tentatives.clear();
            int heldx; 
            int heldy;
            list<pair<int, int> > trow;
            is>>maxi>>maxj;
            for(int i=0;i<maxi;i++){
                for(int j=0;j<maxj;j++){
                    is>>heldx>>heldy;
                    trow.push_back(make_pair(heldx,heldy));
                }
                b.tentatives.push_back(trow);
                trow.clear();
            }
            is>>b.xNdx>>b.yNdx>>b.currentTentativeSum;
            return is;
        }
    private:
        set<string> dictionary;
        vector<vector<Tile> > mat;
        vector<list<pair<int, int> > > tentatives;
        int xNdx;
        int yNdx;
        int currentTentativeSum;
        vector<string> formatCurrent(){
            vector<string> out;
            stringstream formatter;
            formatter<<currentTentativeSum;
            string val=formatter.str();
            for(int i=0;i<(3-formatter.str().size());i++){
                if(i%2==0){
                    val=' '+val;
                }
                else{
                    val+=' ';
                }
            }
            string color=WORD_VALID;
            if(currentTentativeSum==0){
                val="---";
                color=WORD_INVALID;
            }

            out.push_back("     ___________ ");
            out.push_back("    |"+color+"  current  |"+BKGRND_WHT);
            val="    |"+color+"    "+val+"    |"+BKGRND_WHT;
            out.push_back(val);
            out.push_back("    |"+color+"___________|"+BKGRND_WHT);
            return out;
        }

};

class Rack{
    
    public:
        Rack(){
            vector<Tile> placeHolder(7);
            tiles=placeHolder;
            selecting=false;
            ndx=0;
            space="        ";
        }
                


        void setCurrentTile(char let){
            setTile(ndx,let);
        }
        void clearCurrentTile(){
            clearTile(ndx);
        }
        char getCurrentTile(){
            return tiles[ndx].getLetter();
        }
        int getNextBlankNdx(){
            int ndx=0;
            while(ndx<7&&tiles[ndx].getLetter()!=' '){
                ndx++;
            }
            if(ndx==7){
                ndx=-1;
            }
            return ndx;
        }
        bool isSelecting(){
            return selecting;
        }
        void toggleSelecting(){
            selecting=!selecting;
            tiles[ndx].toggleSelecting();
        }
        void up(){
            tiles[ndx].toggleSelecting();
            if(ndx>0){
                ndx--;
            }
            tiles[ndx].toggleSelecting();
        }
        void down(){
            tiles[ndx].toggleSelecting();
            if(ndx<tiles.size()-1){
                ndx++;
            }
            tiles[ndx].toggleSelecting();
        }
        vector<string> toString(){
            vector<string> out;
            out.push_back(space+" ____");
            string l1=space;
            for(int i=0;i<tiles.size();i++){
                if(selecting&&i==ndx){
                    l1[l1.size()-1]='>';
                }
                l1+="|"+tiles[i].line1();
                out.push_back(l1);
                out.push_back(space+"|"+tiles[i].line2());
                l1=space;
            }
            
            return out;
        }
        
        void setTile(int ndx,char let){
            tiles[ndx].set(let,false,false);
        }
    private:
        void clearTile(int ndx){
            tiles[ndx].set(' ',false,false);
            tiles[ndx].setMod("__");
        }
        string space;
        vector<Tile> tiles; 
        bool selecting;
        int ndx;

};
class TileBag{
    public:
        TileBag(){               //@ A B C D E  F G H I J K L M N O P Q R S T U V W X Y Z
            int initTilesLeft[27]={2,9,2,2,4,12,2,3,2,9,1,1,4,2,6,8,2,1,6,4,6,4,2,2,1,2,1};
            for(int i=0;i<27;i++){
                tilesLeft[i]=initTilesLeft[i];
            }
            srand(time(0));
            empty=false;
        }
        //used for when two clients are active over multiplayer
        void update(TileBag other){
            bool newer=true;
            for(int i=0;i<27;i++){
                if(other.tilesLeft[i]>tilesLeft[i]){
                    newer=false;
                }
            }
            if(newer){
                for(int i=0;i<27;i++){
                    tilesLeft[i]=other.tilesLeft[i];
                }
            }
        }
        //get the number of tiles
        //for the letter "key" that are left
        int getNumLeft(char key){
            if(validLetters.find(key)==string::npos||key==' '){
                cerr<<"in getNumLeft, invalid key, -"<<key<<"-"<<endl;
            }
            return tilesLeft[int(key)-int('@')];
        }
        bool isEmpty(){
            return empty;
        }
        /**
         * gets a letter for a new tile, and decrements the number of those
         * tiles available at the same time
         * returns the char to use, or ' ' if the bag is empty
         */
        char pullTile(){
            vector<char> tileList;
            char toReturn=' ';
            for(int i=0;i<27;i++){
                for(int j=0;j<tilesLeft[i];j++){
                    tileList.push_back(char(i+int('@')));
                }
            }
            if(tileList.size()==0){
                empty=true;
            }
            else{
                int ndx=rand()%tileList.size();
                toReturn=tileList[ndx];
                tilesLeft[int(toReturn)-int('@')]--;//remove tile from bag
            }
            return toReturn;
        }
    private:
        //take advantage of the fact that alphabet in ascii
        //is contiguous from @toZ
        int tilesLeft[27];
        bool empty;
};

class Player{
    public:
        Player(){
            int ndx=0;
            while((ndx=rack.getNextBlankNdx())!=-1){
                rack.setTile(ndx,bag.pullTile());
            }
        }
        vector<vector<string> > toStrs(){
            vector<vector<string> > toReturn;
            toReturn.push_back(board.mat2Str());
            toReturn.push_back(rack.toString());
            return toReturn;
        }
        void chooseTile(){
            char currentTile=rack.getCurrentTile();
            if(currentTile!=' '){
                //choose tile letter
                board.updateCurrentTile(currentTile);
                rack.clearCurrentTile();
            }
        }
        void refilTiles(){
            int rndx=rack.getNextBlankNdx();
            while(rndx!=-1){
                rack.setTile(rndx,bag.pullTile());
                rndx=rack.getNextBlankNdx();
            }
        }
        void replaceTile(){
            rack.setCurrentTile(bag.pullTile());
        }
        friend class Interface;
    private:
        Board board;
        TileBag bag;
        Rack rack;
};

class bottomDisplay{
    public:
        bottomDisplay(){
            content.push_back("");
            content.push_back("                             key bindings: ");
            content.push_back("");
            content.push_back("   up: i  down: k   left: j   right: l  confirm: f  back: d  quit:  q");
            content.push_back("                         submit: <enter key>");
        }
        vector<string> print(){
            return content;
        }
    private:
        vector<string> content;

};

class Interface{
    public:
        Interface(){
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
        void print(){

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
        void play(){//        r  c
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
      //  friend ostream& operator>>(ostream& os,Interface& game){////////
      //      os>>game.score;
      //      os>>game.guy;
      //  }
    private:
        
        //void updateGame(){//////////////////////////////////////
        //    if(!true/*p1wordsp2.lck is found*/){
        //        //open gamefile
        //        gamefile>>*this;
        //    }
       // }
        string getInitialSize(){
            stringstream format;
            format<<"resize -s ";

            struct winsize w;//http://stackoverflow.com/questions/1022957/getting-terminal-width-in-c
            ioctl(0, TIOCGWINSZ, &w);//get the terminal size
            format<<w.ws_row<<" "<<w.ws_col;

            return format.str();
        }
        string setScreenBack;
        bool player;//current player: true is this instance, false is other player's instance
        //if backspace
        void putTileBack(){
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
        void chooseTile(){
            toggleSelecting();
            guy.chooseTile();
            system("clear");
            print();
        }
        void toggleSelecting(){
            if(' '==guy.board.getCurrentTile()){
                choosingTile=!choosingTile;
                guy.rack.toggleSelecting();
                guy.board.toggleSelecting();
                system("clear");
                print();
            }
        }
        void up(){
            if(!choosingTile){
                guy.board.up();
            }
            else{
                guy.rack.up();
            }
            system("clear");
            print();
        }
        void down(){
            if(!choosingTile){
                guy.board.down();
            }
            else{
                guy.rack.down();
            }
            system("clear");
            print();
        }
        void left(){
            if(!choosingTile){
                guy.board.left();
            }
            system("clear");
            print();
        }
        void right(){
            if(!choosingTile){
                guy.board.right();
            }
            system("clear");
            print();
        }
        char char_up;
        char char_down;
        char char_left;
        char char_right;
        char char_submit;
        char char_enter;
        char char_back;
        char char_quit;

        bool choosingTile;
        Scores score;
        vector<string> message;
        Player guy;
        bottomDisplay bottom;

};

int main(int argc, char** argv){

    Interface interface;
    interface.play();
    return 0;
}
