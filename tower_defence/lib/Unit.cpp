#include "Unit.h"


Unit::Unit()
{}

Unit::Unit(sf::RenderWindow *window, Unit_kind kind,
        double health, float velocity, float x0, float y0,
        sf::Sprite sprite, float frame_width, float frame_height):
CommonElement(window, x0, y0, sprite, frame_width, frame_height),
kind_ { kind },
health_ { health },
velocity_ { velocity },
alive_ { true }
{}

Unit::~Unit()
{}

void Unit::draw() const
{
    CommonElement::draw();
}

void Unit::act(float dt)
{
    while(alive_)
    {
        move();
    }
}

void Unit::hurt(double damage)
{
    health_ -= damage;
    if(health_ <= 0)
        this->set_visibility(false);
}