#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include "Square.h"
#include "GameState.h"
#include "StartState.h"
#include "GameOverState.h"

class Piece;

/**
 * @brief The Board class represents a chess board and its current state.
 *
 * The board is an 8x8 grid of squares, each of which may contain a chess piece.
 * The class also manages the game state, including whether there are white or
 * black pieces left and the current state of the game.
 */
class Board {
private:
    Square* tab[8][8]; ///< 2D array representing the chess board.
    friend std::ostream& operator<<(std::ostream& os, const Board& board);
    GameState* currentState; ///< Pointer to the current game state.

public:
    bool whitePiecesLeft; ///< Indicates if there are white pieces left on the board.
    bool blackPiecesLeft; ///< Indicates if there are black pieces left on the board.

    /**
     * @brief Default constructor for the Board class.
     */
    Board();

    /**
     * @brief Get the square at the specified coordinates on the board.
     *
     * @param x The x-coordinate of the square.
     * @param y The y-coordinate of the square.
     * @return Pointer to the Square object at the specified coordinates.
     */
    Square* getSquare(int x, int y) const;

    /**
     * @brief Initialize the chess game on the board with pieces in their starting positions.
     */
    void GameCreation();

    /**
     * @brief Update the content of a square on the board with a new chess piece.
     *
     * @param x The x-coordinate of the square to update.
     * @param y The y-coordinate of the square to update.
     * @param piece Pointer to the new chess piece to place on the square.
     */
    void updateSquare(int x, int y, Piece* piece);

    /**
     * @brief Promote a pawn to a queen at the specified square.
     *
     * @param x The x-coordinate of the square containing the pawn to be promoted.
     * @param y The y-coordinate of the square containing the pawn to be promoted.
     * @param piece Pointer to the pawn to be promoted to a queen.
     */
    void promoteQueen(int x, int y, Piece* piece);

    /**
     * @brief Set the current game state to a new state.
     *
     * @param newState Pointer to the new game state to set.
     */
    void setState(GameState* newState);

    /**
     * @brief Check if the game is over and return true if it is.
     *
     * @return True if the game is over, otherwise false.
     */
    bool CheckGameOver();

    /**
     * @brief Display the current state of the board.
     */
    void displayState();

    /**
     * @brief Clear the console and display game setup information.
     *
     * @param name Name of player 1.
     * @param name1 Name of player 2.
     */
    void clearConsole(std::string name, std::string name1);
};

#endif
