#include <iostream>
#include <map>
#include "gameMenu.h"
#include "game.h"
#include "main.h"

// INCLUIR O PROOPRIO H
using namespace std;

// 4 menu options:
// play
// options
// last game scores
// best scores



void play() {
    cout << "Do you want to play with bot? (Y/N): ";
    char res;
    while (1){
        bool valid = readChar(res);
        if (!valid || (toupper(res) != 'Y' && toupper(res) != 'N')){
            cout << "Invalid, re-enter: ";
            continue;
        }
        break;
    }
    if (res == 'Y'){
        gameSetup(true);
    }
    else{
        gameSetup(false);
    }
}

void instructions() {

}

void lastGames() {

}

void bestScores() {

}


void exit() {

}

// MUDAR NOME
void run() {

    map<string, char> cmdToChar = { // TO BE USED IN SWITCH CMD, DOESNT ACCEPT STRINGS
            {"play",        'p'},
            {"rules",       'r'},
            {"instructions",'i'},
            {"last games",  'l'},
            {"best scores", 'b'},
            {"exit",        'e'},
    };

    bool playing = true;

    while (playing) {
        printf("Please enter a command: \n"
               "Play\n"
               "Instructions\n"
               "Last Games\n"
               "Best Scores\n"
               "Exit\n\n"
               "Choose: ");

        string cmd;
        cin >> cmd;
        // Use here Read String
        if (cin.fail()) {
            printf("Input Invalid\n\n");
            cin.ignore(1000, '\n');
            cin.clear();
        } else if (cin.peek() != '\n') {
            printf("Input Invalid\n\n");
            cin.clear();
        } else {
            switch (cmdToChar[cmd]) {
                case 'p':
                    play();
                    break;
                case 'i' :
                    instructions();
                    break;
                case 'l':
                    lastGames();
                    break;
                case 'b':
                    bestScores();
                    break;
                case 'e':
                    playing = false;
                    cout << "Thanks for playing!" << endl;
                    break;
            }
        }
    }
}