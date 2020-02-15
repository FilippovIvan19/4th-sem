#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "constants.h"


class CommonElement
{
private:
    float x_;
    float y_;
    float frame_width_;
    float frame_height_;
    // float frame_chanched_ago_;
    sf::RenderWindow *window_;
    int frame_x_;
    int frame_y_;
    bool visibility_;
protected:
    sf::Sprite sprite_;
public:
    CommonElement(sf::RenderWindow *window, float x0, float y0, 
        sf::Sprite sprite, float frame_width, float frame_height);
    CommonElement();
   ~CommonElement();

    void set_visibility(bool visibility);
    void set_frame(int x, int y);
    void set_position(float x, float y);
    float get_x() const;
    float get_y() const;

    virtual void draw() const;
    virtual void    act(float dt);
    virtual void update(float dt); //visual part only
};