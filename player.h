#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <stdlib.h>
#include "common.h"
#include "board.h"
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();
    
    Move *doMove(Move *opponentsMove, int msLeft);
    int minimax(Board *board, Side side, int depth, Move *&best_move);
    Side player_side;
    Board *board;
    
    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
