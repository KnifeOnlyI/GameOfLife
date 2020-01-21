#include "game_of_life/GameConwayRules.hpp"

namespace GOL
{
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
    if (nbAliveCellAround > 3 || nbAliveCellAround < 2)
    {
        cellState.nextState = GOL::CellNextState::DEAD;
    }
    else if (nbAliveCellAround == 3)
    {
        cellState.nextState = GOL::CellNextState::ALIVE;
    }
    else if (nbAliveCellAround == 2)
    {
        cellState.nextState = cellState.isAlive ? GOL::CellNextState::ALIVE : GOL::CellNextState::DEAD;
    }
}
}