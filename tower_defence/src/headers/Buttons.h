#pragma once

#include "Cell.h"
#include "constants.h"


class Buttons // just for drawing button icons
{
private:
    Cell button_array_[MAP_HEIGHT];
    Cell background_[MAP_HEIGHT];
    sf::Text labels_[MAP_HEIGHT];
    sf::Text hints_[MAP_HEIGHT];
    int cur_hint_;
    sf::RenderWindow* window_;
    static sf::Text make_coins_text(std::string str, sf::Font *font, int row);
    static sf::Text make_hint(std::string str, sf::Font *font, int row);

public:
    enum Order {
        Pause = 0,
        SpeedUp,

        PillTower = 3,
        CapsuleTower,

        Coins = 6,
        Health = 8,

        Restart = MAP_HEIGHT - 3,
        Menu,
        Exit,
    };

    Buttons();
    Buttons(sf::RenderWindow* window, sf::Sprite buttons_sprite, sf::Font *font);
   ~Buttons();

    void draw() const;
    void highlight(int num);
    void darken(int num);
    void set_coins(int count);
    void set_health(int count);

    void help();
};
