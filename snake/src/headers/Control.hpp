#pragma once

#include "Snake.hpp"

class Control : public Snake
{
public:
    Control(Game& game);
protected:
    Game& game;
};
