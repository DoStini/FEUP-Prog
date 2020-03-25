#include <iostream>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include "game.h"
#include "gameMenu.h"
#include "main.h"
#include "bot.h"


using namespace std;




enum state {
    INIT,
    P1,
    P2,
    W1,
    W2,
    T
};




void showBoard(gameData currGame){

    cout << COLORS[currGame.playerColors[0][0]] << "\n\t" << currGame.playerNames[0] << "'s Points: " << currGame.score[0] << endl << endl;
    cout << COLORS["RESET"];
    cout << "6\t5\t4\t3\t2\t1" << endl;
    cout << "----------------------" << endl;
    for (int player = 0; player < 2; player++){
        for (int i = 0; i < 6; i++){
            int nSeeds = currGame.board[player][abs(5*mod(player+1, 2) - i)];             // Invert player's 0 order:        // 5 4 3 2 1 0
            if (nSeeds == 1 || nSeeds == 2){                                                                                           // 0 1 2 3 4 5
                cout << COLORS[currGame.playerColors[player][0]] << nSeeds << "\t"; // In danger
                cout << COLORS["RESET"];
            }
            else{
                cout << COLORS[currGame.playerColors[player][1]] << nSeeds << "\t"; // Not in danger
                cout << COLORS["RESET"];
            }
        }
        cout << endl;
    }
    cout << "----------------------" << endl;
    cout << "1\t2\t3\t4\t5\t6" << endl;
    cout << COLORS[currGame.playerColors[1][0]] << "\n\t" << currGame.playerNames[1] << "'s Points: " << currGame.score[1] << endl;
    cout << COLORS["RESET"];
}


bool checkEmptyMove(gameData currGame, int player, int house){ // Checks if a move is valid
    if (currGame.board[player][house-1] + house > 6){
        return true;
    }
    else{
        return false;
    }
}



int getValidMove(vector<int> available){

    int position;

    cout << "Available options: ";

    for (int i = 0; i < available.size(); ++i) {
        cout << available[i] << " ";
    }
    cout << endl;

    while (1){
        bool valid = readInt(position); // PROGRAM BREAKS IF I ENTER LETTER
        if (valid && find(available.begin(), available.end(), position) != available.end()){ // find retorna um iterador, se não houver elemento igual, vai retornar o final do iterador.
            break;
        } else{
            cout << "Invalid, re-enter: ";
        }
    }
    return position;
}



void forceEnd(gameData &currGame){
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 6; ++j) {
            currGame.score[i] += currGame.board[i][j];
            currGame.board[i][j] = 0;
        }
    }
}



bool round(gameData &currGame, int player, bool hasBot = true) {
    bool finalState; // To be able to know if we skip a player or not in gameManager

    int position;
    int LEN = sizeof(currGame.board[player])/sizeof(int);
    int playerPieces = sumArray(currGame.board[player], LEN); // Check if player has no pieces in his side
    vector<int> availableMoves = {};


    cout << endl << endl;


    cout << COLORS["MAIN_BOLD"];


    if (playerPieces == 0){

        finalState = false;

        cout << currGame.playerNames[player] << " you are out of options, ";
        player = mod(player+1,2); // Skip to the next player
        cout << currGame.playerNames[player] << " you're on." << endl;

        for (int i = 1; i < 7; i++){
            if (checkEmptyMove(currGame, player, i)){ // changed this and
                availableMoves.push_back(i);
            }
        }

        if (availableMoves.size() == 0){
            cout << endl << "There are no moves left! The game has ended..." << endl;
            forceEnd(currGame);
            return finalState;
        }

        if (hasBot && player == 1){
            cout << endl << "Bot " << currGame.playerNames[1] << " is choosing a position: " << flush;
            position = getBotMove(currGame, availableMoves);
            cout << position;
        }
        else{
            position = getValidMove(availableMoves);
        }

    }else {

        finalState = true;


        if (hasBot && player == 1) {
            cout << endl << "Bot " << currGame.playerNames[1] << " is choosing a position: " << flush;
            for (int i = 1; i < 7; ++i) {
                if (currGame.board[1][i-1] != 0){
                    availableMoves.push_back(i);
                }
            }
            position = getBotMove(currGame, availableMoves);
            cout << position;
        }
        else {
            cout << "\nThis is your turn " << currGame.playerNames[player]
                 << "\nPlease enter a position to remove your seeds (1-6): ";
            while (1) {
                bool valid = readInt(position);
                if (position == ENDGAME){
                    cout << endl << "You decided to end the game..." << endl;
                    forceEnd(currGame);
                    return false;
                }
                if (!valid || position < 1 || position > 6 || currGame.board[player][position - 1] == 0) {
                    cout << "Not valid, re-enter: ";
                    continue;
                }
                break;
            }
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
        if (canConquer
        && player != currField
        && (currGame.board[currField][temp] == 2
        || currGame.board[currField][temp] == 3)){
            currGame.score[player] += currGame.board[currField][temp];
            currGame.board[currField][temp] = 0;
        } else{
            canConquer = false;
        }
        temp--;
    }



    cout << "\n";
    showBoard(currGame);
    currGame.rounds++;
    return finalState;
}


int botAnalyse(gameData &currGame, int position) {
    bool finalState; // To be able to know if we skip a player or not in gameManager

    int LEN = sizeof(currGame.board[1])/sizeof(int);
    int playerPieces = sumArray(currGame.board[1], LEN); // Check if player has no pieces in his side


    int seeds = currGame.board[1][position-1];
    currGame.board[1][position-1] = 0;


    int currField = 1;

    int temp = position + seeds - 1;
    bool canConquer = true; // Stays true until the last pieces can be conquered, and so on
    // Can conquer pieces from the last piece sowed until one house doesnt get conquered

    int seedsCounter = 0;

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
        if (canConquer
            && currField != 1
            && (currGame.board[currField][temp] == 2
                || currGame.board[currField][temp] == 3))
        {
            seedsCounter += currGame.board[currField][temp];
            currGame.board[currField][temp] = 0;
        } else{
            canConquer = false;
        }
        temp--;
    }

    return seedsCounter;
}


void win(int player, gameData currGame){
    cout << COLORS[currGame.playerColors[player][0]];
    cout << "\n\nGame ended in " << currGame.rounds << " rounds!" << endl;
    sleep(2);
    // Blinking win text
    for (int i = 0; i < 4; i++) {
        clearScreen();
        sleep(1);
        cout << "The winner of the game is " << currGame.playerNames[player] << " with " << currGame.score[player] << " points!"<<  endl;
        sleep(1);
    }
    sleep(2);
    clearScreen();
}

void tie(gameData currGame){
    // Blinking win text
    cout << "\n\nGame ended in " << currGame.rounds << " rounds!" << endl;
    sleep(2);
    // Blinking win text
    for (int i = 0; i < 4; i++) {
        clearScreen();
        sleep(1);
        cout << "This long battle resulted in a tie!" << endl;
        sleep(1);
    }
    sleep(2);
    clearScreen();

}

void gameManager(gameData currGame, bool hasBot) {

    cout << COLORS["MAIN_BOLD"];

    // Choose random player to start
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
                cout << COLORS["MAIN_BOLD"];
                bool status = round(currGame, 0);
                if (status) {
                    currState = P2;
                }
                if(currGame.score[0] >= 25){
                    currState = W1;
                }
                else if(currGame.score[1] >= 25){
                    currState = W2;
                }
                else if(currGame.score[0] == 24 && currGame.score[1] == 24){
                    currState = T;
                }
                break;
            }

            case P2:{
                bool status = round(currGame, 1, hasBot);
                if (status) {
                    currState = P1;
                }
                if(currGame.score[0] >= 25){
                    currState = W1;
                }
                else if(currGame.score[1] >= 25){
                    currState = W2;
                }
                else if(currGame.score[0] == 24 && currGame.score[1] == 24){
                    currState = T;
                }
                break;
            }

            case W1:{
                win(0, currGame);
                end = true;
                break;
            }

            case W2:{
                win(1, currGame);
                end = true;
                break;
            }

            case T:{
                tie(currGame);
                end = true;
                break;
            }
        }
    }
}



void gameSetup(bool hasBot) {
    cout << COLORS["MAIN_BOLD"];
    cout << "Setting up..." << endl;

    struct gameData currGame;

    // Setting starting value in the board
    for (int pl = 0; pl < 2; pl++){
        for (int i = 0; i < 6; i++) {
            //currGame.board[pl][i] =  pl == 1 ? 4 : 1;
            currGame.board[pl][i] = 4;
        }
    }

    currGame.score[0] = 0;
    currGame.score[1] = 0;
    currGame.rounds = 0;

    // CHOOSING PLAYERS NAMES
    for (int i = 0; i < 2; i++) {
        cout << COLORS["MAIN_BOLD"];
        cout << "Please enter player's " << i+1 << " name: " << COLORS["MAIN"];
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

    for (int i = 0; i < 2; i++) {
        cout << COLORS["MAIN_BOLD"];
        cout << endl;
        cout << "Available colors: " << COLORS["BOLD_RED"] << "red" << COLORS["MAIN_BOLD"] << ", " << COLORS["BOLD_YELLOW"] << "yellow" << COLORS["MAIN_BOLD"] << "," << COLORS["BLUE"] << "blue" << COLORS["MAIN_BOLD"] << "." << endl;
        cout << "Please enter " << currGame.playerNames[i] << "'s color: " << COLORS["MAIN_BOLD"];
        bool valid;
        string color;
        while (1) {
            valid = readString(color);
            transform(color.begin(), color.end(), color.begin(), ::toupper);
            if (!valid || (color != "RED" && color != "YELLOW" && color != "BLUE")) {
                printf("Invalid, re-enter: ");
                continue;
            }
            currGame.playerColors[i][0] = "BOLD_" + color;
            currGame.playerColors[i][1] = color;
            if (currGame.playerColors[mod(i-1,2)][1] == currGame.playerColors[i][1]){
                printf("Cant be same color as the other player, re-enter: ");
                continue;
            }
            break;
        }
    }
    cout << COLORS["MAIN_BOLD"];
    showBoard(currGame);
    gameManager(currGame, hasBot);
}
