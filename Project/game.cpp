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

    /*
     * Function to show the board
     *
     * @param currGame - Current game's data
     */

    cout << COLORS[currGame.playerColors[0][0]] << "\n\t" << currGame.playerNames[0] << "'s Points: " << currGame.score[0] << endl << endl;
    cout << COLORS["RESET"];
    cout << "6\t5\t4\t3\t2\t1" << endl;
    cout << "----------------------" << endl;
    for (int player = 0; player < 2; player++){
        for (int i = 0; i < 6; i++){
            int nSeeds = currGame.board[player][abs(5*mod(player+1, 2) - i)];             // Invert player's 0 order:        // indexes: 5 4 3 2 1 0
            if (nSeeds == 1 || nSeeds == 2){                                                        // players' 1 order is normal:     // indexes: 0 1 2 3 4 5
                cout << COLORS[currGame.playerColors[player][0]] << nSeeds << "\t";                 // In danger, bold color
                cout << COLORS["RESET"];
            }
            else{
                cout << COLORS[currGame.playerColors[player][1]] << nSeeds << "\t";                 // Not in danger
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


bool checkEmptyMove(gameData currGame, int player, int house){

    /*
    * Function used to ensure the position chosen allows the game to continue.
    * Called when someone has no seeds in their field
    *
    * @param currGame - Current game's data
    * @param player - Current player
    * @param house - Move being checked
    * @return a bool saying the move is valid or not
    */



    if (currGame.board[player][house-1] + house > 6){
        return true;
    }
    else{
        return false;
    }
}



int getValidMove(vector<int> available){


    /*
     * Function used to ensure input player is within the available vector
     *
     * @param available - Available moves to choose from
     */


    int position;

    cout << "Available options: ";

    for (int i = 0; i < available.size(); ++i) {
        cout << available[i] << " ";
    }
    cout << endl;

    while (1){
        bool valid = readInt(position);
        if (valid && find(available.begin(), available.end(), position) != available.end()){ // Find functions returns an iterator, meaning if the iterator returned is not the end of available, there is an occurence of position
            break;                                      // Exits the loop because it got a valid move
        } else{
            cout << "Invalid, re-enter: ";
        }
    }
    return position;
}



void forceEnd(gameData &currGame){


    /*
     * A function called when a game has to end early on:
     *      Due to players deciding game enetered in an infinite cycle
     *      There are no moves left to allow the game to conitnue
     * Collects all the seeds in each field and gives to the owner
     *
     * @param currGame - Current game's data
     */

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 6; ++j) {
            currGame.score[i] += currGame.board[i][j];
            currGame.board[i][j] = 0;
        }
    }
}



bool round(gameData &currGame, int player, bool hasBot = true) {

    /*Manages one round per player
     * @param recieves a reference of the current game data
     * @param player - 0/1 indicating which player is playing
     * @param hasBot - Indicates if there is a bot playing. If there is, it will always be player 1.
     * @return a bool indicating if we can change to the next player or not.
     */

    bool finalState; // To be able to know if we skip a player or not in gameManager

    int position;  // Defining the position chosen by the player
    int LEN = sizeof(currGame.board[player])/sizeof(int);
    int playerPieces = sumArray(currGame.board[player], LEN); // Checks the number of pieces in the current player's side
    vector<int> availableMoves = {};  // A vector storing the possible/ valid moves for the player to make


    cout << endl;


    cout << COLORS["MAIN_BOLD"];


    if (playerPieces == 0){

        /*
         * Current player is out of options to player
         * The player will change
         */

        finalState = false;  // Because we are already changing player in this section, currState will stay as the player who had no options to play

        cout << currGame.playerNames[player] << " you are out of options, ";
        player = mod(player+1,2); // Currently skipping to the next player
        cout << currGame.playerNames[player] << " you're on." << endl;

        for (int i = 1; i < 7; i++){
            if (checkEmptyMove(currGame, player, i)){
                availableMoves.push_back(i);     // Checking available moves that allow other player to keep playing
            }
        }

        if (availableMoves.size() == 0){
            cout << endl << "There are no moves left! The game has ended..." << endl;
            forceEnd(currGame);
            return finalState;
        }

        else if (hasBot && player == 1){    // If a bot is playing, can only be second player.
            cout << endl << "Bot " << currGame.playerNames[1] << " is choosing a position: " << flush;
            position = getBotMove(currGame, availableMoves);   // Get a seed position, chosen by the bot
            cout << position;
        }
        else{   // Get a seed position, chosen by the human player
            position = getValidMove(availableMoves);
        }

    }else {

        finalState = true;

        if (hasBot && player == 1) {
            cout << endl << "Bot " << currGame.playerNames[1] << " is choosing a position: " << flush;
            for (int i = 1; i < 7; ++i) {
                if (currGame.board[1][i-1] != 0){
                    availableMoves.push_back(i);    // Checks the positions that aren't zero (You cant choose an empty house)
                }
            }
            position = getBotMove(currGame, availableMoves);
            cout << position;
        }
        else {   // If there is no bot, human player will get prompted to give an input
            cout << "\nThis is your turn " << currGame.playerNames[player]
                 << "\nPlease enter a position to remove your seeds (1-6): ";
            while (1) {
                bool valid = readInt(position);
                if (position == ENDGAME){    // End game is defined to end game, and is triggered when CTRL-D is pressed
                    cout << endl << "You decided to end the game..." << endl;
                    forceEnd(currGame);
                    return false;
                }
                else if (!valid || position < 1 || position > 6 || currGame.board[player][position - 1] == 0) { // Checks if the position is within the board and if it not zero
                    cout << "Not valid, re-enter: ";
                    continue;
                }
                break;
            }
        }
    }

    /*
     * Since position is an integer related to the house number (1 -> 6), the respective index of the board is position-1.
     */


    int seeds = currGame.board[player][position-1];     // Gets the number of seeds in the chosen house
    currGame.board[player][position-1] = 0;             // Removes the seeds from the house

    int currField = player;                             // Curr field refers to the player where we are putting seeds

    int temp = position + seeds - 1;                    // Temp refers to the last house and will be used as an index to access players' houses
    bool canConquer = true;                             // Stays true until the last pieces can be conquered, and so on
                                                        // Can conquer pieces from the last piece sowed until one house doesnt get conquered

    for (int i = position + seeds; i > position; i--){
        if(temp > 5) {
            currField = mod(currField + temp/6, 2);     // Curr field is changed if the seeds are in the other field.
            temp = mod(temp, 6);                           // currField+1  changes player  temp/6 verifies if temp didnt return to the initial player
        }                                                     // if temp = 7 -> index is 1 of player 2. 7/6=1 (rotates player)
        else if(temp < 0) {                                   // if temp = 12 -> index is 1 of player 1. 12/6=2 (doesnt rotate as 2mod2 = 0)
            currField = mod(currField + 1, 2);
            temp = 5;
        }
        currGame.board[currField][temp] += 1;


        // Checks if a house can be conquered
        if (canConquer
        && player != currField                          // Not able to conquer own seeds
        && (currGame.board[currField][temp] == 2
        || currGame.board[currField][temp] == 3)
        ){
            currGame.score[player] += currGame.board[currField][temp];
            currGame.board[currField][temp] = 0;
        } else{
            canConquer = false;                         // If one of the houses fails to conquer, the next ones wont be conquered as well
        }
        temp--;
    }



    cout << "\n";
    showBoard(currGame);
    currGame.rounds++;
    return finalState;
}




void win(gameData currGame, int player){

    /*
    * A function to mark the end of the game with a blinking text
    *
    * @param currGame - Current game's data
    * @param player - The player who won
 */

    cout << COLORS[currGame.playerColors[player][0]];

    cout << "\n\nGame ended in " << currGame.rounds << " rounds!" << endl;
    sleep(2);
    for (int i = 0; i < 4; i++) {                       // Blinking win text
        clearScreen();
        sleep(1);
        cout << "The winner of the game is " << currGame.playerNames[player] << " with " << currGame.score[player] << " points!"<<  endl;
        sleep(1);
    }
    sleep(2);
    clearScreen();
}

void tie(gameData currGame){

    /*
    * A function to mark the end of the game with a blinking text
    *
    * @param currGame - Current game's data
 */


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

    /*
    * A function to manage the game, states of the game, and giving the game an end.
    *
    * @param currGame - Current game's data
    * @param hasBot - If a bot is playing or not
    */


    cout << COLORS["MAIN_BOLD"];


    int startingPlayer = random()%2;                // CHoosing a random player to start

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
                bool status = round(currGame, 0);  // Round function returns if the player will be skipped or not
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


    for (int pl = 0; pl < 2; pl++){                     // Setting starting value in the board
        for (int i = 0; i < 6; i++) {
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
        while (1) {                                     // Just a basic loop to ensure user input is valid
            valid = readString(name);
            if (!valid) {
                printf("Invalid, re-enter: ");
                continue;
            }
            currGame.playerNames[i] = name;
            if (currGame.playerNames[mod(i+1,2)] == currGame.playerNames[i]){   // Checks if the other player has the same name
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

        while (1) {                                     // Just a basic loop to ensure user input is valid
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
    showBoard(currGame);                                // Shows the first board
    gameManager(currGame, hasBot);                      // Starts the game
}
