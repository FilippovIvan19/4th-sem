#include "LevelIcon.h"

LevelIcon::LevelIcon() :
CommonElement(),
number_ ( 0 ),
locked_ (true),
score_ ( 0 )
{}

LevelIcon::LevelIcon(sf::RenderWindow *window, float x0, float y0, sf::Sprite sprite,
        int number, int pic_frame_width, int pic_frame_height) : 
CommonElement(window, x0, y0, sprite, pic_frame_width, pic_frame_height), 
number_ (number),
locked_ (true),
score_ ( 0 )
{
    // score_sprite_.setTextureRect(sf::IntRect(0 * this->number_, 0 * this->number_,0,0));
}

LevelIcon::~LevelIcon() {}

void LevelIcon::set_score(int score)
{
    this->score_ = score;
}

void LevelIcon::draw() const
{
    this->CommonElement::draw();
    // printf("%.2f %.2f\n", get_x(), get_y());
    // switch (this->score_)
    // {
    // case 0:
    //     // draw(this->score_sprite_.setTextureRect(
    //     //     sf::IntRect(0 * this->score_, 0 * this->score, 0, 0)));
    //     break;
    // case 1:
    //     // draw(this->score_sprite_.setTextureRect(
    //     //     sf::IntRect(0 * this->score_, 0 * this->score, 0, 0)));
    //     break;
    // case 2:
    //     // draw(this->score_sprite_.setTextureRect(
    //     //     sf::IntRect(0 * this->score_, 0 * this->score, 0, 0)));
    //     break;
    // case 3:
    //     // draw(this->score_sprite_.setTextureRect(
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