#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Board.h"
#include "Piece.h"
#include "Pawn.h"
#include "Square.h"
#include "Queen.h"

/**
 * @brief The Player class represents a player in a chess game.
 *
 * This class defines common attributes and behaviors for players, including
 * whether the player is on the white side, whether they are human or computer-controlled,
 * their name, and the ability to make moves on the chess board.
 */
class Player {

public:
    bool whiteside; ///< Indicates whether the player is on the white side.
    bool humanPlayer; ///< Indicates whether the player is a human player.
    std::string playerName; ///< The name of the player.
    Square start; ///< The starting square for a move.
    Square end; ///< The ending square for a move.

    /**
     * @brief Check if the player is on the white side.
     *
     * @return True if the player is on the white side, otherwise false.
     */
    bool IsWhiteSide();

    /**
     * @brief Check if the player is a human player.
     *
     * @return True if the player is a human player, otherwise false.
     */
    bool IsHumanPlayer();

    /**
     * @brief Set whether the player is a human player.
     *
     * @param human Indicates whether the player is a human player.
     */
    void SetHumanPlayer(bool human);

    /**
     * @brief Set whether the player is on the white side.
     *
     * @param isWhite Indicates whether the player is on the white side.
     */
    void SetWhiteSide(bool isWhite);

    /**
     * @brief Set the name of the player.
     *
     * @param name The name of the player.
     */
    void setName(const std::string& name);

    /**
     * @brief Get the name of the player.
     *
     * @return The name of the player.
     */
    std::string getName() const;

    /**
     * @brief Make a move on the chess board.
     *
     * This is a pure virtual function that must be implemented by subclasses
     * to specify how a player makes a move on the chess board.
     *
     * @param board The chess board on which the move is to be made.
     * @param isWhitePlayerTurn Indicates whether it is the white player's turn.
     */
    virtual void makeMove(Board& board, bool isWhitePlayerTurn) = 0;

    /**
     * @brief Create and set up a player instance based on user input.
     *
     * This function allows the user to choose the player type (human or computer)
     * and set the player's name based on user input.
     *
     * @param playerNumber The number of the player (1 or 2).
     * @param isWhite Indicates whether the player is on the white side.
     * @return A pointer to the created player instance.
     */
    static Player* chooseAndSetNameAndDisplay(int playerNumber, bool isWhite);
};

/**
 * @brief The Human class represents a human player in a chess game.
 */
class Human : public Player {
public:
    /**
     * @brief Constructor for the Human class.
     *
     * @param whiteside Indicates whether the human player is playing as the white side.
     */
    Human(bool whiteside);
};

/**
 * @brief The Computer class represents a computer player in a chess game.
 */
class Computer : public Player {
public:
    /**
     * @brief Constructor for the Computer class.
     *
     * @param whiteside Indicates whether the computer player is playing as the white side.
     */
    Computer(bool whiteside);
};

#endif // PLAYER_H