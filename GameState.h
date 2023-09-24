#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP


/**
 * @brief The GameState class represents a state of the chess game.
 *
 * This class is an abstract base class that defines the interface for different
 * game states. Subclasses of this class should implement the `displayState` function
 * to provide specific behavior for displaying the game state.
 */
class GameState {
public:
    /**
     * @brief Display the state of the game.
     *
     * This pure virtual function should be implemented by subclasses to display
     * information about the current game state.
     */
    virtual void displayState() = 0;

    /**
     * @brief Virtual destructor for the GameState class.
     */
    virtual ~GameState() = default;
};

#endif
