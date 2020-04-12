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
    
    void draw() const;
    void update(float dt);
    void act(float dt);

    void run_wave(int wave_num);
    GameCodes check_wave();
};
