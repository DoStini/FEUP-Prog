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


bool checkEmptyMove(gameData currGame, int player, int house){
    if (currGame.board[player][house] + house > 5){
        return true;
    }
    else{
        return false;
    }
}



int showValidMoves(bool available[]){

    int counter = 0;
    int position;


    cout << "Available options: ";

    for (int i = 0; i < 6; ++i) {
        if (available[i]){
            counter ++;
            cout << i + 1 << " ";
        }
    }
    if(counter == 0){
        return -1; // My definition of invalid
    }
    else{
        while (1){
            bool valid = readInt(position);
            if (valid && available[position-1]){
                break;
            } else{
                cout << "Invalid, re-enter: ";
            }
        }
        return position;
    }
}


bool round(gameData &currGame, int player) {

    bool finalState; // To be able to know if we skip a player or not in gameManager

    int position;
    int LEN = sizeof(currGame.board[player])/sizeof(int);
    int playerPieces = sumArray(currGame.board[player], LEN); // Check if player has no pieces in his side
    bool availableMoves[6];

    if (playerPieces == 0){

        finalState = false;

        cout << currGame.playerNames[player] << " you are out of options, ";
        player = mod(player+1,2); // Skip to the next player
        cout << currGame.playerNames[player] << " you're on." << endl;

        for (int i = 0; i < 6; i ++ ){
            availableMoves[i] = checkEmptyMove(currGame, player, i);
        }

        position = showValidMoves(availableMoves);
        if (position == -1) {
            cout << endl << "There are no moves left! The game has ended..." << endl;
            for (int i = 0; i < 6; ++i) {
                currGame.score[player] += currGame.board[player][i];
                currGame.board[player][i] = 0;
                return finalState;
            }
        }
    }else{

        finalState = true;

        cout << "\nThis is your turn " << currGame.playerNames[player] << "\nPlease enter a position to remove your seeds (1-6): ";

        while(1){
            bool valid = readInt(position);
            if (!valid || position < 1 || position > 6 || currGame.board[player][position-1] == 0){
                cout << "Not valid, re-enter: ";
                continue;
            }
            break;
        }
    }


    int seeds = currGame.board[player][position-1];
    currGame.board[player][position-1] = 0;


    int currField = player;

    int temp = position + seeds - 1;
    bool canConquer = true; // Stays true until the last pieces can be conquered, and so on
    // Can conquer pieces from the last piece sowed until one house doesnt get conquered


    for (int i = position + seeds; i > position; i--){ // LOOP MOVE THE SEEDS reversed
        if(temp > 5) {
            currField = mod(currField + temp/6, 2); // trabalhar com a divisao inteira para saber se roda o jogador
            temp = mod(temp, 6);
        }
        else if(temp < 0) {
            currField = mod(currField + 1, 2);
            temp = 5;
        }
        currGame.board[currField][temp] += 1;


        // Checks if a house can be conquered
        if (canConquer && (currGame.board[currField][temp] == 2 || currGame.board[currField][temp] == 3)){
            currGame.score[player] += currGame.board[currField][temp];
            currGame.board[currField][temp] = 0;
        } else{
            canConquer = false;
        }
        temp--;
    }



    cout << "\n";
    showBoard(currGame);
    return finalState;
}


void win(int player, gameData currGame){
    cout << "\n\nGame ended in " << currGame.rounds << "!" << endl;
    cout << "The winner of the game is " << currGame.playerNames[player] << endl;
}


void gameManager(gameData currGame) {

    // Choose random player to start
    srand(time(NULL));
    int startingPlayer = random()%2; // THIS NOT WORKING, i mean, it actually is, but not very random

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
            currGame.board[pl][i] = 4*pl;
        }
    }

    currGame.score[0] = 0;
    currGame.score[1] = 0;
    currGame.rounds = 0;

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
    showBoard(currGame);
    gameManager(currGame);
}
