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
    LevelIcon(sf::RenderWindow *window, float x0, float y0, sf::Sprite sprite,
        int number, int pic_frame_width, int pic_frame_height);
   ~LevelIcon();

    void draw() const override;
    void set_lock(bool value);
    bool is_locked() const;
    void set_score(int score);
};