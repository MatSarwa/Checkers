#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include "Player.h"
#include <cstdlib>

/**
 * @brief The ComputerPlayer class represents a computer player in a chess game.
 *
 * This class is a subclass of the Player class and is responsible for making
 * moves on the chess board automatically as the computer's turn.
 */
class ComputerPlayer : public Player {
public:
    /**
     * @brief Constructor for the ComputerPlayer class.
     *
     * @param whiteside Indicates whether the computer player is playing as the white side.
     */
    ComputerPlayer(bool whiteside);

    /**
     * @brief Make a move on the chess board during the computer player's turn.
     *
     * This function is responsible for selecting and making a move for the computer
     * player on the given chess board.
     *
     * @param board The chess board on which the move is to be made.
     * @param isWhitePlayerTurn Indicates whether it is the white player's turn.
     */
    virtual void makeMove(Board& board, bool isWhitePlayerTurn) override;
};

#endif