#include "Board.h"
#include "Player.h"
#include "Move.h"
#include "Piece.h"
#include "GameState.h"
#include "GameOverState.h"
#include <string>
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include <chrono>

template <typename Duration>
Duration addDurations(const Duration& duration1, const Duration& duration2) {
    return duration1 + duration2;
}

int main() {
   
    GameState* currentState = new StartState();
    currentState->displayState();
    bool isWhitePlayerTurn = true;

    std::chrono::seconds firstPlayer(0);
    std::chrono::seconds secondPlayer(0);

    // Choose player types
    Player* player1 = Player::chooseAndSetNameAndDisplay(1, true);
    Player* player2 = Player::chooseAndSetNameAndDisplay(2, false);

    Board board;

    board.GameCreation();
    std::cout << std::endl << board << std::endl; // Display the initial board

    Player* currentPlayer = player1; // Start with player 1

    try {
        while (!board.CheckGameOver()) {
            if (currentPlayer->IsHumanPlayer()) {
                std::cout << currentPlayer->getName() << "'s turn" << std::endl;
            }
            else {
                std::cout << "Computer's turn" << std::endl;
            }

            try {
                auto startTime = std::chrono::high_resolution_clock::now();
                    currentPlayer->makeMove(board, isWhitePlayerTurn);
                auto endTime = std::chrono::high_resolution_clock::now();
                auto moveTime = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);

                if (currentPlayer == player1) {
                    firstPlayer = addDurations(firstPlayer, moveTime);
                }
                else {
                    secondPlayer = addDurations(secondPlayer, moveTime);
                }
            }
            catch (const std::exception& e) {
                board.clearConsole(player1->getName(), player2->getName());
                std::cout << board << std::endl; // Display the board after the move
                std::cout << "Invalid move: " << e.what() << std::endl;
                continue; // Continue to the next iteration of the loop
            }

            board.clearConsole(player1->getName(), player2->getName());
            std::cout << board << std::endl; // Display the board after the move    
            std::cout << "Duration of player 1's moves: " << firstPlayer.count() << " s" << std::endl;
            std::cout << "Duration of player 2's moves: " << secondPlayer.count() << " s" << std::endl;

            // Switch the turn to the next player
            isWhitePlayerTurn = !isWhitePlayerTurn;
            currentPlayer = (currentPlayer == player1) ? player2 : player1; // Switch players
        }
    }
    catch (const std::exception& e) {
        std::cout << "An unexpected error occurred: " << e.what() << std::endl;
    }

    // Free memory
    delete player1;
    delete player2;

    delete currentState;

    return 0;
}








