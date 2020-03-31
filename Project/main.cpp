#include <iostream>
#include "gameMenu.h"
#include "game.h"
#include <vector>
#include <algorithm>
#include "main.h"
#include <map>
#include <sstream>
#include <unistd.h>


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

void gotoxy(int x, int y){
    ostringstream oss;
    oss << "\033["<< y << ";"<< x << "H";
    cout << oss.str();
}


void clearScreen()
{
    cout << "\033[2J";
    gotoxy(0, 0);
}


/*
 * All of the functions: readString, readChar, redInt are use to get an input
 *
 * @param variable - variable to store the value of the reading
 * @return bool stating if there was an error in the reading or not
 */


bool readString(string &s) {

    cin >> s;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        return false;
    } else if (cin.peek() != '\n') {
        cin.ignore(1000, '\n');
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
        if (cin.eof()){
            cin.clear();
            cin.ignore(1000, '\n');
            i = ENDGAME;
        }
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

    /*
     * Returns true modulos function
     */

    if (a < 0){
        return a%b + b;
    }
    else{
        return a%b;
    }
}

int sumArray(int array[], int len){

    /*
     * Sums an array of integers
     */

    int sum = 0;

    for(int i = 0; i < len; i++){
        sum += array[i];
    }

    return sum;
}


int main(){

    srand(time(NULL));

    clearScreen();
    COLORS["MAIN_BOLD"] =  COLORS["BOLD_CYAN"];
    COLORS["MAIN"] = COLORS["CYAN"];

    cout << COLORS["BOLD_RED"];
    cout << "Welcome to Oware by Andre Moreira." << endl;
    sleep(3);
    clearScreen();
    cout << COLORS["BOLD_YELLOW"];
    cout << "This is an oware game, I hope you have fun. The first commands will be shown after(instructions for program related commands and rules for game rules)." << endl;
    sleep(5);
    clearScreen();
    run();
}
