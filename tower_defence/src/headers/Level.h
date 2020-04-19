#pragma once

#include "EntityManager.h"


class Level
{
private:
    std::vector<Wave*> waves_;
    int cur_wave_num_;
public:
    Map map_;
    EntityManager entity_manager_;

    Level(sf::RenderWindow *window, all_sprites *sprites, int num);
    Level();
   ~Level(); //should delete every wave

    void run_wave(int wave_num);
    void damage_hq(int n = 1);
    
    void draw() const;
    void update(float dt);
    void act(float dt);

    GameCodes check_wave();
};
