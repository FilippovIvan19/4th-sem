#pragma once

#include "CommonElement.h"


class Gun : public CommonElement
{
public:
    Gun(sf::RenderWindow *window, float x0, float y0,
        sf::Sprite sprite, int frame_width, int frame_height);
    Gun();
   ~Gun();
    
    void rotate(CommonElement *target);

    // void    act(float dt) override;
    // void update(float dt) override;
};


class Tower : public CommonElement
{
private:
    Gun gun_;
    
    int rank_num_;
    CommonElement rank_;
    CommonElement bullet_;

    float shoot_period_;
    float shoot_ago_;
    float attack_range_;
    Tower_kind kind_;
    CommonElement *target_;
public:
    Tower(sf::RenderWindow *window, Tower_kind kind, float attack_range, float x0, float y0,
        sf::Sprite   base_sprite, int   base_frame_width, int   base_frame_height,
        sf::Sprite    gun_sprite, int    gun_frame_width, int    gun_frame_height,
        sf::Sprite bullet_sprite, int bullet_frame_width, int bullet_frame_height,
        sf::Sprite   rank_sprite, int   rank_frame_width, int   rank_frame_height);
    Tower();
   ~Tower();

    void    act(float dt) override; //shooting
    void update(float dt) override; //gun rotation
    void draw() const override;
    void find_target();

    virtual void shoot(CommonElement *target) = 0;
};