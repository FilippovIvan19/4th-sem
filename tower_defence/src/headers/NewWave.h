#pragma once

#include "Unitpack.h"


class Wave
{
private:
    std::vector<Unitpack*> packs_;
public:

    Wave(const char *filename); // look wave constructor
   ~Wave(); // should delete every unitpack inside
    
    void draw() const;
    void update(float dt);
    void act(float dt);
};
