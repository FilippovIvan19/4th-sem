#pragma once

#include "structs.hpp"
#include <list>
class Snake;

class Game
{
public:
    enum
    {
        TICK = 100,
        RABBITS_CHANCE = 20,
        MAX_RABBITS = 10,
    };

    Game();

    void add(Snake& sn);
    void move();
    void draw();
    bool is_clear(Coord);
    Coord randxy();
    std::optional<Coord> rabbit_near(Coord);
private:
    std::list<std::reference_wrapper<Snake>> snakes;
    std::list<Coord> rabbits;
};
