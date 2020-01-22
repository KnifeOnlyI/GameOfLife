#include "game_of_life/GameConwayRules.hpp"

namespace GOL
{
GameConwayRules::GameConwayRules()
    : AbstractGame {}
{
}

GameConwayRules::GameConwayRules(const std::array<std::array<bool, MAP_WIDTH>, MAP_HEIGHT> &map)
    : AbstractGame {map}
{
}

GameConwayRules::GameConwayRules(const std::string &configFile)
    : AbstractGame(configFile)
{
}

void GameConwayRules::checkCell(GOL::CellState &cellState, unsigned int nbAliveCellAround)
{
    cellState.previously = cellState.isAlive;

    if (nbAliveCellAround > 3 || nbAliveCellAround < 2)
    {
        cellState.isAlive = false;
    }
    else if (nbAliveCellAround == 3)
    {
        cellState.isAlive = true;
    }
}
}