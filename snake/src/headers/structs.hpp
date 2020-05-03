#pragma once

#include <optional>

enum Direction
{
    UP,
    DOWN,
    RIGHT,
    LEFT,
    BODY,
    NONE,
};

struct Coord : std::pair<int,int>
{
    using Parent = std::pair<int,int>;
    using Parent::Parent;

    int dist(const Coord& c) const
    {
        return std::abs(this->first - c.first) + std::abs(this->second - c.second);
    }
};

struct BodyPart : Coord
{
    BodyPart(const Coord &coord, int b, Direction dir) :
        Coord(coord),
        id(b),
        dir(dir)
        {}
    
    int id;
    Direction dir;
};

struct Rabbit : Coord, std::optional<int>
{
    Rabbit(const Coord& coord) :
        Coord(coord)
        {}
};
