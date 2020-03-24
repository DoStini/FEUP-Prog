#include <iostream>
#include "gameMenu.h"
#include "game.h"
#include <vector>
#include <algorithm>
#include "main.h"
#include <map>


using namespace std;

map<string, string> COLORS = {
        {"RESET",       "\u001B[0m"},
        {"RED",         "\u001B[0;31m"},
        {"BOLD_RED",    "\u001B[1;31m"},
        {"YELLOW",       "\u001B[0;33m"},
        {"BOLD_YELLOW",  "\u001B[1;33m"},
        {"BLUE",      "\u001B[0;34m"},
        {"BOLD_BLUE", "\u001B[1;34m"},
        {"CYAN",        "\u001B[0;36m"},
        {"BOLD_CYAN",   "\u001B[1;36m"}
};


void clearScreen()
{
    cout << "\033[2J";
    cout.flush();
}


bool readString(string &s) {

    cin >> s;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        return false;
    } else if (cin.peek() != '\n') {
        cin.ignore();
        return false;
    } else {
        return true;
    }
}

bool readChar(char &c){
    cin >> c;
    if (cin.fail()){
        cin.clear();
        cin.ignore(1000, '\n');
        return false;
    }
    else if (cin.peek() != '\n'){
        cin.ignore(1000, '\n');
        return false;
    }
    else{
        return true;
    }
}

bool readInt(int &i){
    cin >> i;
    if (cin.fail()){
        cin.clear();
        cin.ignore(1000, '\n');
        return false;
    }
    else if (cin.peek() != '\n'){
        cin.ignore(1000, '\n');
        return false;
    }
    else{
        return true;
    }
}

int mod(int a,int b){
    if (a < 0){
        return a%b + b;
    }
    else{
        return a%b;
    }
}

int sumArray(int array[], int len){
    int sum = 0;

    for(int i = 0; i < len; i++){
        sum += array[i];
    }

    return sum;
}


int main(){
    COLORS["MAIN_BOLD"] =  COLORS["BOLD_CYAN"];
    COLORS["MAIN"] = COLORS["CYAN"];
    while (1){
        run();
    }
}
