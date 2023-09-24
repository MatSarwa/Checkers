#include "Board.h"
#include "Square.h"
#include "Pawn.h"
#include <iostream>
#include "Queen.h"

Board::Board() {
    // Initialize the chess board with squares and nullptr (no pieces) initially
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            tab[i][j] = new Square(i, j, nullptr);
        }
    }
}

void Board::setState(GameState* newState) {
    // Clean up the existing state and set the new state
    delete currentState;
    currentState = newState;
}

void Board::displayState() {
    currentState->displayState(); // Delegate to the current state's displayState()
}

void Board::clearConsole(std::string name, std::string name1) {
    // Clear the console and display game setup information
    std::system("cls");
    std::cout << "Choose player 1 type (1 - Human, 2 - Computer): 1" << std::endl;
    std::cout << "Choose player 2 type (1 - Human, 2 - Computer): 1" << std::endl;
    std::cout << "Enter name for player 1: " << name << std::endl;
    std::cout << "Enter name for player 2: " << name1 << std::endl;
    std::cout << "Player 1 name: " << name << std::endl;
    std::cout << "Player 2 name: " << name1 << std::endl;
    std::cout << std::endl;
}

bool Board::CheckGameOver() {
    whitePiecesLeft = false;
    blackPiecesLeft = false;

    // Check if there are any pieces left on the board
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Square* square = tab[i][j];

            if (square != nullptr) {
                Piece* piece = square->getPiece();

                if (piece != nullptr) {
                    if (piece->isWhite()) {
                        whitePiecesLeft = true;
                    }
                    else {
                        blackPiecesLeft = true;
                    }
                }
            }
        }
    }

    // If there are no white or black pieces left, set the game to GameOverState
    if (!whitePiecesLeft || !blackPiecesLeft) {
        setState(new GameOverState());
        std::cout << "Game Over!" << std::endl;
        return true;
    }

    return false; // The game is not over yet
}

Square* Board::getSquare(int x, int y) const {
    return tab[x][y];
}

void Board::GameCreation() {
    // Initialize the chess board with pieces in their starting positions
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 8; j++) {
            if ((j % 2) == (i % 2)) {
                tab[i][j] = new Square(i, j, nullptr);
            }
            else {
                tab[i][j] = new Square(i, j, new Pawn(false));
            }
        }
    }

    for (int i = 3; i < 5; i++) {
        for (int j = 0; j < 8; j++) {
            if ((j % 2) == (i % 2)) {
                tab[i][j] = new Square(i, j, nullptr);
            }
            else {
                tab[i][j] = new Square(i, j, nullptr);
            }
        }
    }

    for (int i = 5; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((j % 2) == (i % 2)) {
                tab[i][j] = new Square(i, j, nullptr);
            }
            else {
                tab[i][j] = new Square(i, j, new Pawn(true));
            }
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Board& board) {
    // Display the current state of the chess board
    os << "   A B C D E F G H  \n";
    os << "  +---------------+\n";
    for (int i = 0; i < 8; i++) {
        os << i + 1 << " |";
        for (int j = 0; j < 8; j++) {
            Square* square = board.tab[i][j];
            if (square == nullptr) {
                os << " ";
            }
            else {
                Piece* piece = square->getPiece();
                if (piece == nullptr) {
                    os << " ";
                }
                else {
                    if (piece->getType() == "Queen") {
                        if (piece->isWhite()) {
                            os << "W"; // Uppercase 'W' for white queen
                        }
                        else {
                            os << "B";
                        }
                    }
                    else if (piece->getType() == "Pawn") {
                        if (piece->isWhite()) {
                            os << "w";
                        }
                        else {
                            os << "b";
                        }
                    }
                }
            }
            os << "|";
        }
        os << " " << i + 1 << "\n";
    }
    os << "  +---------------+\n";
    os << "   A B C D E F G H \n";
    return os;
}

void Board::updateSquare(int x, int y, Piece* piece) {
    // Get the square at coordinates (x, y)
    Square* square = getSquare(x, y);

    if (square != nullptr) {
        // Set the piece within the square using the setPiece function
        square->SetPiece(piece);
    }
    else {
        // Handle the case when the square is not found or invalid
        throw std::runtime_error("Invalid square coordinates");
    }
}

void Board::promoteQueen(int x, int y, Piece* piece) {
    // Check if the piece is a Pawn
    if (piece->getType() == "Pawn") {
        if (piece->isWhite()) {
            // Check if the white Pawn reaches the last row
            if (x == 0) {
                // Promote the white Pawn to a Queen
                delete tab[x][y]->getPiece();
                tab[x][y]->SetPiece(new Queen(true));
            }
        }
        else {
            // Check if the black Pawn reaches the last row
            if (x == 7) {
                // Promote the black Pawn to a Queen
                delete tab[x][y]->getPiece();
                tab[x][y]->SetPiece(new Queen(false));
            }
        }
    }
}

