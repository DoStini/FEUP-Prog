//
// Created by andremoreira9 on 17/03/20.
//

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <unistd.h>
#include "game.h"


using namespace std;

vector<int> maxIndices(vector<int> v){
    int biggest = *max_element(v.begin(), v.end());
    vector<int> output;

    for (int i = 0; i < v.size(); ++i) {
        if(v[i] == biggest){
            output.push_back(i);
        }
    }
    return output; // Returnnig the indices of the max values, has to be applied to available moves to take effect
}


// Returns the best move
int getBotMove(gameData currGame, vector<int> availableMoves){
    vector<int> scores;
    for (int i = 0; i < availableMoves.size(); ++i) {
        gameData copyGame = currGame;
        int points = botAnalyse(copyGame, availableMoves[i]);
        scores.push_back(points);
    }

    vector<int> scorePositions = maxIndices(scores);

    int position = availableMoves[scorePositions[rand()%scorePositions.size()]];

    sleep(2); // GIVE SOME TIME TO LET THE PLAYER PROCESS WHAT IS GOING ON

    return position;
}


