#pragma once

#include "Unit.h"

class VirusUnit : public Unit 
{
public:
    VirusUnit();
    VirusUnit(sf::RenderWindow *window, float x0, float y0, int health,
        float velocity, int cost, sf::Sprite sprite, sf::Sprite health_sprite, Level *level);
   ~VirusUnit();
};
