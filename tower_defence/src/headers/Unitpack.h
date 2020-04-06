#pragma once

#include "Unit.h"


class Unitpack
{
private:
    std::vector<Unit*> units_;
    float spawn_dt_;
public:
    Unitpack(std::string &unit_name, int unit_count, float spawn_dt); // look wave::create_unitpack
   ~Unitpack(); // should delete every unit inside
    
    void draw() const;
    void update(float dt);
    void act(float dt);
};
