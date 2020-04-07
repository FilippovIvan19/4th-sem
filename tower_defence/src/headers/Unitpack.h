#pragma once

#include "Unit.h"


class Unitpack
{
private:
    std::vector<Unit*> units_;
    float spawn_delta_;
    float spawn_delay_;
public:
    Unitpack(std::string &unit_name, int unit_count, float spawn_delta, float spawn_delay); // look wave::create_unitpack
    Unitpack();
   ~Unitpack(); // should delete every unit inside
    
    void draw() const;
    void update(float dt);
    void act(float dt);
};
