#pragma once 

#include "constants.h"
#include "CommonElement.h"


class LevelIcon : public CommonElement
{
private:
    int number_;
    int score_;
    bool locked_;

    sf::Sprite number_sprite_;
    sf::Sprite score_sprite_;
public:
    LevelIcon();
    LevelIcon(sf::RenderWindow *window, sf::Sprite sprite,
        int number, float frame_width, float frame_height);
   ~LevelIcon();

    void draw() const override;
    void set_score(int score);
};