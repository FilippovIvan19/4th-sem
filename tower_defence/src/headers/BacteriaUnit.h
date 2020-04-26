#pragma once

#include "Unit.h"

class BacteriaUnit : public Unit 
{
public:
    BacteriaUnit();
    BacteriaUnit(sf::RenderWindow *window, float x0, float y0, int health,
        float velocity, int cost, sf::Sprite sprite, sf::Sprite health_sprite, Level *level);
   ~BacteriaUnit();
};
