#pragma once

#include "CommonElement.h"
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
public:
    Unit(sf::RenderWindow *window, Unit_kind kind,
        double health, float velocity, float x0, float y0,
        sf::Sprite sprite, float frame_width, float frame_height);
    Unit();
   ~Unit();

    void draw () const override;
    void    act (float dt) override; // moving, dying
    void update (float dt) override; // only visual

    void hurt(double damage);
    void move(float dt);
};