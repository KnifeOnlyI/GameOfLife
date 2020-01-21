#include <iostream>

#include "game_of_life/GameConwayRules.hpp"

int main()
{
    /*
     * Example file format :
     *
     * 01110
     * 00100
     * 01010
     * 00100
     * 01010
     */
    GOL::GameConwayRules map {"start.gol"};

    map.start(50);

    return 0;
}
