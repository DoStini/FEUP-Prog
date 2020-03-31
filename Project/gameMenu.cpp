#include <iostream>
#include <map>
#include <algorithm>
#include "gameMenu.h"
#include "game.h"
#include "main.h"

// INCLUIR O PROOPRIO H
using namespace std;

// 4 menu options:
// play
// options
// rules
// instructions



void play() {

    /*
     * The function that will start the game, asking if we want a bot or not, and calling the game setup.
     */


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
    clearScreen();
    if (toupper(res) == 'Y'){
        gameSetup(true);
    }
    else{
        gameSetup(false);
    }
}

void instructions() {

    /*
     * Prints out the instructions
     */

    cout << COLORS["MAIN"];
    cout << "\nAt the beggining of each game you can select if you want to play with a bot." << endl;
    cout << "You may also choose the players' colors and names. Note they can't be the same!" << endl;
    cout << "Finally, if both players agree on ending the game press CTRL-Z (on windows) or CTRL-D(on linux)!" << endl << endl;
}

void rules() {

    /*
    * Prints out the rules
    */

    cout << "\nSOWING:" << endl;
    cout << COLORS["MAIN"] << "Players take turns moving the seeds. On a turn, a player chooses one of the six pits under their control.\nThe player removes all seeds from this pit, and distributes them in each pit counter-clockwise from this house, in a process called sowing." << endl << endl;
    cout << COLORS["MAIN_BOLD"] << "CAPTURING:" << endl;
    cout << COLORS["MAIN"]<< "After a turn, if the last seed was placed into an opponent's pit that brought its total to two or three, all the seeds in that house are captured and placed in the player's scoring pit.\nIf the previous to last seed also brought an opponent's pit to two or three, these are captured as well, and so on." << endl << endl;
    cout << COLORS["MAIN_BOLD"] << "EXCEPTION:" << endl;
    cout << COLORS["MAIN"]<< "If an opponent's pits are all empty, the current player must make a move that gives the opponent seeds.\nIf no such move is possible, the current player captures all seeds in their own territory, ending the board game."<< endl << endl;
    cout << COLORS["MAIN_BOLD"]<< "END OF GAME:" << endl;
    cout << COLORS["MAIN"]<< "If a player captures more then halve of all seeds (25 or more), he is a winner.\nIf both players have 24 points, this results in a tie!\nIf the two players agree they entered in an infinite cycle, they can end the game, collecting the seed in each field." << endl << endl << endl;
}


// MUDAR NOME
void run() {

    /*
     * The main function in the game, manages the main menu.
     */


    map<string, char> cmdToChar = { // TO BE USED IN SWITCH CMD, DOESNT ACCEPT STRINGS
            {"play",        'p'},
            {"rules",       'r'},
            {"instructions",'i'},
            {"exit",        'e'},
    };

    bool playing = true;

    while (playing) {
        cout << COLORS["MAIN_BOLD"];

        printf("Please enter a command: \n\n"
               "Play\n"
               "Instructions\n"
               "Rules\n"
               "Exit\n\n"
               "Choose: ");

        string cmd;

        bool valid = readString(cmd);

        if (!valid) {
            cout << "Input invalid, reenter." << endl;
        } else {
            transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
            switch (cmdToChar[cmd]) {
                case 'p':
                    play();
                    break;
                case 'i' :
                    instructions();
                    break;
                case 'r':
                    rules();
                    break;
                case 'e':
                    cout << "Thanks for playing!" << endl;
                    playing = false;
                    break;
                default:
                    cout << "Invalid, please reenter.";
                    break;
            }
        }
    }
}