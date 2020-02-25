#include "LevelIcon.h"

LevelIcon::LevelIcon() :
CommonElement(),
number_ ( 0 ),
locked_ (true),
score_ ( 0 )
{}

LevelIcon::LevelIcon(sf::RenderWindow *window, sf::Sprite sprite,
        int number, float frame_width, float frame_height) : 
CommonElement(window, 0, 0, sprite, frame_width, frame_height), 
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
    switch (this->score_)
    {
    case 0:
        // draw(this->score_sprite_.setTextureRect(
        //     sf::IntRect(0 * this->score_, 0 * this->score, 0, 0)));
        break;
    case 1:
        // draw(this->score_sprite_.setTextureRect(
        //     sf::IntRect(0 * this->score_, 0 * this->score, 0, 0)));
        break;
    case 2:
        // draw(this->score_sprite_.setTextureRect(
        //     sf::IntRect(0 * this->score_, 0 * this->score, 0, 0)));
        break;
    case 3:
        // draw(this->score_sprite_.setTextureRect(
        //     sf::IntRect(0 * this->score_, 0 * this->score, 0, 0)));
        break;
    default:
        break;
    }
}
