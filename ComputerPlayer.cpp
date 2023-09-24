#include "ComputerPlayer.h"

/**
 * @brief Constructor for ComputerPlayer class.
 *
 * @param whiteside True if the player is playing as the white side, false otherwise.
 */
ComputerPlayer::ComputerPlayer(bool whiteside) : Player() {
    this->whiteside = whiteside;
    this->humanPlayer = false;
}

/**
 * @brief Make a move on the board for the computer player.
 *
 * This function is not yet implemented and currently displays a message
 * indicating that the computer player's move is pending.
 *
 * @param board The game board on which the move will be made.
 * @param isWhitePlayerTurn True if it's the white player's turn, false otherwise.
 */
void ComputerPlayer::makeMove(Board& board, bool isWhitePlayerTurn) {
    // Display a message indicating that ComputerPlayer is not implemented yet
    std::cout << "ComputerPlayer not implemented yet\n";

    // Check if the player is not a human player, and exit the game if so
    if (!humanPlayer) {
        std::cout << "Exiting the game because the computer is the player." << std::endl;
        std::exit(0);
    }
}