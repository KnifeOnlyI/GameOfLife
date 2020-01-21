#ifndef GAMEOFLIFE_CELLSTATE_HPP
#define GAMEOFLIFE_CELLSTATE_HPP

#include "game_of_life/Configuration.hpp"

namespace GOL
{
enum CellNextState
{
    ALIVE,
    DEAD,
    UNKNOWN,
};

/**
 * Represent a cell state
 *
 * \author Dany Pignoux (dany.pignoux@outlook.fr)
 */
struct CellState
{
    bool isAlive {false}; /**< TRUE if the cell state is ALIVE, FALSE otherwise */
    CellNextState nextState {UNKNOWN}; /**< TRUE if the cell state is ALIVE, FALSE otherwise */
};
}

#endif //GAMEOFLIFE_CELLSTATE_HPP
