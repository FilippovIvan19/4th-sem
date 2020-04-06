#pragma once

#include "Cell.h"


class Buttons // just for drawing button icons
{
private:
    Cell button_array_[MAP_HEIGHT];

public:
    Buttons();
    Buttons(sf::RenderWindow* window, sf::Sprite buttons_sprite);
   ~Buttons();

    void draw() const;
    void highlight(int num);
    void darken(int num);
};
