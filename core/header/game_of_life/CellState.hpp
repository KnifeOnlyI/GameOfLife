#ifndef GAMEOFLIFE_CELLSTATE_HPP
#define GAMEOFLIFE_CELLSTATE_HPP

#include "game_of_life/Configuration.hpp"

namespace GOL
{
/**
 * Represent a cell state
 *
 * \author Dany Pignoux (dany.pignoux@outlook.fr)
 */
struct CellState
{
    bool isAlive {false}; /**< TRUE if the cell state is ALIVE, FALSE otherwise */
    bool previously {false}; /**< TRUE if the cell state was ALIVE, FALSE otherwise */
};
}

#endif //GAMEOFLIFE_CELLSTATE_HPP
