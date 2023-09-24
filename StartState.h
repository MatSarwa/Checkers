#ifndef STARTSTATE_HPP
#define STARTSTATE_HPP

#include "GameState.h"

/**
 * @brief The StartState class represents the game state at the start of a chess game.
 *
 * This class is a subclass of the GameState class and is responsible for displaying
 * the state of the game at the beginning when it is in the initial setup phase.
 */
class StartState : public GameState {
public:
    /**
     * @brief Display the initial state of the game.
     *
     * This function is responsible for displaying information about the game
     * when it is in the initial setup phase, such as the starting position of the pieces.
     */
    void displayState() override;
};

#endif
