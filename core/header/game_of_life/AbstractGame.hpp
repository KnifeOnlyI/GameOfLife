#ifndef GAMEOFLIFE_ABSTRACTGAME_HPP
#define GAMEOFLIFE_ABSTRACTGAME_HPP

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
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
     * Initialize the map with random cell states
     */
    AbstractGame();

    explicit AbstractGame(const std::array<std::array<bool, MAP_WIDTH>, MAP_HEIGHT> &map);

    /**
     * Initialize the map
     *
     * \param configFile The file contains first turn configuration to analyze
     */
    explicit AbstractGame(const std::string &configFile);

    /**
     * Start the game and execute the number of turns
     */
    void start();

    /**
     * Execute one turn
     */
    void executeOneTurn();

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

private:
    /** \var The window */
    sf::RenderWindow _window {sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Game of life", sf::Style::Fullscreen};

    /** \var The cell shape */
    sf::RectangleShape _cellShape {sf::Vector2f {CELL_WIDTH, CELL_HEIGHT}};

    sf::Color _aliveCellColor {255, 255, 255};
    sf::Color _deadCellColor {0, 0, 0};

    /** \var The turn number */
    unsigned int _turnNumber {0};

    /** \var Represent the map. Pointer is used to not limited by stack memory allocation mechanism */
    std::unique_ptr<std::array<std::array<GOL::CellState, MAP_HEIGHT>, MAP_WIDTH >> _map;
};
}

#endif //GAMEOFLIFE_ABSTRACTGAME_HPP
