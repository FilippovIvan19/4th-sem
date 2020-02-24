#pragma once


#include "Unit.h"

class BacteriaUnit : public Unit 
{
public:
    BacteriaUnit();
    BacteriaUnit(sf::RenderWindow *window, float x0, float y0, 
        sf::Sprite sprite, int frame_width, int frame_height);
   ~BacteriaUnit();
};