#ifndef PIECE_H
#define PIECE_H

#include "Board.h"
#include "vector"
#include "Square.h"

class Board;
class Square;

/**
 * @brief The Piece class represents a chess piece.
 *
 * This is an abstract base class that defines the common attributes and behaviors
 * of all chess pieces. Subclasses should implement specific piece types.
 */
class Piece {
private:
    // No private members in the base class.

public:
    bool white; ///< Indicates whether the piece is white.

    /**
     * @brief Constructor for the Piece class.
     *
     * @param isWhite Indicates whether the piece is a white piece.
     */
    Piece(bool isWhite);

    /**
     * @brief Virtual destructor for the Piece class.
     */
    virtual ~Piece();

    /**
     * @brief Check if the piece is white.
     *
     * @return True if the piece is white, otherwise false.
     */
    bool isWhite() const;

    /**
     * @brief Check if the piece can move from the starting square to the ending square.
     *
     * This is a pure virtual function that must be implemented by subclasses
     * to define the movement rules for each specific chess piece.
     *
     * @param board The chess board on which the move is being checked.
     * @param start The starting square of the move.
     * @param end The ending square of the move.
     * @param isWhite Indicates whether the piece is a white piece.
     * @return True if the move is valid for the piece, otherwise false.
     */
    virtual bool canMove(Board& board, Square& start, Square& end, bool isWhite) const = 0;

    /**
     * @brief Determine if any pawn of the specified color can capture on the board.
     *
     * This is a pure virtual function that must be implemented by subclasses
     * to determine if any pawns of the given color can make capturing moves.
     *
     * @param board The chess board to check for capturing moves.
     * @param isWhite Indicates whether the pawns to check are white.
     * @return The number of pawns that can capture on the board.
     */
  
    void setWhite(bool isWhite);

    /**
     * @brief Get the type of the chess piece.
     *
     * This is a pure virtual function that must be implemented by subclasses
     * to return the type of the specific chess piece (e.g., "Pawn").
     *
     * @return A string representing the type of the chess piece.
     */
    virtual std::string getType() const = 0;

    /**
     * @brief Determine the number of capturing moves for the chess piece.
     *
     * This is a pure virtual function that must be implemented by subclasses
     * to determine the number of capturing moves for the specific chess piece.
     *
     * @param board The chess board on which capturing moves are counted.
     * @param start The starting square of the chess piece.
     * @param isWhite Indicates whether the piece is a white piece.
     * @return The number of capturing moves for the piece.
     */
    virtual int countCapturingMoves(Board& board, Square& start, bool isWhite) const = 0;
};

#endif