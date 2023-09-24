#include "HumanPlayer.h"
#include <iostream>

/**
 * @brief Construct a new Human Player object.
 *
 * @param whiteside Whether the player is on the white side.
 */
HumanPlayer::HumanPlayer(bool whiteside) : Player() {
    this->whiteside = whiteside;
    this->humanPlayer = true;
}

/**
 * @brief Convert a character coordinate ('1'-'8', 'a'-'h', 'A'-'H') to its numeric representation (0-7).
 *
 * @param coordinate The character coordinate to convert.
 * @return int The numeric representation of the coordinate.
 * @throw std::runtime_error if the coordinate is invalid.
 */
int HumanPlayer::convertCoordinate(char coordinate) {
    if (coordinate >= '1' && coordinate <= '8') {
        return coordinate - '1';
    }
    else if (coordinate >= 'a' && coordinate <= 'h') {
        return coordinate - 'a';
    }
    else if (coordinate >= 'A' && coordinate <= 'H') {
        return coordinate - 'A';
    }
    else {
        // Handle error if the entered coordinate is invalid
        throw std::runtime_error("Invalid coordinate input.");
    }
}

/**
 * @brief Make a move for the human player.
 *
 * @param board The chess board.
 * @param isWhitePlayerTurn Whether it's the white player's turn.
 */
void HumanPlayer::makeMove(Board& board, bool isWhitePlayerTurn) {
    // Prompt the player for the starting and ending coordinates

    // Check if any pawn or queen can make a capturing move
    int maxCapturingMoves = 0;

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            Square* square = board.getSquare(row, col);
            Piece* piece = square->getPiece();

            if (piece != nullptr && piece->isWhite() == isWhitePlayerTurn) {
                int capturingMoves = piece->countCapturingMoves(board, *square, isWhitePlayerTurn);
                maxCapturingMoves = std::max(maxCapturingMoves, capturingMoves);
            }
        }
    }

    std::cout << "Max possible capturing on board: " << maxCapturingMoves << std::endl;
    int maxCapturingMovesForYourPawns = maxCapturingMoves;
    bool canCapture = (maxCapturingMovesForYourPawns > 0);

    int startYNumeric, startXNumeric, endYNumeric, endXNumeric;
    char startY, startX, endY, endX;

    std::cout << "Enter the starting position (x, y): ";
    std::cin >> startX >> startY;
    std::cout << "Enter the ending position (x, y): ";
    std::cin >> endX >> endY;

    // Convert letter coordinates to numeric coordinates
    startYNumeric = convertCoordinate(startY);
    startXNumeric = convertCoordinate(startX);
    endYNumeric = convertCoordinate(endY);
    endXNumeric = convertCoordinate(endX);

    // Get the corresponding squares from the board
    Square* startSquare = board.getSquare(startYNumeric, startXNumeric);
    Square* endSquare = board.getSquare(endYNumeric, endXNumeric);

    // Check if the piece on the start square exists
    Piece* piece = startSquare->getPiece();
    if (piece == nullptr) {
        throw std::runtime_error("Invalid move: No piece at the starting position.");
    }

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            Square* square = board.getSquare(row, col);
            Piece* piece = square->getPiece();

            if (piece != nullptr && piece->isWhite() == isWhitePlayerTurn) {
                int maxCapturing = piece->countCapturingMoves(board, *startSquare, isWhitePlayerTurn);

                if (maxCapturing >= maxCapturingMovesForYourPawns && maxCapturing > 0) {
                    canCapture = true;
                    std::cout << "Possible capturing for selected " << piece->getType() << ": " << maxCapturing << std::endl;
                }
            }
        }
    }

    // Check if the piece can move to the ending position
    if (!canCapture) {
        // Check if the piece can move to the ending position
        if (!piece->canMove(board, *startSquare, *endSquare, !isWhitePlayerTurn)) {
            throw std::runtime_error("Invalid move: The piece cannot move to the ending position.");
        }

        // Check for promotion to a queen
        if (piece->getType() == "Pawn" && ((isWhitePlayerTurn && endYNumeric == 0) || (!isWhitePlayerTurn && endYNumeric == 7))) {
            // Before promoting to a queen, remove the old pawn piece from the board
            board.updateSquare(startYNumeric, startXNumeric, nullptr);

            // Promote the pawn to a queen
            board.promoteQueen(endYNumeric, endXNumeric, piece);

            // Note: The board should already have the queen in the new position
            return;
        }

        // Move your piece to the end square (without capturing)
        endSquare->SetPiece(piece);
        startSquare->SetPiece(nullptr);
    }

    if (piece->getType() == "Pawn" || piece->getType() == "Queen") {
        Square* startSquarePawn = startSquare; // Save the starting square of the pawn
        std::vector<Square*> capturedPawnPositions; // To store captured pawn squares
        int capturingCount = 0; // Initialize a counter for capturing moves

        while (capturingCount < maxCapturingMovesForYourPawns) {
            char startX1, startY1, endX1, endY1;
            int startYNumeric1, startXNumeric1, endYNumeric1, endXNumeric1;

            std::cout << "Enter the starting position (x, y): ";
            std::cin >> startX1 >> startY1;
            std::cout << "Enter the ending position (x, y): ";
            std::cin >> endX1 >> endY1;

            startYNumeric1 = convertCoordinate(startY1);
            startXNumeric1 = convertCoordinate(startX1);
            endYNumeric1 = convertCoordinate(endY1);
            endXNumeric1 = convertCoordinate(endX1);

            Square* startSquare1 = board.getSquare(startYNumeric1, startXNumeric1);
            Square* endSquare1 = board.getSquare(endYNumeric1, endXNumeric1);

            // Check if the pawn is moving from its starting square
            if (startSquare1 != startSquarePawn) {
                throw std::runtime_error("Invalid move: This pawn must start its capturing moves from its original square.");
            }

            if (piece->getType() == "Pawn") {
                Pawn* pawn = static_cast<Pawn*>(piece);
                if (pawn->simulateAndValidateCapturingMoves(board, *startSquare1, isWhitePlayerTurn, capturedPawnPositions, maxCapturingMovesForYourPawns, *endSquare1, piece)) {
                    // Increment the capturing move count
                    capturingCount++;

                    // Update the starting square of the pawn for the next capturing move
                    startSquarePawn = endSquare1;
                }
                else {
                    // If the function returns false, restore captured enemy pawns to the board
                    for (const auto& square : capturedPawnPositions) {
                        square->SetPiece(new Pawn(!isWhitePlayerTurn)); // Create a new enemy pawn and place it back on the board
                    }
                    capturedPawnPositions.clear(); // Clear the vector
                    startSquare->SetPiece(new Pawn(isWhitePlayerTurn));

                    // Prompt the player to re-input values
                    std::cout << "Invalid move: The piece cannot move to the ending position." << std::endl;
                }
            }
        }
    }
}



 
