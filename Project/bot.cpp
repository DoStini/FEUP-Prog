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
            output.push_back(i+1); // Its a position, so it belongs from [1;6]
        }
    }
    return output;
}


// Returns the best move
int getBotMove(gameData currGame, vector<int> availableMoves = {1, 2, 3, 4, 5, 6}){
    vector<int> scores;
    for (int i = 0; i < availableMoves.size(); ++i) {
        gameData copyGame = currGame;
        int points = botAnalyse(copyGame, availableMoves[i]);
        scores.push_back(points);
    }

    vector<int> scorePositions = maxIndices(scores);

    int position = scorePositions[rand()%scorePositions.size()];

    sleep(2);

    return position;
}


