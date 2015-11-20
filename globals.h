#ifndef GLOBALS
#define GLOBALS
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

enum KeyBindings{REBIND,UP,DOWN,LEFT,RIGHT,
    SUBMIT,CONFIRM,BACK,CLEAR,QUIT,NUM_BOUND_KEYS};

const string KeyNames[NUM_BOUND_KEYS]={"Rebind","Up","Down","Left","Right",
    "Submit","Confirm","Back","Clear","Quit"};//these must match the above

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
int kbhit();

//get char that supports arrow keys
// uses ^ V < > for returned direction
char getch();

#endif
