#include "Piece.h"

/**
 * @brief Constructor for a chess piece.
 * @param isWhite Indicates whether the piece is white or black.
 */
Piece::Piece(bool isWhite) : white(isWhite) {}

/**
 * @brief Destructor for a chess piece.
 */
Piece::~Piece() {}

/**
 * @brief Set the color of the chess piece.
 * @param isWhite Indicates whether the piece is white or black.
 */
void Piece::setWhite(bool isWhite) {
    white = isWhite;
}

/**
 * @brief Check if the chess piece is white.
 * @return True if the piece is white, false otherwise.
 */
bool Piece::isWhite() const {
    return white;
}
