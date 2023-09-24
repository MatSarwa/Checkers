#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "Player.h"

/**
 * @brief The HumanPlayer class represents a human player in a chess game.
 *
 * This class is a subclass of the Player class and is responsible for allowing
 * a human player to make moves on the chess board.
 */
class HumanPlayer : public Player {
public:
    /**
     * @brief Constructor for the HumanPlayer class.
     *
     * @param whiteside Indicates whether the human player is playing as the white side.
     */
    HumanPlayer(bool whiteside);

    /**
     * @brief Make a move on the chess board during the human player's turn.
     *
     * This function is responsible for allowing the human player to select and make
     * a move on the given chess board.
     *
     * @param board The chess board on which the move is to be made.
     * @param isWhitePlayerTurn Indicates whether it is the white player's turn.
     */
    virtual void makeMove(Board& board, bool isWhitePlayerTurn) override;

    /**
     * @brief Convert a character coordinate (e.g., 'a', '1') to a numeric coordinate (0-7).
     *
     * This function takes a character coordinate in algebraic notation and converts it
     * to a numeric coordinate suitable for use with the chess board.
     *
     * @param coordinate The character coordinate to convert.
     * @return The numeric coordinate (0-7) corresponding to the character coordinate.
     */
    int convertCoordinate(char coordinate);
};

#endif 