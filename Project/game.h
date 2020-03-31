//
// Created by andremoreira9 on 10/03/20.
//
#include <string>
using namespace std;

#ifndef PROJECT_GAME_H
#define PROJECT_GAME_H

#define ENDGAME 10

struct gameData {
    int board[2][6];
    int score[2];
    string playerColors[2][2];
    string playerNames[2];
    int rounds;
};


void gameSetup(bool hasBot);
bool round(gameData &currGame, int player, bool hasBot);
void spreadSeeds(gameData &currGame, int player, int position, int seeds);

#endif //PROJECT_GAME_H
