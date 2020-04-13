#pragma once

#include "Tower.h"


class PillTower : public Tower
{
public:
    PillTower(sf::RenderWindow *window, float x0, float y0, all_sprites *sprites);
    PillTower();
   ~PillTower();
    
    // void shoot(Unit *target) override;
};
