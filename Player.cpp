#include <iostream>
#include "Board.h"
#include "Player.h"
#include "Piece.h"
#include "Pawn.h"
#include "Queen.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"

/**
 * @file Player.cpp
 * @brief Implementation of the Player and its derived classes.
 */

 /**
  * @brief Getter for the whiteside attribute.
  *
  * @return True if the player is on the white side, false otherwise.
  */
bool Player::IsWhiteSide() {
    return whiteside;
}

/**
 * @brief Getter for the humanPlayer attribute.
 *
 * @return True if the player is a human player, false otherwise.
 */
bool Player::IsHumanPlayer() {
    return humanPlayer;
}

/**
 * @brief Setter for the humanPlayer attribute.
 *
 * @param human True if the player is a human player, false otherwise.
 */
void Player::SetHumanPlayer(bool human) {
    humanPlayer = human;
}

/**
 * @brief Setter for the whiteside attribute.
 *
 * @param isWhite True if the player is on the white side, false otherwise.
 */
void Player::SetWhiteSide(bool isWhite) {
    whiteside = isWhite;
}

/**
 * @brief Setter for the playerName attribute.
 *
 * @param name The name to set for the player.
 */
void Player::setName(const std::string& name) {
    playerName = name;
}

/**
 * @brief Getter for the playerName attribute.
 *
 * @return The name of the player.
 */
std::string Player::getName() const {
    return playerName;
}

/**
 * @brief Constructor for the Human class.
 *
 * @param whiteside True if the player is on the white side, false otherwise.
 */
Human::Human(bool whiteside) : Player() {
    this->whiteside = whiteside;
    this->humanPlayer = true;
}

/**
 * @brief Constructor for the Computer class.
 *
 * @param whiteside True if the player is on the white side, false otherwise.
 */
Computer::Computer(bool whiteside) : Player() {
    this->whiteside = whiteside;
    this->humanPlayer = false;
}

/**
 * @brief Function to choose player type, set name, and display player information.
 *
 * This function allows the user to select the player type (Human or Computer),
 * set the player's name, and displays the player's name.
 *
 * @param playerNumber The number assigned to the player.
 * @param isWhite True if the player is on the white side, false otherwise.
 * @return A pointer to the created player.
 */
Player* Player::chooseAndSetNameAndDisplay(int playerNumber, bool isWhite) {
    int choice;
    std::cout << "Choose player " << playerNumber << " type (1 - Human, 2 - Computer): ";
    std::cin >> choice;

    Player* player = nullptr;

    if (choice == 1) {
        player = new HumanPlayer(isWhite);
    }
    else if (choice == 2) {
        player = new ComputerPlayer(isWhite);
    }
    else {
        throw std::runtime_error("Invalid choice.");
    }

    std::string name;
    std::cout << "Enter name for player " << playerNumber << ": ";
    std::cin.ignore(); // Ignore the newline character left by previous input
    std::getline(std::cin, name);
    player->setName(name);

    // Display the player's name
    std::cout << "Player " << playerNumber << " name: " << player->getName() << std::endl;

    return player;
}