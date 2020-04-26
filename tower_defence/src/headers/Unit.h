#pragma once

#include "CommonElement.h"
#include "constants.h"
class Level;


class HealthBar : public CommonElement
{
private:
    int health_percent_;
public:
    HealthBar(sf::RenderWindow *window, float x0, float y0,
    sf::Sprite sprite, int pic_frame_width, int pic_frame_height);
    HealthBar();
   ~HealthBar();
    
    void set_percent(int percent);
};


class Unit : public CommonElement
{
private:
    float velocity_;
    double health_;
    double spawn_health_;
    bool alive_;
    Unit_kind kind_;
    Level *level_;
    int cost_;
    float prev_dist_x_;
    float prev_dist_y_;
    int power_;
    HealthBar health_bar_;
public:
    point waypoint_;
    int cur_waypoint_;

    Unit(sf::RenderWindow *window, Unit_kind kind,
        double health, float velocity, int cost, int power, float x0, float y0,
        sf::Sprite sprite, sf::Sprite health_sprite, int pic_frame_width, int pic_frame_height, Level *level);
    // Unit(Unit_kind kind); // experimental
    Unit();
   ~Unit();

    bool is_alive() const;
    
    void spawn();
    void die();
    void update_way();
    void hurt (double damage);
    void move (float dt);
    float cur_waypoint_distance();

    void draw () const override;
    void draw_bar() const;
    void    act (float dt) override; // moving, dying
    void update (float dt) override; // only visual
};
