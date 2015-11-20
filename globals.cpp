#include "globals.h"
int kbhit(void){
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

char getch(){
    char toReturn=getchar();
    if(toReturn==char(27)){
        getchar();
        toReturn=getchar();
        if(toReturn==char(65)){
            toReturn='^';
        }
        else if(toReturn==char(66)){
            toReturn='V';
        }
        else if(toReturn==char(67)){
            toReturn='>';
        }
        else if(toReturn==char(68)){
            toReturn='<';
        }
    }
    return toReturn;
}
