#pragma once

#include "CommonElement.h"
#include "Map.h"
#include "constants.h"


class Unit : public CommonElement
{
private:
    float velocity_;
    double health_;
    bool alive_;
    Unit_kind kind_;
    Map *map_;
public:
    point waypoint_;
    int cur_waypoint_;

    Unit(sf::RenderWindow *window, Unit_kind kind,
        double health, float velocity, float x0, float y0,
        sf::Sprite sprite, int pic_frame_width, int pic_frame_height, Map *map);
    // Unit(Unit_kind kind); // experimental
    Unit();
   ~Unit();

    bool is_alive() const;
    
    void spawn();
    void update_way(Map* map);
    void hurt (double damage);
    void move (float dt);
    float cur_waypoint_distance();

    void draw () const override;
    void    act (float dt) override; // moving, dying
    void update (float dt) override; // only visual
};
