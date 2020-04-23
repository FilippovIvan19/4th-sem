#include "../headers/CommonElement.h"


CommonElement::CommonElement(sf::RenderWindow *window, float x0, float y0,
    sf::Sprite sprite, int pic_frame_width, int pic_frame_height):
x_(x0),
y_(y0),
sprite_(sprite),
visibility_(true),
window_(window)
{
    this->sprite_.setPosition(x0, y0);
    this->sprite_.setTextureRect(sf::IntRect(0, 0, pic_frame_width, pic_frame_height));
}

CommonElement::CommonElement():
x_(0),
y_(0),
sprite_(sf::Sprite()),
visibility_(false),
window_(nullptr)
{
    this->sprite_.setPosition(0, 0);
}

CommonElement::~CommonElement()
{}

void CommonElement::set_frame(int x, int y)
{
    this->sprite_.setTextureRect(sf::IntRect
        (x * this->sprite_.getTextureRect().width, y * this->sprite_.getTextureRect().height, 
        this->sprite_.getTextureRect().width, this->sprite_.getTextureRect().height));
}

void CommonElement::set_visibility(bool visibility)
{
    this->visibility_ = visibility;
}

void CommonElement::set_position(float x, float y)
{
    this->x_ = x;
    this->y_ = y;
    this->sprite_.setPosition(x, y);
}

void CommonElement::draw() const
{
    if (this->visibility_)
        this->window_->draw(this->sprite_);
}

float CommonElement::get_x() const
{
    return this->x_;
}

float CommonElement::get_y() const
{
    return this->y_;
}

float CommonElement::get_center_x() const
{
    return this->x_ + this->sprite_.getGlobalBounds().width / 2;
}

float CommonElement::get_center_y() const
{
    return this->y_ + this->sprite_.getGlobalBounds().height / 2;
}

void CommonElement::set_origin_center()
{
    this->sprite_.setOrigin(this->sprite_.getTextureRect().width / 2,
        this->sprite_.getTextureRect().height / 2);
}

void CommonElement::set_origin_zero(float new_x, float new_y)
{
    this->sprite_.setOrigin(new_x, new_y);
}

void CommonElement::scale(float factorX, float factorY)
{
    this->sprite_.scale(factorX, factorY);
}

void CommonElement::update(float dt)
{}

void CommonElement::act(float dt)
{}
