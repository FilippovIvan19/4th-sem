#pragma once

// #include "Unitpack.h"
// #include "Map.h"
#include "constants.h"
class Unitpack;
class Map;


class Wave
{
private:
public:
    std::vector<Unitpack*> packs_;

    Wave(sf::RenderWindow *window, all_sprites *sprites, Map *map, std::string &wave_info);
    Wave();
   ~Wave(); // should delete every unitpack inside
    
    void draw() const;
    void update(float dt);
    void act(float dt);

    bool is_alive() const;
};
