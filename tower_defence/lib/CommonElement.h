#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class CommonElement
{
public:
    
    CommonElement(sf::RenderWindow *window, float x0, float y0, 
        sf::Sprite sprite, float frame_width, float frame_height);
    CommonElement();
   ~CommonElement();

    float x_;
    float y_;
    float frame_width_;
    float frame_height_;
    sf::Sprite sprite_;
    sf::RenderWindow *window_ptr_;
    int frame_x_;
    int frame_y_;

    void set_frame(int x, int y);
    void set_position(float x, float y);

    virtual void draw() const;
    virtual void act(float dt) = 0;
    virtual void update(float dt) = 0;
};