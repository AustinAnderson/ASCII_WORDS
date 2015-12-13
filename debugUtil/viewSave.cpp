#include "../Tile.h"

using namespace std;

void readAndShowRack(ifstream& in){
    vector<Tile> tiles(7);
    for(int i=0;i<7;i++){
        in>>tiles[i];
    }
    for(int i=0;i<7;i++){
        cout<<tiles[i].line1();
    }
    cout<<TXTCLRRST<<endl;
    for(int i=0;i<7;i++){
        cout<<tiles[i].line2();
    }
    cout<<TXTCLRRST<<endl;
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



    int num;
    in>>num;
    cout<<" it's player "<<(!num)+1<<" turn"<<endl;
    in>>num;
    cout<<"score: p1="<<num;
    in>>num;
    cout<<" p2="<<num<<" (";
    in>>num;
    if(!num){
        cout<<"not ";
    }
    cout<<"currently committing)"<<endl;
    cout<<"tile bag contents:"<<endl;
    for(int i=0;i<27;i++){
        cout<<" "<<char(i+int('@'))<<" ";
    }
    cout<<endl;
    for(int i=0;i<27;i++){
        in>>num;
        printf(" %-2d",num);
    }
    cout<<endl;
    string lastWord;
    in>>lastWord;
    cout<<"last word played: "<<lastWord<<endl;
    readAndShowBoard(in);
    cout<<BKGRND_WHT<<"my rack                            "<<TXTCLRRST<<endl;
    readAndShowRack(in);
    cout<<BKGRND_WHT<<"other's rack                       "<<TXTCLRRST<<endl;
    readAndShowRack(in);

    return 0;
}

