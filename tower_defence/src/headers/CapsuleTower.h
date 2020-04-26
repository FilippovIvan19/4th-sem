#pragma once

#include "Tower.h"
#include "constants.h"


class CapsuleTower : public Tower
{
public:
    CapsuleTower(sf::RenderWindow *window, float x0, float y0, all_sprites *sprites);
    CapsuleTower();
   ~CapsuleTower();
    
    // void shoot(Unit *target) override;
};
