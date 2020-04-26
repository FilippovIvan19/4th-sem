#include "../headers/LevelIcon.h"

LevelIcon::LevelIcon() :
CommonElement(),
number_ ( 0 ),
locked_ (true)
// score_ ( 0 )
{}

LevelIcon::LevelIcon(sf::RenderWindow *window, float x0, float y0, all_sprites *sprites,
        int number, int pic_frame_width, int pic_frame_height) : 
CommonElement(window, x0, y0, *sprites->level_icon_sprite, pic_frame_width, pic_frame_height), 
number_ (number),
locked_ (true),
// score_ ( 0 ),
lock_elem_(window, x0 + LEVEL_ICON_SIZE / 2, y0 + LEVEL_ICON_SIZE / 2,
    *sprites->lock_sprite, LEVEL_LOCK_PIC_SIZE, LEVEL_LOCK_PIC_SIZE)
{
    this->lock_elem_.set_origin_center();
    // score_.setTextureRect(sf::IntRect(0 * this->number_, 0 * this->number_,0,0));
}

LevelIcon::~LevelIcon() {}

// void LevelIcon::set_score(int score)
// {
//     this->score_ = score;
// }

void LevelIcon::draw() const
{
    this->CommonElement::draw();
    if (this->locked_)
        this->lock_elem_.draw();
    // printf("%.2f %.2f\n", get_x(), get_y());
    // switch (this->score_)
    // {
    // case 0:
    //     // draw(this->score_.setTextureRect(
    //     //     sf::IntRect(0 * this->score_, 0 * this->score, 0, 0)));
    //     break;
    // case 1:
    //     // draw(this->score_.setTextureRect(
    //     //     sf::IntRect(0 * this->score_, 0 * this->score, 0, 0)));
    //     break;
    // case 2:
    //     // draw(this->score_.setTextureRect(
    //     //     sf::IntRect(0 * this->score_, 0 * this->score, 0, 0)));
    //     break;
    // case 3:
    //     // draw(this->score_.setTextureRect(
    //     //     sf::IntRect(0 * this->score_, 0 * this->score, 0, 0)));
    //     break;
    // default:
    //     break;
    // }
}

void LevelIcon::set_lock(bool value)
{
    this->locked_ = value;
}

bool LevelIcon::is_locked() const
{
    return this->locked_;
}