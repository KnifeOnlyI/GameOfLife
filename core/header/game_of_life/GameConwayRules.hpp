#ifndef GAMEOFLIFE_GAMECONWAYRULES_HPP
#define GAMEOFLIFE_GAMECONWAYRULES_HPP

#include "game_of_life/AbstractGame.hpp"

namespace GOL
{
/**
 * Represent the game of life with the conway's rules
 *
 * \author Dany Pignoux (dany.pignoux@outlook.fr)
 */
class GameConwayRules : public AbstractGame
{
public:
    GameConwayRules();

    explicit GameConwayRules(const std::array<std::array<bool, MAP_WIDTH>, MAP_HEIGHT> &map);

    explicit GameConwayRules(const std::string &configFile);

    void checkCell(GOL::CellState &cellState, unsigned int nbAliveCellAround) override;
};
}

#endif //GAMEOFLIFE_GAMECONWAYRULES_HPP
