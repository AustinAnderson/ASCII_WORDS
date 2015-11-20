#ifndef BOTTOM_DISPLAY
#define BOTTOM_DISPLAY
#include "globals.h"
#include "BindDisplay.h"
class bottomDisplay{
    public:
        string print();
        void rebind();
        void init(vector<char>* initialBindings);
    private:
        string header;
        string headerDefault;
        string headerHighlighted;
        int mode;
        int xNdx;
        int yNdx;
        vector<vector<BindDisplay> > contentMat;
        vector<char>* keyBindings;

        void up();
        void down();
        void left();
        void right();
        void repaint();
        string generateHeaderSelected();
        string getKeyName(char key);
        int getKeyNdx(char key);
        void setBinding(int key,char keyChar);
};
#endif//BOTTOM_DISPLAY
