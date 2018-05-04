#include "Parser.h"

unique_ptr<PiecePosition> Parser::parsePiecePosition(string commandLine) {
    if(commandLine.empty()) return move(make_unique<PiecePositionImp>(INVALID_POINT,INVALID_POINT,'#','#'));
    char *str = const_cast<char*>(commandLine.c_str());
    char *tokens[5];
    const char delim[] = " \t\n\r";

    tokens[0] = strtok(str, delim);
    for (int i = 1; i < 5; i++)
        tokens[i] = strtok(NULL, delim);

    //valid positioning command
    if (isCharArrValidToolType(tokens[0]) &&
        isNumInRange(tokens[1], 1, M) &&
        isNumInRange(tokens[2], 1, N) &&
        tokens[3]==NULL){

            char piece = *(tokens[0]);
            int srcX = atoi(tokens[1]), srcY = atoi(tokens[2]);
            return move(make_unique<PiecePositionImp>(srcX, srcY, piece, NO_JOKER_CHANGE_SYMBOL));
    }

    else if(tokens[0]!=NULL && !strcmp(tokens[0], "J") &&
            isNumInRange(tokens[1], 1, M) &&
            isNumInRange(tokens[2], 1, N) &&
            isCharArrValidJokerToolType(tokens[3]) &&
            tokens[4]==NULL){

                char jokerRep = *(tokens[3]);
                int srcX = atoi(tokens[1]), srcY = atoi(tokens[2]);
                return move(make_unique<PiecePositionImp>(srcX, srcY, 'J' ,jokerRep));
    }
    else return move(make_unique<PiecePositionImp>(INVALID_POINT,INVALID_POINT,INVALID_SYMBOL,INVALID_SYMBOL));
}

commandType Parser::parseMoveCommand(string commandLine, vector<Move>& moves, vector<JokerChange>& jokerChanges){
    vector<commandType> steps;
    int fromX, fromY, toX, toY, jokerX, jokerY;
    char new_rep;
    if(commandLine.empty()) {
//        ((PlayerAlgorithmImp &)po).move = MoveImp(0, 0, 0, 0);
//        steps = {INVALID_MOVE_COMMAND};
        moves.push_back(MoveImp(INVALID_POINT,INVALID_POINT,INVALID_POINT,INVALID_POINT));
        jokerChanges.push_back(JokerChangeImp(0,0,'#'));
        return INVALID_MOVE_COMMAND;
    }

    char *str = const_cast<char*>(commandLine.c_str());
    char *tokens[9];
    const char delim[] = " \t\n\r";


    tokens[0] = strtok(str, delim);
    for (int i = 1; i < 9; i++) {tokens[i] = strtok(NULL, delim);}

    //9th token  - INVALID_MOVE_COMMAND command
    if (tokens[8] != NULL || tokens[0] == NULL) {
//        steps = {INVALID_MOVE_COMMAND};
        return INVALID_MOVE_COMMAND;
    }
    //first 4 arguments are not valid numbers in range
    if (!isNumInRange(tokens[0], 1, M) || !isNumInRange(tokens[1], 1, N) || !isNumInRange(tokens[2], 1, M) ||
        !isNumInRange(tokens[3], 1, N)) {
//        steps = {INVALID_MOVE_COMMAND};
        return INVALID_MOVE_COMMAND;
    }
    //There is a 5th argument (joker command)
    else if (tokens[4] != NULL) {
        if (strcmp(tokens[4], "J:") || !isNumInRange(tokens[5], 1, M) || !isNumInRange(tokens[6], 1, N) ||
            !isCharArrValidJokerToolType(tokens[7]) || tokens[8]!=NULL) {
//            steps = {INVALID_MOVE_COMMAND};
            return INVALID_MOVE_COMMAND;
        }
        //valid joker command
        else {
            steps = {MOVE_COMMAND, JOKER_COMMAND};
            fromX = atoi(tokens[0]), fromY = atoi(tokens[1]), toX = atoi(tokens[2]), toY = atoi(tokens[3]);
            jokerX = atoi(tokens[5]), jokerY = atoi(tokens[6]);
            new_rep = *(tokens[7]);
            return INVALID_MOVE_COMMAND;
        }
    }
    //valid move command, no joker command that follows
    else {
        steps = {MOVE_COMMAND};
        fromX = atoi(tokens[0]), fromY = atoi(tokens[1]), toX = atoi(tokens[2]), toY = atoi(tokens[3]);
        return INVALID_MOVE_COMMAND;
    }
}