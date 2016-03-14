#include "player.h"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
	player_side = side;
	board = new Board();
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/**
Returns the maximal score of the board, and modifies best_move to contain 
the move that will reach that score. (best_move is dynamically allocated; 
please free with delete.) Uses minimax of the specified depth, where the
to-be-optimized player is on the specified side. 
If depth = 0 or there are no legal moves, the board's heuristic score is 
returned, and best_move is NULL and does NOT need to be deleted.
*/
int Player::minimax(Board *board, Side side, int depth, Move *&best_move) {
    best_move = NULL;
    
    if (depth == 0)
    {
        return board->score(side);
    }

    int best_score = -1000000;
    int new_score;
    Move *new_move, *temp;
    Board *new_board;
    
    Side otherSide = side == BLACK ? WHITE : BLACK;
    
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            new_move = new Move(i, j);
            new_board = board->doLegalMove(new_move, side);
            
            if (new_board != NULL) {
                new_score = -minimax(new_board, otherSide, depth - 1, temp);
                if (temp != NULL) {
                    delete temp;
                }

                if (new_score > best_score)
					{ 
                    best_score = new_score;
                    if (best_move != NULL)
                    {
                        delete best_move;
                    }
                    best_move = new_move;
					}    
                else
				{
                    delete new_move;
                }
            }
            else
			{
				delete new_move;
			}
            
            delete new_board;
        }
    }
    
    if (best_move == NULL) { 
        if (this->testingMinimax)
        {
			return board->simple_score(side);
		}
		else
		{
			return board->score(side);
		}
    }
    
    return best_score;
}


/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be NULL.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return NULL.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {        
    Side opponent_side = (player_side == BLACK) ? WHITE : BLACK;
	board->doMove(opponentsMove, opponent_side);
    
    Move *best_move;
    if (this->testingMinimax)
    {
		minimax(board, player_side, 2, best_move); 
	}
	else
	{
		minimax(board, player_side, 5, best_move);
	}
    board->doMove(best_move, player_side);
    
    return best_move;
}
