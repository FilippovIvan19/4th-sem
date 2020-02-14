#include "CommonElement.h"


CommonElement::CommonElement(sf::RenderWindow *window_ptr, float x0, float y0,
    sf::Sprite sprite, float frame_width, float frame_height):
x_(x0),
y_(y0),
sprite_(sprite),
frame_width_(frame_width),
frame_height_(frame_height),
window_ptr_(window_ptr),
frame_x_(0),
frame_y_(0)
{
    this->sprite_.setPosition(x0, y0);
    this->sprite_.setTextureRect(sf::IntRect(0, 0, frame_width_, frame_height_));
}

CommonElement::CommonElement():
x_(0),
y_(0),
sprite_(sf::Sprite()),
frame_width_(0),
frame_height_(0),
window_ptr_(nullptr),
frame_x_(0),
frame_y_(0)
{
    this->sprite_.setPosition(0, 0);
}

CommonElement::~CommonElement()
{}

void CommonElement::set_frame(int x, int y)
{
    this->sprite_.setTextureRect(sf::IntRect
        (frame_x_ * frame_width_, frame_y_ * frame_height_, frame_width_, frame_height_));
}

void CommonElement::set_position(float x, float y)
{
    this->x_ = x;
    this->y_ = y;
    this->sprite_.setPosition(x, y);
}

void CommonElement::draw() const
{
    this->window_ptr_->draw(this->sprite_);
}

