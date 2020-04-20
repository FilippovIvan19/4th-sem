#pragma once

#include "constants.h"
class Level;
class Unit;


class Unitpack
{
private:
    float spawn_delta_;
    float spawn_delay_;
    int spawned_count_;
    float delayed_;
public:
    std::vector<Unit*> units_;

    Unitpack(sf::RenderWindow *window, all_sprites *sprites, Level *level,
        std::string &unit_name, int unit_count, float spawn_delta, float spawn_delay);
    Unitpack();
   ~Unitpack(); // should delete every unit inside
    
    void draw() const;
    void update(float dt);
    void act(float dt);

    void delay(float dt);
    bool is_alive() const;
};
