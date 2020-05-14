#pragma once

#include "Control.hpp"

class Human : public Control
{
public:
    Human(Game& game);
    void keypressed(int key);
};

class Robot : public Control
{
public:
    Robot(Game& game);
    void tick();
};
