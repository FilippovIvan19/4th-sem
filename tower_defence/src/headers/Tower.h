#pragma once

#include <queue>
#include <set>

#include "CommonElement.h"
#include "constants.h"

#include "../headers/audio.h"

class Unit;
class Wave;


class Gun : public CommonElement
{
public:
    Gun(sf::RenderWindow *window, float x0, float y0,
        sf::Sprite sprite, int pic_frame_width, int pic_frame_height);
    Gun();
   ~Gun();
    
    void rotate(Unit *target);
};

class Bullet : public CommonElement
{
public:
    Bullet(sf::RenderWindow *window, float x0, float y0,
        sf::Sprite sprite, int pic_frame_width, int pic_frame_height);
    Bullet();
   ~Bullet();
    
    Unit *target_;
};


class Tower : public CommonElement
{
protected:
    Gun gun_;
    CommonElement rank_;
    std::queue<Bullet*> free_bullets_;
    std::set<Bullet*> active_bullets_;
private:
    int rank_num_;
    float shoot_period_;
    float shoot_ago_;
    float attack_range_;
    Unit *target_;
    int power_;
    Sound* shoot_;
public:
    Tower(sf::RenderWindow *window, float attack_range,
        float shoot_period, double power, float x0, float y0,
        sf::Sprite   base_sprite, int   base_frame_width, int   base_frame_height,
        sf::Sprite    gun_sprite, int    gun_frame_width, int    gun_frame_height,
        sf::Sprite bullet_sprite, int bullet_frame_width, int bullet_frame_height,
        sf::Sprite   rank_sprite, int   rank_frame_width, int   rank_frame_height);
    Tower();
   ~Tower(); // deletes bullets

    void    act(float dt) override; //shooting
    void update(float dt) override; //gun rotation
    void draw() const override;
    void find_target(Wave *wave);

    virtual void shoot();
    bool is_available(Unit *target) const;
    void move_bullets(float dt);
};
