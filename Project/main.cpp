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

int sumArray(int array[], int len){
    int sum = 0;

    for(int i = 0; i < len; i++){
        sum += array[i];
    }

    return sum;
}

bool valueInArray(int value, int array[]){
    int size = sizeof(array)/ sizeof(int);

    for(int i = 0; i < size; i++){
        if(array[i] == value){
            return true;
        }
    }

    return false;
}

int main() {
    gameSetup();
}
