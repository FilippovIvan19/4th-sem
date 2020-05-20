#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class CommonElement
{
private:
    float x_;
    float y_;
    bool visibility_;
protected:
    sf::RenderWindow *window_;
    sf::Sprite sprite_;
public:
    CommonElement(sf::RenderWindow *window, float x0, float y0, 
        sf::Sprite sprite, int pic_frame_width, int pic_frame_height);
    CommonElement();
    virtual
   ~CommonElement();

    void set_visibility(bool visibility);
    void set_frame(int x, int y);
    void set_position(float x, float y);
    void set_origin_center();
    void set_origin_zero(float new_x = 0, float new_y = 0);
    void scale(float factorX, float factorY);
    float get_x() const;
    float get_y() const;
    float get_center_x() const;
    float get_center_y() const;

    virtual void draw() const;
    virtual void    act(float dt); //all inner logic & calls functions like moving, shooting etc
    virtual void update(float dt); //visual part only i.e. desribes frame changing behavior
};
