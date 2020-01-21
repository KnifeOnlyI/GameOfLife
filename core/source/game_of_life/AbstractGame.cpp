#include <SFML/Window/Event.hpp>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <random>

#include "game_of_life/AbstractGame.hpp"

namespace GOL
{
AbstractGame::AbstractGame()
    : _window {sf::VideoMode(CELL_WIDTH * MAP_WIDTH, CELL_WIDTH * MAP_HEIGHT), "Game of life"}
{
    std::default_random_engine generator;

    std::uniform_int_distribution<int> distribution {0, 2};

    for (unsigned x {0}; x < MAP_WIDTH; x++)
    {
        for (unsigned y {0}; y < MAP_HEIGHT; y++)
        {
            _map[x][y].isAlive = (distribution(generator)) == 1;
        }
    }
}

AbstractGame::AbstractGame(const std::array<std::array<bool, MAP_WIDTH>, MAP_HEIGHT> &map)
    : _window {sf::VideoMode(CELL_WIDTH * MAP_WIDTH, CELL_WIDTH * MAP_HEIGHT), "Game of life"}
{
    for (unsigned x {0}; x < MAP_WIDTH; x++)
    {
        for (unsigned y {0}; y < MAP_HEIGHT; y++)
        {
            _map[x][y].isAlive = map[x][y];
        }
    }
}

AbstractGame::AbstractGame(const std::string &configFile)
    : _window {sf::VideoMode(CELL_WIDTH * MAP_WIDTH, CELL_WIDTH * MAP_HEIGHT), "Game of life"}
{
    const std::array<std::array<bool, MAP_WIDTH>, MAP_HEIGHT> data {};

    std::ifstream file {configFile};
    std::string line;

    int nbChar {0};
    int x {0};

    while (std::getline(file, line) && (x < MAP_HEIGHT))
    {
        nbChar = line.size();

        for (unsigned int y {0}; (y < MAP_WIDTH) && (y < nbChar); y++)
        {
            _map[x][y].isAlive = line[y] == '1';
        }

        x++;
    }
}

void AbstractGame::start()
{
    while (_window.isOpen())
    {
        sf::Event event {};

        while (_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                _window.close();
            }
        }

        _window.clear();
        executeOneTurn();
        _window.display();

        std::this_thread::sleep_for(std::chrono::milliseconds(WAITING_TIME_MS));
    }
}

void AbstractGame::executeOneTurn()
{
    _turnNumber++;

    for (int x {0}; x < MAP_WIDTH; x++)
    {
        for (int y {0}; y < MAP_HEIGHT; y++)
        {
            GOL::CellState &cellState {_map[x][y]};
            unsigned int nbAliveCellAround {getNbAliveCellAround(x, y)};

            checkCell(cellState, nbAliveCellAround);
        }
    }

    update();
    display();
}

void AbstractGame::update()
{
    for (int x {0}; x < MAP_WIDTH; x++)
    {
        for (int y {0}; y < MAP_HEIGHT; y++)
        {
            CellState &cellState {_map[x][y]};

            if (cellState.nextState == GOL::CellNextState::UNKNOWN)
            {
                display();
                throw std::runtime_error("The next state of cell is UNKNOWN !");
            }

            cellState.isAlive = cellState.nextState == GOL::CellNextState::ALIVE;
        }
    }
}

bool AbstractGame::topIsAlive(unsigned int x, unsigned int y) const
{
    unsigned int realX {x - 1};

    // If realX is are out of bounds, return FALSE
    if ((realX < 0 || realX >= MAP_WIDTH))
    {
        return false;
    }
    else
    {
        return _map[realX][y].isAlive;
    }
}

bool AbstractGame::bottomIsAlive(unsigned int x, unsigned int y) const
{
    unsigned int realX {x + 1};

    // If realX is out of bounds, return FALSE
    if ((realX < 0 || realX >= MAP_WIDTH))
    {
        return false;
    }
    else
    {
        return _map[realX][y].isAlive;
    }
}

bool AbstractGame::leftIsAlive(unsigned int x, unsigned int y) const
{
    unsigned int realY {y - 1};

    // If realY is out of bounds, return FALSE
    if ((realY < 0 || realY >= MAP_WIDTH))
    {
        return false;
    }
    else
    {
        return _map[x][realY].isAlive;
    }
}

bool AbstractGame::rightIsAlive(unsigned int x, unsigned int y) const
{
    unsigned int realY {y + 1};

    // If realY is out of bounds, return FALSE
    if ((realY < 0 || realY >= MAP_WIDTH))
    {
        return false;
    }
    else
    {
        return _map[x][realY].isAlive;
    }
}

bool AbstractGame::cornerTopLeftIsAlive(unsigned int x, unsigned int y) const
{
    unsigned int realX {x - 1};
    unsigned int realY {y - 1};

    // If realX or realY are out of bounds, return FALSE
    if ((realX < 0 || realX >= MAP_WIDTH) || (realY < 0 || realY >= MAP_HEIGHT))
    {
        return false;
    }
    else
    {
        return _map[realX][realY].isAlive;
    }
}

bool AbstractGame::cornerTopRightIsAlive(unsigned int x, unsigned int y) const
{
    unsigned int realX {x - 1};
    unsigned int realY {y + 1};

    // If realX or realY are out of bounds, return FALSE
    if ((realX < 0 || realX >= MAP_WIDTH) || (realY < 0 || realY >= MAP_HEIGHT))
    {
        return false;
    }
    else
    {
        return _map[realX][realY].isAlive;
    }
}

bool AbstractGame::cornerBottomLeftIsAlive(unsigned int x, unsigned int y) const
{
    unsigned int realX {x + 1};
    unsigned int realY {y - 1};

    // If realX or realY are out of bounds, return FALSE
    if ((realX < 0 || realX >= MAP_WIDTH) || (realY < 0 || realY >= MAP_HEIGHT))
    {
        return false;
    }
    else
    {
        return _map[realX][realY].isAlive;
    }
}

bool AbstractGame::cornerBottomRightIsAlive(unsigned int x, unsigned int y) const
{
    unsigned int realX {x + 1};
    unsigned int realY {y + 1};

    // If realX or realY are out of bounds, return FALSE
    if ((realX < 0 || realX >= MAP_WIDTH) || (realY < 0 || realY >= MAP_HEIGHT))
    {
        return false;
    }
    else
    {
        return _map[realX][realY].isAlive;
    }
}

unsigned int AbstractGame::getNbAliveCellAround(unsigned int x, unsigned int y) const
{
    unsigned int results {0};

    if (cornerTopLeftIsAlive(x, y))
    {
        results++;
    }

    if (cornerTopRightIsAlive(x, y))
    {
        results++;
    }

    if (cornerBottomLeftIsAlive(x, y))
    {
        results++;
    }

    if (cornerBottomRightIsAlive(x, y))
    {
        results++;
    }

    if (topIsAlive(x, y))
    {
        results++;
    }

    if (leftIsAlive(x, y))
    {
        results++;
    }

    if (bottomIsAlive(x, y))
    {
        results++;
    }

    if (rightIsAlive(x, y))
    {
        results++;
    }

    return results;
}

void AbstractGame::display()
{
    for (unsigned int x {0}; x < MAP_WIDTH; x++)
    {
        for (unsigned int y {0}; y < MAP_HEIGHT; y++)
        {
            if (_map[x][y].isAlive)
            {
                _cellShape.setFillColor(sf::Color {255, 255, 255});
            }
            else
            {
                _cellShape.setFillColor(sf::Color {0, 0, 0});
            }

            _cellShape.setPosition(CELL_WIDTH * y, CELL_WIDTH * x);

            _window.draw(_cellShape);
        }
    }
}
}
