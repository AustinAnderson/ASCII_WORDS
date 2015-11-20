#ifndef BIND_DISPLAY
#define BIND_DISPLAY
#include "globals.h"

enum MODES {DEFAULT,HIGHLIGHTED,SELECTED};

class BindDisplay{
    public:
        BindDisplay();
        void setName(string newName);
        void setMode(int mode);
        void setBound(char key);
        char getBound();
        string print();

    private:
        int mode;
        char bound;
        string name;

};
#endif//BIND_DISPLAY


