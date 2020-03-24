//
// Created by andremoreira9 on 10/03/20.
//

#include <map>

#ifndef PROJECT_MAIN_H
#define PROJECT_MAIN_H

using namespace std;


extern map<string, string> COLORS;

void clearScreen();
bool readString(string &x);
bool readChar(char &c);
bool readInt(int &i);
int mod(int a, int b);
int sumArray(int array[], int len);


#endif //PROJECT_MAIN_H
