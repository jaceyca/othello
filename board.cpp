#include "board.h"
#include <iostream>
using namespace std;

/*
 * Make a standard 8x8 othello board and initialize it to the standard setup.
 */
Board::Board() {
    taken.set(3 + 8 * 3);
    taken.set(3 + 8 * 4);
    taken.set(4 + 8 * 3);
    taken.set(4 + 8 * 4);
    black.set(4 + 8 * 3);
    black.set(3 + 8 * 4);
}

/*
 * Destructor for the board.
 */
Board::~Board() {
}

/**
 * Used values from https://github.com/kartikkukreja/blog-codes/blob/master/src/Heuristic%20Function%20for%20Reversi%20%28Othello%29.cpp
 */
 
const int Board::heuristic_values[64] =
    {20,-3,11, 8, 8,11,-3,20,
     -3,-7,-4, 1, 1,-4,-7,-3,
     11,-4, 2, 2, 2, 2,-4,11,
      8, 1, 2,-3,-3, 2, 1, 8,
      8, 1, 2,-3,-3, 2, 1, 8,
     11,-4, 2, 2, 2, 2,-4,11,
     -3,-7,-4, 1, 1,-4,-7,-3,
     20,-3,11, 8, 8,11,-3,20,};


/**
 * Returns a copy of this board.
 */
Board *Board::copy() {
    Board *newBoard = new Board();
    newBoard->black = black;
    newBoard->taken = taken;
    return newBoard;
}

/**
Returns whether (x, y) is occupied.
*/
bool Board::occupied(int x, int y) {
    return taken[x + 8*y];
}

/**
Returns whether (x, y) is occupied by the specified side.
*/
bool Board::get(Side side, int x, int y) {
    return occupied(x, y) && (black[x + 8*y] == (side == BLACK));
}

/**
Sets position (x, y) to be occupied by the specified side.
*/
void Board::set(Side side, int x, int y) {
    taken.set(x + 8*y);
    black.set(x + 8*y, side == BLACK);
}

/**
Flip a single piece at the specified position. Assumes the position is
occupied; i.e. there is something to flip there.
*/
void Board::flip(int x, int y) {
    black.flip(x + 8*y);
}

/**
Returns whether (x, y) is on the board.
*/
bool Board::onBoard(int x, int y) {
    return(0 <= x && x < 8 && 0 <= y && y < 8);
}



/**
Updates the board to reflect the specified move. Assumes the move is valid.
If the move is NULL, do not update the board.
*/
void Board::doMove(Move *m, Side side) {
    // A NULL move means pass.
    if (m == NULL) return;

    int X = m->getX();
    int Y = m->getY();
    Side other = (side == BLACK) ? WHITE : BLACK;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dy == 0 && dx == 0) continue;

            int x = X;
            int y = Y;
            do {
                x += dx;
                y += dy;
            } while (onBoard(x, y) && get(other, x, y));

            if (onBoard(x, y) && get(side, x, y)) {
                x = X;
                y = Y;
                x += dx;
                y += dy;
                while (onBoard(x, y) && get(other, x, y)) {
                    set(side, x, y);
                    x += dx;
                    y += dy;
                }
            }
        }
    }
    set(side, X, Y);
}

Board *Board::doLegalMove(Move *m, Side side) {
    int X = m->getX();
    int Y = m->getY();

    if (occupied(X, Y))
    {
		return NULL;
	}
	
    Board *newBoard = NULL;

    Side other = (side == BLACK) ? WHITE : BLACK;
    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            if (dy == 0 && dx == 0) 
            {
				continue;
			}
            int x = X + dx;
            int y = Y + dy;
            if (onBoard(x, y) && get(other, x, y))
            {
                do
                {
                    x += dx;
                    y += dy;
                } while (onBoard(x, y) && get(other, x, y));

                if (onBoard(x, y) && get(side, x, y))
                {
                    if (newBoard == NULL)
                    {
                        newBoard = this->copy();
                    }

                    for (int i = X + dx, j = Y + dy;
                        i != x || j != y;
                        i += dx, j += dy)
                        {
                        newBoard->flip(i, j);
						}
                }
            }
        }
    }

    if (newBoard != NULL)
    {
        newBoard->set(side, X, Y);

    }
    return newBoard;
}

/**
Calculates the score, from the perspective of the specified side.
(Squares occupied by the same side as "side" contribute positively;
those occupied by the opposite side contribute negatively.)
*/
int Board::score(Side side) {
    int output = 0;
    for (int i = 0; i < 64; i++)
    {
        if (taken[i])
        {
            if (black[i] == (side == BLACK))
            {
               output += heuristic_values[i];
            } else
            {
               output -= heuristic_values[i];
            }
        }
    }
    return output;
}


/**
 * Simple score calculation, using this formula:
 * board position score = (# stones you have) - (# stones your opponent has)
 */ 
int Board::simple_score(Side side){
	int output = 0;
    for (int i = 0; i < 64; i++)
    {
        if (taken[i])
        {
            if (black[i] == (side == BLACK))
            {
                output += 1;
            } else
            {
                output -= 1;
            }
        }
    }
    return output;
}

/*
 * Current count of given side's stones.
 */
int Board::count(Side side) {
    return (side == BLACK) ? countBlack() : countWhite();
}

/*
 * Current count of black stones.
 */
int Board::countBlack() {
    return black.count();
}

/*
 * Current count of white stones.
 */
int Board::countWhite() {
    return taken.count() - black.count();
}

/*
 * Sets the board state given an 8x8 char array where 'w' indicates a white
 * piece and 'b' indicates a black piece. Mainly for testing purposes.
 */
void Board::setBoard(char data[]) {
    taken.reset();
    black.reset();
    for (int i = 0; i < 64; i++)
    {
        if (data[i] == 'b')
        {
            taken.set(i);
            black.set(i);
        } 
        if (data[i] == 'w')
        {
            taken.set(i);
        }
    }
}

void Board::printboard()
{
	for (int j = 0; j < 8; j++)
	{
        for (int i = 0; i < 8; i++)
        {
            if (!this->occupied(i, j))
            {
				cerr << "0 ";
			}
			else if (this->get(WHITE, i, j))
			{
				cerr << "W ";
			}
			else if (this->get(BLACK, i, j))
			{
				cerr << "B ";
			}
        }
        cerr << endl;
    }
    cerr << endl;
}
