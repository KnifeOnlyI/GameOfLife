#ifndef GAMEOFLIFE_ABSTRACTGAME_HPP
#define GAMEOFLIFE_ABSTRACTGAME_HPP

#include <array>

#include "game_of_life/CellState.hpp"

namespace GOL
{
/**
 * Represent the abstract base game. The rules is not specified
 *
 * \author Dany Pignoux (dany.pignoux@outlook.fr)
 */
class AbstractGame
{
public:
    /**
     * Initialize the map
     *
     * \param map The map configuration on the first turn
     */
    explicit AbstractGame(const std::array<std::array<bool, MAP_WIDTH>, MAP_HEIGHT> &map);

    /**
     * Initialize the map
     *
     * \param configFile The file contains first turn configuration to analyze
     */
    explicit AbstractGame(const std::string &configFile);

    /**
     * Start the game and execute the number of turns
     *
     * \param nbTurn The numbers of turn to execute
     */
    void start(unsigned int nbTurn);

    /**
     * Execute one turn
     */
    void executeOneTurn();

    /**
     * Update the map corresponding to all cell's state next states
     */
    void update();

    /**
     * Check the specified cell and determine the next state
     *
     * \param cellState The cell to analyze
     * \param nbAliveCellAround The number of alive cell around the specified cell state
     */
    virtual void checkCell(GOL::CellState &cellState, unsigned int nbAliveCellAround) = 0;

    /**
     * Check if the top of the specified position is alive
     *
     * \param x The x position to check
     * \param x The y position to check
     *
     * \return TRUE if the top of the specified position is alive,
     *         FALSE if is not alive or no cell state is available (e.g : out of map)
     */
    [[nodiscard]] bool topIsAlive(unsigned int x, unsigned int y) const;

    /**
     * Check if the bottom of the specified position is alive
     *
     * \param x The x position to check
     * \param x The y position to check
     *
     * \return TRUE if the bottom of the specified position is alive,
     *         FALSE if is not alive or no cell state is available (e.g : out of map)
     */
    [[nodiscard]] bool bottomIsAlive(unsigned int x, unsigned int y) const;

    /**
     * Check if the left of the specified position is alive
     *
     * \param x The x position to check
     * \param x The y position to check
     *
     * \return TRUE if the left of the specified position is alive,
     *         FALSE if is not alive or no cell state is available (e.g : out of map)
     */
    [[nodiscard]] bool leftIsAlive(unsigned int x, unsigned int y) const;

    /**
     * Check if the right of the specified position is alive
     *
     * \param x The x position to check
     * \param x The y position to check
     *
     * \return TRUE if the right of the specified position is alive,
     *         FALSE if is not alive or no cell state is available (e.g : out of map)
     */
    [[nodiscard]] bool rightIsAlive(unsigned int x, unsigned int y) const;

    /**
     * Check if the corner top left of the specified position is alive
     *
     * \param x The x position to check
     * \param x The y position to check
     *
     * \return TRUE if the corner top left of the specified position is alive,
     *         FALSE if is not alive or no cell state is available (e.g : out of map)
     */
    [[nodiscard]] bool cornerTopLeftIsAlive(unsigned int x, unsigned int y) const;

    /**
     * Check if the corner top right of the specified position is alive
     *
     * \param x The x position to check
     * \param x The y position to check
     *
     * \return TRUE if the corner top right of the specified position is alive,
     *         FALSE if is not alive or no cell state is available (e.g : out of map)
     */
    [[nodiscard]] bool cornerTopRightIsAlive(unsigned int x, unsigned int y) const;

    /**
     * Check if the corner bottom left of the specified position is alive
     *
     * \param x The x position to check
     * \param x The y position to check
     *
     * \return TRUE if the corner bottom left of the specified position is alive,
     *         FALSE if is not alive or no cell state is available (e.g : out of map)
     */
    [[nodiscard]] bool cornerBottomLeftIsAlive(unsigned int x, unsigned int y) const;

    /**
     * Check if the corner bottom right of the specified position is alive
     *
     * \param x The x position to check
     * \param x The y position to check
     *
     * \return TRUE if the corner bottom right of the specified position is alive,
     *         FALSE if is not alive or no cell state is available (e.g : out of map)
     */
    [[nodiscard]] bool cornerBottomRightIsAlive(unsigned int x, unsigned int y) const;

    /**
     * Get the total number of alive cells directly around of the specified position
     *
     * \param x The x position to check
     * \param y The y position to check
     *
     * \return The number
     */
    [[nodiscard]] unsigned int getNbAliveCellAround(unsigned int x, unsigned int y) const;

    /**
     * Display the map
     */
    void display() const;

private:
    /** \var The turn number */
    unsigned int _turnNumber {0};

    /**
     * \var Represent the map
     */
    std::array<std::array<GOL::CellState, MAP_WIDTH>, MAP_HEIGHT> _map;
};
}

#endif //GAMEOFLIFE_ABSTRACTGAME_HPP
