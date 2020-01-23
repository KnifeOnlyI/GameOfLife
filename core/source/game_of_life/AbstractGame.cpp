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
{
    std::default_random_engine generator {(unsigned long) std::chrono::system_clock::now().time_since_epoch().count()};

    std::uniform_int_distribution<int> distribution {0, 10};

    _map = std::make_unique<std::array<std::array<GOL::CellState, MAP_HEIGHT>, MAP_WIDTH>>();

    for (int x {0}; x < MAP_WIDTH; x++)
    {
        for (int y {0}; y < MAP_HEIGHT; y++)
        {
            _map->at(x)[y].isAlive = distribution(generator) == 1;
        }
    }
}

AbstractGame::AbstractGame(const std::array<std::array<bool, MAP_WIDTH>, MAP_HEIGHT> &map)
{
    _map = std::make_unique<std::array<std::array<GOL::CellState, MAP_HEIGHT>, MAP_WIDTH>>();

    for (unsigned int x {0}; x < MAP_WIDTH; x++)
    {
        for (unsigned int y {0}; y < MAP_HEIGHT; y++)
        {
            _map->at(x)[y].isAlive = map[x][y];
        }
    }
}

AbstractGame::AbstractGame(const std::string &configFile)
{
    const std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> data {};

    std::ifstream file {configFile};
    std::string line;

    int nbChar {0};
    int x {0};

    while (std::getline(file, line) && (x < MAP_HEIGHT))
    {
        nbChar = line.size();

        for (unsigned int y {0}; (y < MAP_WIDTH) && (y < nbChar); y++)
        {
            _map->at(x)[y].isAlive = line[y] == '1';
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
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Key::Space)
                {

                    _paused = !_paused;
                }
                else if (event.key.code == sf::Keyboard::Key::R)
                {
                    _waitingTime = WAITING_TIME_MS;
                }
            }
            else if ((event.type == sf::Event::MouseWheelScrolled) && (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel))
            {
                if (event.mouseWheelScroll.delta == 1)
                {
                    _waitingTime -= 2;

                    if (_waitingTime < 0)
                    {
                        _waitingTime = 0;
                    }
                }
                else if (event.mouseWheelScroll.delta == -1)
                {
                    _waitingTime += 2;
                }
            }
        }

        if (!_paused)
        {
            _window.clear();
            executeOneTurn();
            _window.display();
            std::this_thread::sleep_for(std::chrono::milliseconds(_waitingTime));
        }
    }

    std::cout << "Turn numbers : " << _turnNumber << '\n';
}

void AbstractGame::executeOneTurn()
{
    _turnNumber++;

    for (unsigned int x {0}; x < MAP_WIDTH; x++)
    {
        for (unsigned int y {0}; y < MAP_HEIGHT; y++)
        {
            GOL::CellState &cellState {_map->at(x)[y]};
            unsigned int nbAliveCellAround {getNbAliveCellAround(x, y)};

            checkCell(cellState, nbAliveCellAround);

            if (cellState.isAlive)
            {
                _cellShape.setFillColor(_aliveCellColor);
            }
            else
            {
                _cellShape.setFillColor(_deadCellColor);
            }

            _cellShape.setPosition(CELL_WIDTH * x, CELL_WIDTH * y);

            _window.draw(_cellShape);
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
        return _map->at(realX)[y].previously;
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
        return _map->at(realX)[y].isAlive;
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
        return _map->at(x)[realY].previously;
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
        return _map->at(x)[realY].isAlive;
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
        return _map->at(realX)[realY].previously;
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
        return _map->at(realX)[realY].previously;
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
        return _map->at(realX)[realY].previously;
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
        return _map->at(realX)[realY].isAlive;
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
}
