#pragma once

#include "Wave.h"
#include "Tower.h"


class EntityManager
{
private:
    std::set<Tower*> towers_;
    Wave *cur_wave_;
public:
    EntityManager();
   ~EntityManager(); // should delete every tower
    
    void draw() const;
    void update(float dt);
    void act(float dt);

    void add(Tower *tower);
    void set_wave(Wave *wave);
};
