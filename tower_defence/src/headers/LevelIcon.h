#pragma once 

#include "constants.h"
#include "CommonElement.h"


class LevelIcon : public CommonElement
{
private:
    // sf::RenderWindow window_;

    int number_;
    bool locked_;

    CommonElement lock_elem_;
    CommonElement number_elem_;
    sf::Text number_text_;
    // CommonElement score_elem_;
public:
    LevelIcon();
    LevelIcon(sf::RenderWindow *window, float x0, float y0, all_sprites *sprites,
        int number, int pic_frame_width, int pic_frame_height, sf::Font *font);
   ~LevelIcon();

    void draw() const override;
    void set_lock(bool value);
    bool is_locked() const;
};
