#pragma once

#include "Unit.h"


class Unitpack
{
private:
    std::vector<Unit*> units_;
    float spawn_delta_;
    float spawn_delay_;
    int spawned_count_;
    float delayed_;
public:
    Unitpack(sf::RenderWindow *window, all_sprites *sprites, Map *map,
        std::string &unit_name, int unit_count, float spawn_delta, float spawn_delay);
    Unitpack();
   ~Unitpack(); // should delete every unit inside
    
    void draw() const;
    void update(float dt);
    void act(float dt);

    void delay(float dt);
    bool is_alive() const;
};
