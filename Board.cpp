#include "Board.h"

//public:
    Board::Board(){
        //*
        cout<<"Loading..."<<endl;
        ifstream dictFile;
        //string filePath="/home/csi/a/andersonau/game/asciiWords/dictionary";
        string filePath="./dictionary.txt";
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
    bool Board::isTentative(){
        return mat[xNdx][yNdx].isTentative();
    }
    void Board::setTentative(bool newVal){
        mat[xNdx][yNdx].setTentative(newVal);
    }
    void Board::toggleSelecting(){
        mat[xNdx][yNdx].toggleSelecting();
    }
    void Board::up(){
        mat[xNdx][yNdx].toggleSelecting();
        if(xNdx>0){
            xNdx--;
        }
        mat[xNdx][yNdx].toggleSelecting();
    }
    void Board::down(){
        mat[xNdx][yNdx].toggleSelecting();
        if(xNdx<mat.size()-1){
            xNdx++;
        }
        mat[xNdx][yNdx].toggleSelecting();
    }
    void Board::left(){
        mat[xNdx][yNdx].toggleSelecting();
        if(yNdx>0){
            yNdx--;
        }
        mat[xNdx][yNdx].toggleSelecting();
    }
    void Board::right(){
        mat[xNdx][yNdx].toggleSelecting();
        if(yNdx<mat[0].size()-1){
            yNdx++;
        }
        mat[xNdx][yNdx].toggleSelecting();
    }
    void Board::updateCurrentTile(char letter){
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
    void Board::clearCurrentTile(){
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
    char Board::getCurrentTile(){
        return mat[xNdx][yNdx].getLetter();
    }
    vector<string> Board::mat2Str(){
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
    bool Board::currentPlacementValid(){
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
    vector<string> Board::computeSum(){
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
    bool Board::currentWordsValid(){
        vector<string> toCheck=computeSum();
        bool isValid=true;
        for(int i=0;i<toCheck.size();i++){
            if(dictionary.find(toCheck[i])==dictionary.end()){
                isValid=false;
            }
        }
        return isValid;
    }
    int Board::checkAndCommit(){
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

//private:
    vector<string> Board::formatCurrent(){
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

