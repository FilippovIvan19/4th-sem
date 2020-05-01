#pragma once

#include "constants.h"

class Unitpack;
class Level;


class Wave
{
private:
public:
    std::vector<Unitpack*> packs_;

    Wave(sf::RenderWindow *window, all_sprites *sprites, Level *level, std::string &wave_info);
    Wave();
   ~Wave(); // should delete every unitpack inside
    
    void draw() const;
    void update(float dt);
    void act(float dt);

    bool is_alive() const;
};
