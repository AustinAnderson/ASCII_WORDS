#include "bottomDisplay.h"
//public:
    bottomDisplay::bottomDisplay(){
        content.push_back("");
        content.push_back("                             key bindings: ");
        content.push_back("");
        content.push_back("   up: i  down: k   left: j   right: l  confirm: f  back: d  quit:  q");
        content.push_back("                         submit: <enter key>");
    }
    vector<string> bottomDisplay::print(){
        return content;
    }
