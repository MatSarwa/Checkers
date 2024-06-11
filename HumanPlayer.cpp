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
    int maxCapturingMoves = 0;

    // Find the maximum number of capturing moves available
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
    bool canCapture = (maxCapturingMoves > 0);

    int startYNumeric, startXNumeric;

    // Loop until a valid piece is selected
    while (true) {
        char startY, startX;
        std::cout << "Enter the starting position (x, y): ";
        std::cin >> startX >> startY;

        // Convert letter coordinates to numeric coordinates
        startYNumeric = convertCoordinate(startY);
        startXNumeric = convertCoordinate(startX);

        // Get the corresponding square from the board
        Square* startSquare = board.getSquare(startYNumeric, startXNumeric);
        Piece* piece = startSquare->getPiece();

        if (piece == nullptr) {
            std::cout << "Invalid move: No piece at the starting position." << std::endl;
            continue;
        }

        if (piece->isWhite() != isWhitePlayerTurn) {
            std::cout << "Invalid move: It's not your turn." << std::endl;
            continue;
        }

        int maxCapturing = piece->countCapturingMoves(board, *startSquare, isWhitePlayerTurn);
        if (canCapture && maxCapturing == 0) {
            std::cout << "Invalid move: This piece cannot capture." << std::endl;
            continue;
        }

        if (maxCapturing > 0) {
            std::cout << "Possible capturing for selected " << piece->getType() << ": " << maxCapturing << std::endl;
        }

        if (!canCapture) {
            char endY, endX;
            int endYNumeric, endXNumeric;

            std::cout << "Enter the ending position (x, y): ";
            std::cin >> endX >> endY;

            endYNumeric = convertCoordinate(endY);
            endXNumeric = convertCoordinate(endX);

            Square* endSquare = board.getSquare(endYNumeric, endXNumeric);

            // Check if the piece can move to the ending position
            if (!piece->canMove(board, *startSquare, *endSquare, !isWhitePlayerTurn)) {
                std::cout << "Invalid move: The piece cannot move to the ending position." << std::endl;
                continue;
            }

            // Check for promotion to a queen
            if (piece->getType() == "Pawn" && ((isWhitePlayerTurn && endYNumeric == 0) || (!isWhitePlayerTurn && endYNumeric == 7))) {
                board.updateSquare(startYNumeric, startXNumeric, nullptr);
                board.promoteQueen(endYNumeric, endXNumeric, piece);
                return;
            }

            // Move your piece to the end square (without capturing)
            endSquare->SetPiece(piece);
            startSquare->SetPiece(nullptr);
            return;
        }
        else {
            // Handle capturing moves
            std::vector<Square*> capturedPawnPositions;
            int capturingCount = 0;
            Square* currentSquare = startSquare;

            while (capturingCount < maxCapturingMoves) {
                char endY, endX;
                int endYNumeric, endXNumeric;

                std::cout << "Enter the ending position (x, y) for capture: ";
                std::cin >> endX >> endY;

                endYNumeric = convertCoordinate(endY);
                endXNumeric = convertCoordinate(endX);

                Square* endSquare = board.getSquare(endYNumeric, endXNumeric);

                if (piece->getType() == "Pawn") {
                    Pawn* pawn = static_cast<Pawn*>(piece);
                    if (pawn->simulateAndValidateCapturingMoves(board, *currentSquare, isWhitePlayerTurn, capturedPawnPositions, maxCapturingMoves, *endSquare, piece)) {
                        capturingCount++;
                        currentSquare = endSquare; // Update current square to new position after capturing
                        // If there are more captures possible, continue; otherwise, break
                        if (capturingCount >= maxCapturingMoves || piece->countCapturingMoves(board, *currentSquare, isWhitePlayerTurn) == 0) {
                            break;
                        }
                    }
                    else {
                        // If the function returns false, restore captured enemy pawns to the board
                        for (const auto& square : capturedPawnPositions) {
                            square->SetPiece(new Pawn(!isWhitePlayerTurn)); // Create a new enemy pawn and place it back on the board
                        }
                        capturedPawnPositions.clear();
                        startSquare->SetPiece(new Pawn(isWhitePlayerTurn));

                        std::cout << "Invalid move: The piece cannot move to the ending position." << std::endl;
                        break;
                    }
                }
            }
            return;
        }
    }
}








 
