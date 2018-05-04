//
// Created by loten on 30/04/2018.
//

#ifndef ADVANCEDTOPICS2_GAMEMANAGER_H
#define ADVANCEDTOPICS2_GAMEMANAGER_H

#include "Board.h"
#include "FightInfo.h"
#include "GameStatus.h"

int static playerEnumToInt(playerEnum player){
    switch(player){
        case PLAYER_1:
            return 1;
        case PLAYER_2:
            return 2;
        case NO_PLAYER:
            return 0;
        default:
            return -1;
    }
}

string playerEnumToString(playerEnum player);

playerEnum getOpposite(playerEnum player);

string getWinnerString(playerEnum player);

//***********************Game Manager*****************************************************

class GameManager {
private:
    Board board;
    vector<shared_ptr<Piece>> player1Tools;
    vector<shared_ptr<Piece>> player2Tools;
    int player1Score;
    int player2Score;
    playerEnum currentPlayer;
    FightInfoImp fightInfo;
    GameStatus gameStatus;


public:
    /*
     * Set @arg(player) tools according to @arg(commands)
    */
    void setPlayerTools(const vector<PositioningCommand> &commands, playerEnum player);

};


#endif //ADVANCEDTOPICS2_GAMEMANAGER_H
