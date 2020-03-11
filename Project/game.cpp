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
    int board[2][6];
    int score[2];
    int rounds;
    string playerNames[2];
};




void showBoard(gameData currGame){

    cout << "\n\t" << currGame.playerNames[0] << "'s Points: " << currGame.score[0] << endl << endl;
    cout << "6\t5\t4\t3\t2\t1" << endl;
    cout << "----------------------" << endl;
    for (int player = 0; player < 2; player++){
        for (int i = 0; i < 6; i++){
            cout << currGame.board[player][abs(5*mod(player+1, 2) - i)] << "\t"; // Invert player's 0 order:        // 5 4 3 2 1 0
        }                                                                                                                     // 0 1 2 3 4 5
        cout << endl;
    }
    cout << "----------------------" << endl;
    cout << "1\t2\t3\t4\t5\t6" << endl;
    cout << "\n\t" << currGame.playerNames[1] << "'s Points: " << currGame.score[1] << endl;
}


bool round(gameData &currGame, int player) {
    // USE THIS FUNCTION TO ROTATE SEEDS

    int position;
    cout << "\nThis is your turn " << currGame.playerNames[player] << "\nPlease enter a position to remove your seeds (1-6): ";

    while(1){
        bool valid = readInt(position);
        if (!valid || position < 1 || position > 6){
            cout << "Not valid, re-enter: ";
            continue;
        }
        break;
    }

    int seeds = currGame.board[player][position-1];
    currGame.board[player][position-1] = 0;

    int temp = position;
    bool canConquer = false; // When the seeds are on the other
    for (int i = position; i < position + seeds; i++){
        if(temp > 5) {
            canConquer = true;
            player = mod(player + 1, 2);
            temp = 0;
        }
        currGame.board[player][temp] += 1;
        if (currGame.board[player][temp] == 2 || currGame.board[player][temp] == 3){ // MISSING HERE A CAN CONQUER
            currGame.score[mod(player + 1, 2)] += currGame.board[player][temp]; // Add points to the other player
            currGame.board[player][temp] = 0;
        }
        temp++;
    }
    cout << "\n";
    showBoard(currGame);
    return true;
}


void win(int player, gameData currGame){
    cout << "\n\nGame ended in " << currGame.rounds << "!" << endl;
    cout << "The winner of the game is " << currGame.playerNames[player] << endl;
}


void gameManager(gameData currGame) {

    // Choose random player to start
    srand(time(NULL));
    int startingPlayer = random()%2;

    cout << "\nPlayer starting is " << currGame.playerNames[startingPlayer] << ". Good luck!" << endl;

    enum state currState;
    if (startingPlayer == 0){
        currState = P1;
    }
    else{
        currState = P2;
    }

    bool end = false;

    while (!end) {
        switch (currState) {
            case P1:{
                bool status = round(currGame, 0);
                if (status) { // ALTERAR ISTO PARA MAIS ABAIXO PARA SER MAIS EFICIENTE
                    currState = P2;
                }
                if(currGame.score[0] >= 25){
                    currState = W1;
                }
                else if(currGame.score[0] == 24 && currGame.score[1] == 24){
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
                win(0, currGame);
            }

            case W2:{
                win(1, currGame);
            }
        }
    }
}



void gameSetup() {

    printf("Setting up...\n");

    struct gameData currGame;

    // Setting starting value in the board
    for (int pl = 0; pl < 2; pl++){
        for (int i = 0; i < 6; i++) {
            currGame.board[pl][i] = 4;
        }
    }

    currGame.score[0] = 0;
    currGame.score[1] = 0;


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
            if (currGame.playerNames[mod(i-1,2)] == currGame.playerNames[i]){
                printf("Cant be same name as the other player, re-enter: ");
                continue;
            }
            break;
        }
    }


    // CHOOSE RANDOM PLAYER TO START

    showBoard(currGame);
    gameManager(currGame);
}
