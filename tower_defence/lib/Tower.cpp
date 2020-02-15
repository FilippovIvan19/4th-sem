#include "Tower.h"
#include <math.h>

Gun::Gun(sf::RenderWindow *window, float x0, float y0,
    sf::Sprite sprite, float frame_width, float frame_height):
CommonElement(window, x0, y0,   sprite,   frame_width,   frame_height)
{}

Gun::Gun():
CommonElement()
{}

Gun::~Gun()
{}

void Gun::rotate(CommonElement *target)
{
    if (!target)
        return;
    
    float dx = this->get_x() - target->get_x();
    float dy = this->get_y() - target->get_y();
    float angle = atan2(dx, dy) / M_PI * 180;
    this->sprite_.setRotation(angle);
}


Tower::Tower(sf::RenderWindow *window, Tower_kind kind, float attack_range, float x0, float y0,
    sf::Sprite   base_sprite, float   base_frame_width, float   base_frame_height,
    sf::Sprite    gun_sprite, float    gun_frame_width, float    gun_frame_height,
    sf::Sprite bullet_sprite, float bullet_frame_width, float bullet_frame_height,
    sf::Sprite   rank_sprite, float   rank_frame_width, float   rank_frame_height):
CommonElement(window, x0, y0,   base_sprite,   base_frame_width,   base_frame_height),
gun_(         window, x0, y0,    gun_sprite,    gun_frame_width,    gun_frame_height),
bullet_(      window, x0, y0, bullet_sprite, bullet_frame_width, bullet_frame_height),
rank_(        window, x0, y0,   rank_sprite,   rank_frame_width,   rank_frame_height),
rank_num_(0),
shoot_period_(0),
shoot_ago_(0),
kind_(kind),
target_(nullptr),
attack_range_(attack_range)
{
    this->rank_.set_position(this->get_x() + RANK_SPRITE_OFFSET_X,
                             this->get_y() + RANK_SPRITE_OFFSET_Y);
}

Tower::Tower():
CommonElement(),
gun_(),
bullet_(),
rank_(),
rank_num_(0),
shoot_period_(0),
shoot_ago_(0),
kind_((Tower_kind)0),
target_(nullptr),
attack_range_(0)
{}

Tower::~Tower()
{}

void Tower::act(float dt)
{
    this->find_target();
    this->shoot_ago_ += dt;
    if (this->shoot_ago_ >= this->shoot_period_ && this->target_)
    {
        this->shoot(this->target_);
        this->shoot_ago_ = 0;
    }

    /*
    this->gun_.act(dt);
    this->bullet_.act(dt);
    this->rank_.act(dt);
    */
}

void Tower::update(float dt)
{
    /*
    this->bullet_.update(dt);
    this->rank_.update(dt);
    this->gun_.update(dt);
    */

    this->gun_.rotate(this->target_);
}

void Tower::draw() const
{
    CommonElement::draw();
    this->gun_.draw();
    this->bullet_.draw();
    this->rank_.draw();
}

void Tower::find_target()
{
    ////////////////////////////
}