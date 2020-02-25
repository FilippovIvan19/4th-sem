#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "constants.h"


class CommonElement
{
private:
    float x_;
    float y_;
    int frame_width_;
    int frame_height_;
    // float frame_chanched_ago_;
    sf::RenderWindow *window_;
    bool visibility_;
protected:
    sf::Sprite sprite_;
public:
    CommonElement(sf::RenderWindow *window, float x0, float y0, 
        sf::Sprite sprite, int frame_width, int frame_height);
    CommonElement();
   ~CommonElement();

    void set_visibility(bool visibility);
    void set_frame(int x, int y);
    void set_position(float x, float y);
    void set_origin_center();
    void set_origin_zero();
    void set_scale(float factorX, float factorY);
    float get_x() const;
    float get_y() const;

    virtual void draw() const;
    virtual void    act(float dt); //all inner logic & calls functions like moving, shooting etc
    virtual void update(float dt); //visual part only i.e. desribes frame changing behavior
};
