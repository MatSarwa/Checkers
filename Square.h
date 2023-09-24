#ifndef SQUARE_HPP
#define SQUARE_HPP

class Piece; // Forward declaration of the Piece class

/**
 * @brief The Square class represents a square on a chessboard.
 *
 * This class defines a square on the chessboard with its coordinates (x, y)
 * and the chess piece that may be placed on it.
 */
class Square {
private:
    // No private members in this class.

public:
    int x; ///< The x-coordinate of the square.
    int y; ///< The y-coordinate of the square.
    Piece* piece; ///< Pointer to the chess piece placed on the square.

    /**
     * @brief Constructor for the Square class.
     *
     * @param xCoord The x-coordinate of the square.
     * @param yCoord The y-coordinate of the square.
     * @param p Pointer to the chess piece placed on the square.
     */
    Square(int xCoord, int yCoord, Piece* p);

    /**
     * @brief Default constructor for the Square class.
     */
    Square();

    /**
     * @brief Get the x-coordinate of the square.
     *
     * @return The x-coordinate of the square.
     */
    int GetX() const;

    /**
     * @brief Get the y-coordinate of the square.
     *
     * @return The y-coordinate of the square.
     */
    int GetY() const;

    /**
     * @brief Get the chess piece placed on the square.
     *
     * @return Pointer to the chess piece on the square.
     */
    Piece* getPiece() const;

    /**
     * @brief Set the chess piece placed on the square.
     *
     * @param p Pointer to the chess piece to place on the square.
     */
    void SetPiece(Piece* p);
};

#endif
