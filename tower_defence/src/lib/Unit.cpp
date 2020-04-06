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
    if (this->waypoint_.x == END_POINT.x && this->waypoint_.y == END_POINT.y)
        this->hurt(this->health_);
}

int sign(double exp)
{
    if (exp == 0)
        return 0;
    if (exp < 0)
        return -1;
    if (exp > 0)
        return 1;
}

using std::clog;
void Unit::move(float dt)
{
#ifdef DEBUG    
    clog << "move to " << waypoint_.x   << " " << waypoint_.y 
         << " from "   << this->get_x() << " " << this->get_y() << std::endl;
#endif
    if (waypoint_.x == this->get_x() && waypoint_.y == this->get_y())
    {
        this->update_way(map_);
#ifdef DEBUG
        clog << "current position " << get_x() << " " << get_y() << std::endl;
        printf("movecase 1\n");
#endif
    }
    else if (abs(waypoint_.x - this->get_x()) < 0.1 && abs(waypoint_.y - this->get_y()) < 0.1)
    {
        set_position(waypoint_.x, waypoint_.y);
#ifdef DEBUG
        printf("movecase 2\n");
#endif
    }
    else
    {
        set_position(
            this->get_x() + sign(waypoint_.x - this->get_x()) * this->velocity_ * dt,
            this->get_y() + sign(waypoint_.y - this->get_y()) * this->velocity_ * dt
        );
#ifdef DEBUG
        printf("movecase 3\n");
#endif
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