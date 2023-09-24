#include "Pawn.h"
#include "Board.h"
#include "Square.h"
#include "Piece.h"

/**
 * @file Pawn.cpp
 * @brief Implementation of the Pawn class and its member functions.
 */

 /**
  * @brief Constructor for the Pawn class.
  *
  * @param isWhite True if the Pawn is a white piece, false otherwise.
  */
Pawn::Pawn(bool isWhite) : Piece(isWhite) {}

/**
 * @brief Get the type of the Pawn.
 *
 * @return The string "Pawn".
 */
std::string Pawn::getType() const {
    return "Pawn";
}

/**
 * @brief Determine if the Pawn can move to a given square.
 *
 * This function checks if the Pawn can move to the specified square on the board.
 *
 * @param board The game board.
 * @param start The starting square.
 * @param end The target square.
 * @param isWhite True if the Pawn is white, false if black.
 * @return True if the move is valid, false otherwise.
 */
bool Pawn::canMove(Board& board, Square& start, Square& end, bool isWhite) const {
    int startX = start.GetX();
    int startY = start.GetY();
    int endX = end.GetX();
    int endY = end.GetY();

    // Check if the end square is within the bounds of the board
    if (endX < 0 || endX >= 8 || endY < 0 || endY >= 8) {
        return false;
    }

    // Check if the end square is occupied
    if (end.getPiece() != nullptr) {
        return false;
    }

    // Calculate the row and column differences between the start and end squares
    int rowDiff = endX - startX;
    int colDiff = endY - startY;

    // Determine the valid moves for a pawn based on its color
    int forwardDirection = isWhite ? 1 : -1;

    // Pawn can move diagonally forward by one square
    if (rowDiff == forwardDirection && abs(colDiff) == 1) {
        // Check if the end square is empty
        if (end.getPiece() == nullptr) {
            return true;
        }
    }

    // Invalid move
    return false;
}

/**
 * @brief Simulate and validate capturing moves for the Pawn.
 *
 * This function simulates and validates capturing moves for the Pawn.
 *
 * @param board The game board.
 * @param start The starting square.
 * @param isWhite True if the Pawn is white, false if black.
 * @param capturedPawnPositions A vector to store the positions of captured pawns.
 * @param maxCapturingMoves The maximum number of capturing moves.
 * @param endSquare The target square.
 * @param piece The Pawn piece.
 * @return True if capturing is successful, false otherwise.
 */
bool Pawn::simulateAndValidateCapturingMoves(Board& board, Square& start, bool isWhite, std::vector<Square*>& capturedPawnPositions, int maxCapturingMoves, Square& endSquare, Piece* piece) {
    int startX = start.GetX();
    int startY = start.GetY();

    int endX = endSquare.GetX();
    int endY = endSquare.GetY();

    // Calculate coordinates for the behind square
    int behindX = (startX + endX) / 2;
    int behindY = (startY + endY) / 2;

    Square* behindSquare = board.getSquare(behindX, behindY);

    // Check if the behind square exists and has an enemy piece
    if (behindSquare && behindSquare->getPiece() && behindSquare->getPiece()->isWhite() != isWhite) {
        // Check if the end square is diagonally two squares away from the start square
        if (std::abs(endX - startX) == 2 && std::abs(endY - startY) == 2) {
            // Store the captured enemy pawn square
            capturedPawnPositions.push_back(behindSquare);

            // Move the current pawn to the end square
            endSquare.SetPiece(piece);
            start.SetPiece(nullptr);
            behindSquare->SetPiece(nullptr);
            std::cout << board;
            // Remove the enemy pawn from the board

            return true; // Return true when capturing is successful
        }
    }

    start.SetPiece(nullptr);
    return false; // Return false when capturing is not possible
}

/**
 * @brief Count capturing moves for the Pawn.
 *
 * This function counts the number of capturing moves the Pawn can make.
 *
 * @param board The game board.
 * @param start The starting square.
 * @param isWhite True if the Pawn is white, false if black.
 * @return The number of capturing moves.
 */
int Pawn::countCapturingMoves(Board& board, Square& start, bool isWhite) const {
    // Get the starting coordinates
    int startX = start.GetX();
    int startY = start.GetY();

    // Initialize the capturing move count
    int capturingMoves = 0;

    // Define the possible ending coordinates in all four directions
    int possibleEndX[] = { startX + 1, startX - 1, startX + 1, startX - 1 };
    int possibleEndY[] = { startY + 1, startY - 1, startY - 1, startY + 1 };

    // Iterate through all four possible directions
    for (int i = 0; i < 4; ++i) {
        int endX = possibleEndX[i];
        int endY = possibleEndY[i];

        // Check if the potential destination square is within the bounds of the board
        if (endX >= 0 && endX < 8 && endY >= 0 && endY < 8) {
            Square* endSquare = board.getSquare(endX, endY);

            if (endSquare) {
                Piece* capturedPiece = endSquare->getPiece();

                // Check if there is a piece on the destination square and it belongs to the opponent
                if (capturedPiece && capturedPiece->isWhite() != isWhite) {
                    int behindX = endX + (endX - startX);
                    int behindY = endY + (endY - startY);

                    // Check if the square behind the captured piece is within the bounds
                    if (behindX >= 0 && behindX < 8 && behindY >= 0 && behindY < 8) {
                        Square* behindSquare = board.getSquare(behindX, behindY);

                        if (behindSquare && !behindSquare->getPiece()) {
                            Piece* currentPiece = start.getPiece();

                            // Perform the move
                            endSquare->SetPiece(nullptr);
                            behindSquare->SetPiece(currentPiece);

                            // Recursively count capturing moves in this direction
                            int movesInThisDirection = 1 + countCapturingMoves(board, *behindSquare, isWhite);

                            // Update the maximum capturing moves found
                            capturingMoves = std::max(capturingMoves, movesInThisDirection);

                            // Undo the move
                            behindSquare->SetPiece(nullptr);
                            endSquare->SetPiece(capturedPiece);
                            start.SetPiece(currentPiece);
                        }
                    }
                }
            }
        }
    }

    return capturingMoves;
}