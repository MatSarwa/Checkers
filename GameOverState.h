#ifndef GAMEOVERSTATE_HPP
#define GAMEOVERSTATE_HPP

#include "GameState.h"

/**
 * @brief The GameOverState class represents the game state when the game is over.
 *
 * This class is a subclass of the GameState class and is responsible for displaying
 * the state of the game when it has concluded.
 */
class GameOverState : public GameState {
public:
    /**
     * @brief Display the state of the game when it is over.
     *
     * This function is responsible for displaying information about the game's outcome
     * when the game has reached its conclusion.
     */
    void displayState() override;
};

#endif
