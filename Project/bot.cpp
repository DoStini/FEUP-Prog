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


int botAnalyse(gameData currGame, int position);

// Returns the best move
int getBotMove(gameData currGame, vector<int> availableMoves){

    /*
     * A function to run every possible move and choose the best among them
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



int botAnalyse(gameData currGame, int position) {


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


    int seeds = currGame.board[1][position-1];
    currGame.board[1][position-1] = 0;


    int currField = 1;

    int temp = position + seeds - 1;
    bool canConquer = true;

    int seedsCounter = 0;

    for (int i = position + seeds; i > position; i--){
        if(temp > 5) {
            currField = mod(currField + temp/6, 2);
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


