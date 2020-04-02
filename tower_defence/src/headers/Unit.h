#pragma once

#include "CommonElement.h"
#include "Map.h"
#include "constants.h"


class Unit : public CommonElement
{
private:
    float x_;
    float y_;
    float velocity_;
    double health_;
    bool alive_;
    Unit_kind kind_;
    point waypoint_;
    int cur_waypoint_;
public:
    Unit(sf::RenderWindow *window, Unit_kind kind,
        double health, float velocity, float x0, float y0,
        sf::Sprite sprite, int pic_frame_width, int pic_frame_height);
    Unit(Unit_kind kind); // experimental
    Unit();
   ~Unit();

    void draw () const override;
    void    act (float dt) override; // moving, dying
    void update (float dt) override; // only visual

    void update_way(Map map, int n = -1);
    void hurt (double damage);
    void move (float dt);
};