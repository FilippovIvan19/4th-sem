#pragma once

#include "Unitpack.h"
#include "Map.h"


class Wave
{
private:
    std::vector<Unitpack*> packs_;
public:

    Wave(sf::RenderWindow *window, all_sprites *sprites, Map *map, std::string &wave_info);
    Wave();
   ~Wave(); // should delete every unitpack inside
    
    void draw() const;
    void update(float dt);
    void act(float dt);
};
