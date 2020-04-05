#include "../headers/Unit.h"


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
        sf::Sprite sprite, int pic_frame_width, int pic_frame_height, Map* map) :
CommonElement(window, x0, y0, sprite, pic_frame_width, pic_frame_height),
kind_ ( kind ),
health_ ( health ),
velocity_ ( velocity ),
alive_ ( true ),
cur_waypoint_ ( -1 ),
map_ (map)
{
    this->update_way(map);
    this->set_position(waypoint_.x, waypoint_.y);
}

Unit::~Unit()
{}

void Unit::update_way(Map* map)
{
    this->waypoint_ = map->next_turn(this->cur_waypoint_++);
}

void Unit::move(float dt)
{
    using std::clog;
    clog << "move to " << waypoint_.x   << " " << waypoint_.y 
         << " from "   << this->get_x() << " " << this->get_y() << std::endl;

    if (waypoint_.x == this->get_x() && waypoint_.y == this->get_y())
    {
        this->update_way(map_);
        clog << "current position " << get_x() << " " << get_y() << std::endl;
        printf("here 1\n");
    }
    else if(waypoint_.x - this->get_x() == 0)
    {
        if(waypoint_.y - this->get_y() != 0)
            this->set_position(this->get_x(), this->get_y() + 
            (waypoint_.y - this->get_y() < 0 ?
                -this->velocity_ * dt : this->velocity_ * dt)); 
        printf("here 2\n");
    }
    else if(waypoint_.y - this->get_y() == 0)
    {
        if(waypoint_.x - this->get_x() != 0)
            this->set_position(this->get_x() + 
            (waypoint_.x - this->get_x() < 0 ?
                -this->velocity_ * dt : this->velocity_ * dt), this->get_y()); 
        printf("here 3\n");
    }
}

void Unit::draw() const
{
    CommonElement::draw();
}

void Unit::act(float dt)
{
    this->move(dt);
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