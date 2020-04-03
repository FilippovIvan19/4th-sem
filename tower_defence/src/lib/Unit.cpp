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
cur_waypoint_ ( 0 ),
map_ (map)
{
    this->update_way(map);
}

Unit::~Unit()
{}

void Unit::update_way(Map* map)
{
    this->waypoint_ = map->next_turn(this->cur_waypoint_);
}

void Unit::move(float dt)
{
    printf("move to %d %d from %d %d\n", waypoint_.x, waypoint_.y, this->x_, this->y_);
    if (waypoint_.x == this->x_ && waypoint_.y == this->y_)
    {
        this->update_way(map_);
        printf("current position %d %d\n", x_, y_);
        printf("here 1\n");
    }
    else if(waypoint_.x - this->x_ == 0)
    {
        if(waypoint_.y - this->y_ != 0)
            this->y_ += waypoint_.y - this->y_ > 0 ?
                -this->velocity_ * dt : this->velocity_ * dt; 
        printf("here 2\n");
    }
    else if(waypoint_.y - this->y_ == 0)
    {
        if(waypoint_.x - this->x_ != 0)
            this->x_ += waypoint_.x - this->x_ > 0 ?
                -this->velocity_ * dt : this->velocity_ * dt;   
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
