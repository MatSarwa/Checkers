#include "Square.h" 
#include "Piece.h"

/**
 * @brief Constructor for the Square class.
 * @param xCoord The X-coordinate of the square.
 * @param yCoord The Y-coordinate of the square.
 * @param p A pointer to the Piece object placed on the square.
 */
Square::Square(int xCoord, int yCoord, Piece* p) : x(xCoord), y(yCoord), piece(p) {
    // Constructor implementation
}

/**
 * @brief Default constructor for the Square class.
 */
Square::Square() {};

/**
 * @brief Get the X-coordinate of the square.
 * @return The X-coordinate of the square.
 */
int Square::GetX() const {
    return x;
}

/**
 * @brief Get the Y-coordinate of the square.
 * @return The Y-coordinate of the square.
 */
int Square::GetY() const {
    return y;
}

/**
 * @brief Get the chess piece placed on the square.
 * @return A pointer to the Piece object on the square.
 */
Piece* Square::getPiece() const {
    return piece;
}

/**
 * @brief Set the chess piece on the square.
 * @param p A pointer to the Piece object to be placed on the square.
 */
void Square::SetPiece(Piece* p) {
    piece = p;
}
