#include <iostream>
#include "game.h"
#include "gameMenu.h"
#include "main.h"


using namespace std;



enum state {
    INIT,
    P1,
    P2,
    W1,
    W2,
    T
};


struct gameData {
    int board[12]; // 0 a 5 é do player 1, 6 a 11 é do player 2
    int score[2];
    int rounds;
    string playerNames[2];
};




void showBoard(gameData currGame){

    cout << "\t" << currGame.playerNames[0] << "'s Points: " << currGame.score[0] << endl << endl;
    cout << "1\t2\t3\t4\t5\t6" << endl;
    cout << "----------------------" << endl;
    for (int player = 0; player < 2; player++){
        for (int i = 0; i < 6; i++){
            cout << currGame.board[i + 6 * player] << "\t";
        }
        cout << endl;
    }
    cout << "----------------------" << endl;
    cout << "1\t2\t3\t4\t5\t6" << endl;
    cout << "\n\t" << currGame.playerNames[1] << "'s Points: " << currGame.score[1] << endl;
}


bool round(gameData &currGame, int player) {
    // USE THIS FUNCTION TO ROATE SEEDS

    int position;
    cout << "Please enter a position to remove your seeds (1-6): ";


    while(1){
        bool valid = readInt(position);
        if (!valid || position < 1 || position > 6){
            cout << "Not valid, re-enter: ";
            continue;
        }
        break;
    }

    position = position - 1 + 6 * player;
    int seeds = currGame.board[position + 6*player];
    position -= 1;

    for (int i = position; i > position - seeds; i--){
        if((mod(i, 12)) < 6){
            player = 0;
        }else{
            player = 1;
        }
        currGame.board[5*player + abs(i)] += 1;
    }
    cout << "\n";
}


void gameManager(gameData currGame) {
    enum state currState = P1;

    bool end = false;

    while (!end) {
        switch (currState) {
            case P1:{
                bool status = round(currGame, 0);
                if (status) {
                    currState = P2;
                }
                if(currGame.score[0] >= 25){
                    currState = W1;
                }
                else if(currGame.score[0] == 24 && currGame.score[0] == 24){
                    currState = T;
                }
                break;
            }

            case P2:{
                bool status = round(currGame, 1);
                if (status) {
                    currState = P1;
                }
                if(currGame.score[1] >= 25){
                    currState = W2;
                }
                else if(currGame.score[0] == 24 && currGame.score[1] == 24){
                    currState = T;
                }
                break;
            }

            case W1:{

            }
        }
    }
}



void gameSetup() {

    printf("Setting up...\n");

    struct gameData currGame;

    // Setting starting value in the board
    for (int i = 0; i < 12; i++) {
        currGame.board[i] = 4;
    }
    currGame.score[0] = 0;
    currGame.score[1] = 2;


    // CHOOSING PLAYERS NAMES
    for (int i = 0; i < 2; i++) {
        printf("Please enter player's %d name: ", i + 1);
        bool valid;
        string name;
        while (1) {
            valid = readString(name);
            if (!valid) {
                printf("Invalid, re-enter: ");
                continue;
            }
            currGame.playerNames[i] = name;
            if (currGame.playerNames[(i-1)%2] == currGame.playerNames[i]){
                printf("Cant be same name as the other player, re-enter: ");
                continue;
            }
            break;
        }
    }


    // CHOOSE RANDOM PLAYER TO START

    showBoard(currGame);
    round(currGame, 1);
    showBoard(currGame);
    //gameManager(currGame)

}
