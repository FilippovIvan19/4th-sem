#pragma once

#include "Cell.h"


class Buttons // just for drawing button icons

{
private:
    Cell button_array_[MAP_HEIGHT];
    Cell background_[MAP_HEIGHT];
    // create enum to use as index instead of numbers e.g.:
    enum Order {
        Pause = 0,
        // Play,
        SpeedUp,
        Restart = MAP_HEIGHT - 3,
        Menu,
        Exit,
    };

public:
    Buttons();
    Buttons(sf::RenderWindow* window, sf::Sprite buttons_sprite);
   ~Buttons();

    void draw() const;
    void highlight(int num);
    void darken(int num);
};
