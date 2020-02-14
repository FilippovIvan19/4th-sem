#pragma once

#include "CommonElement.h"


class GameManager
{
public:
    GameManager();
   ~GameManager();

    std::set<CommonElement*> game_objects_;

    void add_obj(CommonElement *obj_ptr);
    void draw();
    void update(float dt);
    void act(float dt);
};
