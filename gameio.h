#ifndef GAME_IO
#define GAME_IO//need to make game know which player it is on start up
class GameIOController{
    public:
        GameIOController(string filePath, bool p1,const TileBag* tb,
                const Board* b,const Scores* s, const Interface* i);

    private:
        string filePath;
        bool isPlayer1;
        TileBag* tilebag;
        Board* board;
        Scores* scores;
        Interface* interface;
        StringStream data;
}

#endif//GAME_IO
