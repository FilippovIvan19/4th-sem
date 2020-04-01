#include "Unit.h"


Unit::Unit() :
CommonElement(),
kind_ ( (Unit_kind)0 ),
health_ ( 0 ),
velocity_ ( 0 ),
alive_ ( false ),
cur_waypoint_ ( 0 )
{}

// experimental
Unit::Unit(Unit_kind kind) :
Unit()
{
    kind_ = kind;
}

Unit::Unit(sf::RenderWindow *window, Unit_kind kind,
        double health, float velocity, float x0, float y0,
        sf::Sprite sprite, int pic_frame_width, int pic_frame_height) :
CommonElement(window, x0, y0, sprite, pic_frame_width, pic_frame_height),
kind_ ( kind ),
health_ ( health ),
velocity_ ( velocity ),
alive_ ( true ),
cur_waypoint_ ( 0 )
{}

Unit::~Unit()
{}

void Unit::set_way(Map map, int n)
{
    this->waypoint_ = map.next_turn(n);
}

void Unit::move(float dt)
{
    if(abs(waypoint_.x - x_) == 0);
}

void Unit::draw() const
{
    CommonElement::draw();
}

void Unit::act(float dt)
{
    // this->move(dt);
}

void Unit::update(float dt)
{
    //
}

void Unit::hurt(double damage)
{
    this->health_ -= damage;
    if(this->health_ <= 0)
    {
        this->set_visibility(false);
        this->alive_ = false;
    }
}
