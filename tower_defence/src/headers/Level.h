#pragma once

#include "EntityManager.h"
#include "Map.h"
#include "constants.h"
class Wave;


class Level
{
private:
    std::vector<Wave*> waves_;
    int cur_wave_num_;
    int hq_health_;
    int coins_;
public:
    Map map_;
    EntityManager entity_manager_;

    Level(sf::RenderWindow *window, all_sprites *sprites, int num);
    Level();
   ~Level(); //should delete every wave

    void run_wave(int wave_num);
    void damage_hq(int hp = 1);
    void add_coins(int count);
    int get_coins();
    int get_health();
    
    void draw() const;
    void update(float dt);
    void act(float dt);
    std::pair<int, int> get_wave_num();

    GameCodes check_wave();
};
