#include "Move.h"
#include "Square.h"
#include "Board.h"
#include "Pawn.h"



void Move::makeMove(Board& board, bool isWhitePlayerTurn) {
    // Prompt the player for the starting and ending coordinates
    int startX, startY, endX, endY;
    std::cout << "Enter the starting position (x, y): ";
    std::cin >> startX >> startY;
    std::cout << "Enter the ending position (x, y): ";
    std::cin >> endX >> endY;

    // Get the corresponding squares from the board
    Square* startSquare = board.getSquare(startX, startY);
    Square* endSquare = board.getSquare(endX, endY);

    // Check if the squares are valid
    if (startSquare == nullptr) {
        throw std::runtime_error("Invalid move: Invalid coordinates.");
    }

    // Check if the piece on the start square exists
    Piece* piece = startSquare->getPiece();
    if (piece == nullptr) {
        throw std::runtime_error("Invalid move: No piece at the starting position.");
    }

    // Check if it's the correct player's turn
    if (piece->isWhite() != isWhitePlayerTurn) {
        throw std::runtime_error("Invalid move: It's not your turn.");
    }

    // Check if the piece can move to the ending position
    if (!piece->canMove(board, *startSquare, *endSquare, !isWhitePlayerTurn)) {
        throw std::runtime_error("Invalid move: The piece cannot move to the ending position.");
    }

    // Move the piece to the end square
    endSquare->SetPiece(piece);
    startSquare->SetPiece(nullptr);

    // Check if it's a capturing move
    if (std::abs(endX - startX) == 2 && std::abs(endY - startY) == 2) {
        // Calculate the coordinates of the captured piece
        int capturedX = startX + ((endX - startX) / 2);
        int capturedY = startY + ((endY - startY) / 2);

        // Get the captured square and remove the captured piece
        Square* capturedSquare = board.getSquare(capturedX, capturedY);
        capturedSquare->SetPiece(nullptr);
    }

    if (piece->getType() == "Pawn") {
        if ((isWhitePlayerTurn && endX == 0) || (!isWhitePlayerTurn && endX == 7)) {
            // Before promoting to a queen, remove the old pawn piece from the board
            board.updateSquare(startX, startY, nullptr);

            // Promote the pawn to a queen
            board.promoteQueen(endX, endY, piece);

            // Note: The board should already have the queen in the new position
            return;
        }
    }


    // Update the board with the new positions
    board.updateSquare(startX, startY, nullptr);
    board.updateSquare(endX, endY, piece);
}

