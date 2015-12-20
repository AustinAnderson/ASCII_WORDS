#include "../Tile.h"

using namespace std;

void readAndShowTileBag(ifstream& in){
    int numOfLetter;
    Tile tile;
    for(int i=0;i<27;i++){
        cout<<" "<<char(i+int('@'))<<" ";
    }
    cout<<endl;
    for(int i=0;i<27;i++){
        in>>numOfLetter;
        printf(" %-2d",numOfLetter);
        for(int j=0;j<numOfLetter;j++){
            in>>tile;
        }
    }
    cout<<endl;
}



void readAndShowRack(ifstream& in, string l1, string l2){
    vector<Tile> tiles(7);
    for(int i=0;i<7;i++){
        in>>tiles[i];
    }
    for(int i=0;i<7;i++){
        cout<<tiles[i].line1();
    }
    cout<<TXTCLRRST<<" "<<l1<<endl;
    for(int i=0;i<7;i++){
        cout<<tiles[i].line2();
    }
    cout<<TXTCLRRST<<" "<<l2<<endl;
}

void readAndShowBoard(ifstream& in){
    vector<Tile> tiles(15);
    for(int j=0;j<15;j++){
        for(int i=0;i<15;i++){
            in>>tiles[i];
        }
        for(int i=0;i<15;i++){
            cout<<tiles[i].line1();
        }
        cout<<TXTCLRRST<<endl;
        for(int i=0;i<15;i++){
            cout<<tiles[i].line2();
        }
        cout<<TXTCLRRST<<endl;
    }

}

int main(int argc, char** argv){
    string file;
    if(argc>1){
        file=argv[1];
    }
    else{
        cout<<"Enter file name: ";
        cin>>file;
    }
    ifstream in;
    in.open(file.c_str());
    if(!in){
        cout<<"can't open "<<file<<endl;
        exit(1);
    }


    stringstream format;
    string turn;
    string score1;
    string score2;
    int num;
    in>>num;
    format<<"  it's player "<<(!num)+1<<"'s turn";
    turn=format.str();
    format.str("");
    in>>num;
    format<<"   score: p1="<<num;
    in>>num;
    format<<" p2="<<num;
    in>>num;
    score1=format.str();
    format.str("");
    format<<"(";
    if(!num){
        format<<"not ";
    }
    format<<"currently committing)";
    score2=format.str();
    cout<<"tile bag contents:"<<endl;
    readAndShowTileBag(in);
    cout<<endl;
    string lastWord;
    in>>lastWord;
    lastWord="last word played: "+lastWord;
    readAndShowBoard(in);
    cout<<BKGRND_WHT<<"my rack                            "<<TXTCLRRST<<endl;
    readAndShowRack(in,lastWord,turn);
    cout<<BKGRND_WHT<<"other's rack                       "<<TXTCLRRST<<endl;
    readAndShowRack(in,score1,score2);

    return 0;
}

