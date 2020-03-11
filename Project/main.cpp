#include <iostream>
#include "gameMenu.h"
#include "game.h"

using namespace std;


bool readString(string &s) {

    cin >> s;

    if (cin.fail()) {
        cin.ignore(1000, '\n');
        cin.clear();
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
        cin.ignore(1000, '\n');
        cin.clear();
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
        cin.ignore(1000, '\n');
        cin.clear();
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


int main() {
    gameSetup();
}
