#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Board; // Forward declaration
class Square; // Forward declaration

/**
 * @brief The Pawn class represents a pawn chess piece.
 *
 * This class is a subclass of the Piece class and defines the behavior and rules
 * specific to the pawn piece in chess.
 */
class Pawn : public Piece {
public:
    /**
     * @brief Constructor for the Pawn class.
     *
     * @param isWhite Indicates whether the pawn is a white piece.
     */
    Pawn(bool isWhite);

    /**
     * @brief Check if the pawn can move from the starting square to the ending square.
     *
     * @param board The chess board on which the move is being checked.
     * @param start The starting square of the move.
     * @param end The ending square of the move.
     * @param isWhite Indicates whether the pawn is a white piece.
     * @return True if the move is valid for the pawn, otherwise false.
     */
    bool canMove(Board& board, Square& start, Square& end, bool isWhite) const override;

    /**
     * @brief Simulate and validate capturing moves for the pawn.
     *
     * @param board The chess board on which moves are being simulated and validated.
     * @param start The starting square of the move.
     * @param isWhite Indicates whether the pawn is a white piece.
     * @param capturedPawnPositions A vector to store captured pawn positions during simulation.
     * @param maxCapturingMoves The maximum number of capturing moves to simulate.
     * @param endSquare The square to which the pawn intends to move.
     * @param piece Pointer to the piece being captured, if applicable.
     * @return True if the move is valid and captures other pieces, otherwise false.
     */
    bool simulateAndValidateCapturingMoves(Board& board, Square& start, bool isWhite, std::vector<Square*>& capturedPawnPositions, int maxCapturingMoves, Square& endSquare, Piece* piece);

    /**
 
   

    /**
     * @brief Count the number of capturing moves the pawn can make.
     *
     * @param board The chess board to check for capturing moves.
     * @param start The starting square of the pawn.
     * @param isWhite Indicates whether the pawn is white.
     * @return The number of capturing moves the pawn can make.
     */
    int countCapturingMoves(Board& board, Square& start, bool isWhite) const override;

    /**
     * @brief Get the type of the chess piece.
     *
     * @return A string representing the type of the chess piece (e.g., "Pawn").
     */
    std::string getType() const override;
};

#endif
