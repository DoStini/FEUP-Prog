//
// Created by andremoreira9 on 17/03/20.
//

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <unistd.h>
#include "game.h"
#include "main.h"


using namespace std;

vector<int> maxIndices(vector<int> v){

    /*
     * @param A vector
     * @return The indexes of the max values of an array
     */

    int biggest = *max_element(v.begin(), v.end());  // Max elements returns a pointer pointing to the max element
    vector<int> output;

    for (int i = 0; i < v.size(); ++i) {
        if(v[i] == biggest){
            output.push_back(i);
        }
    }
    return output;
}




int botAnalyse(gameData currGame, int position, int player = 1) {


    /*
     * A function to analyse a move from a bot to know the points he would get from that move
     *
     * @param currGame - Current game's data
     * @param position - The respective move which is being tested
     * @return the number of points a bot would get if it made that move
     */


    bool finalState;

    int LEN = sizeof(currGame.board[1])/sizeof(int);
    int playerPieces = sumArray(currGame.board[1], LEN);



    int seedsCounter = 0;                               // Counts the number of seeds

    int seeds = currGame.board[player][position-1];     // Gets the number of seeds in the chosen house
    int enemyTempField[6];
    spreadSeeds(currGame, player, position, seeds);

    copy(begin(currGame.board[mod(player+1, 2)]), end(currGame.board[mod(player+1, 2)]), begin(enemyTempField));   // Copies the enemy board to later check the validity


    bool canConquer = true;                             // Stays true until the last pieces can be conquered, and so on
    // Can conquer pieces from the last piece sowed until one house doesnt get conquered
    int temp = position + seeds + seeds/12 - 1;             // seeds/12 will indicate if there was a skip to our initial house and how many
    int currField = player;

    for (int i = 0; i < seeds; ++i) {
        if(temp > 5) {
            currField = mod(currField + temp/6, 2);     // Curr field is changed if the seeds are in the other field.
            temp = mod(temp, 6);                           // currField+1  changes player  temp/6 verifies if temp didnt return to the initial player
        }                                                     // if temp = 7 -> index is 1 of player 2. 7/6=1 (rotates player)
        else if(temp < 0) {                                   // if temp = 12 -> index is 1 of player 1. 12/6=2 (doesnt rotate as 2mod2 = 0)
            currField = mod(currField + 1, 2);
            temp = 5;
        }

        if (currField == player){
            break;
        }

        // Checks if a house can be conquered
        if (currGame.board[currField][temp] == 2
            || currGame.board[currField][temp] == 3)
        {
            seedsCounter += currGame.board[currField][temp];
            currGame.board[currField][temp] = 0;
        } else{
            break;                               // If one of the houses fails to conquer, the next ones wont be conquered as well
        }

        temp--;
    }

    if (sumArray(currGame.board[mod(player+1, 2)], 6) == 0         // Ensures enemy player has not 0 seeds
        && sumArray(currGame.board[player], 6 ) != 0)                           // Ensures the game has not ended
    {
        return 0;
    }

    return seedsCounter;
}



int getBotMove(gameData currGame, vector<int> availableMoves){

    /*
     * A function that runs every possible move and choose the best among them
     *
     * @param currGame - Current game's data
     * @param availableMoves - The respective move which is being tested
     * @return The position that the bot will play
     */

    vector<int> scores;                                 // A vector containing the points from every possible move

    for (int i = 0; i < availableMoves.size(); ++i) {
        gameData copyGame = currGame;
        int points = botAnalyse(copyGame, availableMoves[i]);   // Analyses current move from availableMoves
        scores.push_back(points);
    }

    vector<int> bestScoresIndexes = maxIndices(scores); // Getting the indexes of the best moves so far to apply in availableMoves

    int position = availableMoves[bestScoresIndexes[rand() % bestScoresIndexes.size()]];   // Chooses a random move among the best ones

    sleep(2);                                   // Give some time to let player process what is happening

    return position;
}




