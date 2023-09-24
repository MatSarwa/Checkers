#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"  
#include "Board.h"  
#include "Square.h" 

class Board;
class Square;

/**
 * @brief The Queen class represents a queen chess piece.
 *
 * This class is a subclass of the Piece class and defines the behavior and rules
 * specific to the queen piece in chess.
 */
class Queen : public Piece {
public:
    /**
     * @brief Constructor for the Queen class.
     *
     * @param isWhite Indicates whether the queen is a white piece.
     */
    Queen(bool isWhite);

    /**
     * @brief Check if the queen can move from the starting square to the ending square.
     *
     * @param board The chess board on which the move is being checked.
     * @param start The starting square of the move.
     * @param end The ending square of the move.
     * @param isWhite Indicates whether the queen is a white piece.
     * @return True if the move is valid for the queen, otherwise false.
     */
    bool canMove(Board& board, Square& start, Square& end, bool isWhite) const override;

    /**
     * @brief Get the type of the chess piece.
     *
     * @return A string representing the type of the chess piece (e.g., "Queen").
     */
    std::string getType() const override;

    /**
     * @brief Count the number of capturing moves the queen can make.
     *
     * @param board The chess board to check for capturing moves.
     * @param start The starting square of the queen.
     * @param isWhite Indicates whether the queen is white.
     * @return The number of capturing moves the queen can make.
     */
    int countCapturingMoves(Board& board, Square& start, bool isWhite) const override;

    /**
     * @brief Simulate and validate capturing moves for the queen.
     *
     * This function simulates capturing moves for the queen and validates whether
     * they are legal. It keeps track of captured pawn positions and the maximum
     * number of capturing moves allowed.
     *
     * @param board The chess board on which moves are simulated and validated.
     * @param start The starting square of the queen.
     * @param isWhite Indicates whether the queen is white.
     * @param capturedPawnPositions A vector to store captured pawn positions.
     * @param maxCapturingMoves The maximum number of capturing moves allowed.
     * @param endSquare The ending square to validate.
     * @param piece The queen chess piece.
     * @return True if the capturing moves are valid, otherwise false.
     */
    bool simulateAndValidateCapturingMoves(Board& board, Square& start, bool isWhite, std::vector<Square*>& capturedPawnPositions, int maxCapturingMoves, Square& endSquare, Piece* piece);
};

#endif
