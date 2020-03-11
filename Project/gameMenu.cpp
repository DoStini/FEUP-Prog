#include <iostream>
#include <map>
#include "gameMenu.h"
#include "game.h"

// INCLUIR O PROOPRIO H
using namespace std;

// 4 menu options:
// play
// options
// last game scores
// best scores


void play() {
    gameSetup();
}

void options() {

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
            {"options",     'o'},
            {"last games",  'l'},
            {"best scores", 'b'},
            {"exit",        'e'},
    };

    bool playing = true;

    while (playing) {
        printf("Please enter a command: \n"
               "Play\n"
               "Options\n"
               "Last Games\n"
               "Best Scores"
               "Exit\n\n"
               "Choose: ");

        string cmd;
        cin >> cmd;

        if (cin.fail()) {
            printf("Input Invalid\n\n");
            cin.ignore(1000, '\n');
            cin.clear();
        } else if (cin.peek() != '\n') {
            printf("Input Invalid\n\n");
            cin.ignore(1000, '\n');
            cin.clear();
        } else {
            switch (cmdToChar[cmd]) {
                case 'p':
                    play();
                    break;
                case 'o' :
                    options();
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