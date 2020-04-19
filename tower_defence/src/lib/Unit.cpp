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
// Unit::Unit(Unit_kind kind) :
// Unit()
// {
//     kind_ = kind;
// }

Unit::Unit(sf::RenderWindow *window, Unit_kind kind,
        double health, float velocity, float x0, float y0,
        sf::Sprite sprite, int pic_frame_width, int pic_frame_height, Map *map) :
        // TODO: change use of x0 y0
CommonElement(window, x0, y0, sprite, pic_frame_width, pic_frame_height),
kind_ ( kind ),
health_ ( health ),
velocity_ ( velocity ),
alive_ ( false ),
cur_waypoint_ ( -1 ),
map_ (map)
{
    this->update_way(this->map_);
}

Unit::~Unit()
{}

bool Unit::is_alive() const { return this->alive_; }

void Unit::update_way(Map* map)
{
    this->waypoint_ = map->next_turn(this->cur_waypoint_++);
    if (this->waypoint_ == END_POINT)
    {
        this->hurt(this->health_);
        this->map_->damage_hq();
    }
}

// TODO(optional): find alternative in c++ std lib
int sign(double exp)
{
    return exp == 0 ? 0 : exp/abs(exp);
}

void Unit::move(float dt)
{
// #ifdef DEBUG
//     std::clog << "move to " << waypoint_.x   << " " << waypoint_.y 
//               << " from "   << this->get_x() << " " << this->get_y() << std::endl;
// #endif
    // printf("moving to %d %d from %f %f\n", waypoint_.x, waypoint_.y, this->get_x(), this->get_y());
    // TODO: fix comparing 'point' objects
    if (waypoint_.x == this->get_x() && waypoint_.y == this->get_y())
    {
        this->update_way(this->map_);
        // printf("movecase 1\n");
// #ifdef DEBUG
//         std::clog << "movecase 1\ncurrent position " << get_x() << " " << get_y() << std::endl;
// #endif
    }
    else if (abs(waypoint_.x - this->get_x()) < 0.1 && abs(waypoint_.y - this->get_y()) < 0.1)
    {
        set_position(waypoint_.x, waypoint_.y);
        // printf("movecase 2\n");
    }
    else
    {
        set_position(
            this->get_x() + sign(waypoint_.x - this->get_x()) * this->velocity_ * dt,
            this->get_y() + sign(waypoint_.y - this->get_y()) * this->velocity_ * dt
        );
        // printf("movecase 3\n");
    }
}

void Unit::hurt(double damage)
{
    this->health_ -= damage;
    if (this->health_ <= 0)
    {
        this->set_visibility(false);
        this->alive_ = false;
    }
}

void Unit::spawn()
{
    this->set_position(this->waypoint_.x,this->waypoint_.y);
    this->alive_ = true;
}

void Unit::draw() const
{
    if (this->alive_)
        CommonElement::draw();
}

void Unit::act(float dt)
{
    if (this->alive_)
        this->move(dt);
}

void Unit::update(float dt)
{
    // if (this->alive_)
}

float Unit::cur_waypoint_distance()
{
    return abs(this->waypoint_.x - this->get_x() + this->waypoint_.y - this->get_y());
}
