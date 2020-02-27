#pragma once

#include "CommonElement.h"


class GameManager
{
private:
    std::set<CommonElement*> game_objects_;
public:
    GameManager();
   ~GameManager(); //deletes all objects inside!

    void add_obj(CommonElement *obj_ptr);
    void draw();
    void update(float dt);
    void act(float dt);
};
