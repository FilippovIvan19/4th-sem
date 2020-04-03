#pragma once


#include "Unit.h"

class BacteriaUnit : public Unit 
{
public:
    BacteriaUnit();
    BacteriaUnit(sf::RenderWindow *window, float x0, float y0, 
        sf::Sprite sprite, int pic_frame_width, int pic_frame_height, Map* map);
   ~BacteriaUnit();
};
