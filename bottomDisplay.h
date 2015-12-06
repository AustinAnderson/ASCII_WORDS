#ifndef BOTTOM_DISPLAY
#define BOTTOM_DISPLAY
#include "globals.h"
#include "BindDisplay.h"
class bottomDisplay{
    public:
        string print();
        void rebind();
        //using init instead of a constructor with arguments
        //because when using
        //upperclass():bottomDisplay(initBindings,filepath),
        //upperclass creates the initBindings in the first place
        //so the pointer passed to the constructor can't be set correctly
        void init(vector<char>* initialBindings,string writePreferencesTo);
        friend ostream& operator<<(ostream& os,bottomDisplay& bottom);
    private:
        string header;
        string headerDefault;
        string headerHighlighted;
        string headerError;
        string bindPreferencesPath;
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
        void savePreferences();
        string generateHeaderSelected();
        string getKeyName(char key);
        BindDisplay* checkAlreadyMapped(char input);
        int getKeyNdx(char key);
        void setBinding(int key,char keyChar);
};
#endif//BOTTOM_DISPLAY
