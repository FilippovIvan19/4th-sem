#pragma once

#include "Map.h"
#include "EntityManager.h"
#include "NewWave.h"


class Level
{
private:
    std::vector<Wave*> waves_;
    Map map_;
    EntityManager entity_manager_;
public:
    Level(/* args */);
   ~Level(); //should delete every wave
    
    void draw() const;
    void update(float dt);
    void act(float dt);

    void run_wave(int wave_num);
};
