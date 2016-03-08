#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.h"
#include "board.h"
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();
    
    Board *board;
    Move *doMove(Move *opponentsMove, int msLeft);
	Move *randomMove();
    int score(Board * b, Side side);
    Side player_side;
    Side opponent_side;
    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
