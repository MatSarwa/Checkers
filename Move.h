#ifndef MOVE_H
#define MOVE_H

#include "Player.h"
#include "Pawn.h"
#include "Square.h"

/**
 * @brief The Move class represents a chess move between two squares.
 *
 * This class is responsible for defining a chess move by specifying the starting
 * and ending squares of the move.
 */
class Move {
private:
    Square start; ///< The starting square of the move.
    Square end;   ///< The ending square of the move.

public:
    /**
     * @brief Make a chess move on the board.
     *
     * This function is responsible for applying the specified move to the chess board.
     *
     * @param board The chess board on which the move is to be made.
     * @param white Indicates whether it is a white player's move.
     */
    void makeMove(Board& board, bool white);
};

#endif
