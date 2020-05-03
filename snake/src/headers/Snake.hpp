#pragma once

#include <cstdio>
#include <list>
#include "structs.hpp"
class Game;

class Snake
{
public:
    explicit Snake(Game&);
    Snake(const Snake&) = delete;
    Snake& operator=(const Snake&) = delete;

    Coord next();
    void move(std::list<Coord> &rabbits);

    bool stopped;
    Direction dir;
    int id;
    std::list<Coord> body;
protected:
    Game &game;
};
