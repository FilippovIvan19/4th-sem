#pragma once 

#include "constants.h"
#include "CommonElement.h"


class LevelIcon : public CommonElement
{
private:
    sf::Sprite number_;
    sf::Sprite score_;
    bool locked_;
public:
    LevelIcon();
    LevelIcon(sf::RenderWindow *window, sf::Sprite sprite, sf::Sprite score_sprite,
        float frame_width, float frame_height);
   ~LevelIcon();

    void draw() const override;
};