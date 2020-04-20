#pragma once

class Level;
#include "Unit.h"


class BacteriaUnit : public Unit 
{
public:
    BacteriaUnit();
    BacteriaUnit(sf::RenderWindow *window, float x0, float y0, int health, float velocity, 
        sf::Sprite sprite, Level *level);
   ~BacteriaUnit();
};
