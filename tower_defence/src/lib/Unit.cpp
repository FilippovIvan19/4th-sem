#include "../headers/Unit.h"
#include "../headers/Level.h"

#include <iostream>




HealthBar::HealthBar(sf::RenderWindow *window, float x0, float y0,
    sf::Sprite sprite, int pic_frame_width, int pic_frame_height) :
CommonElement(window, x0, y0, sprite, pic_frame_width, pic_frame_height),
health_percent_(0)
{
    this->set_origin_zero(this->sprite_.getTextureRect().width / 2, this->sprite_.getTextureRect().height);
}

HealthBar::HealthBar() :
CommonElement(),
health_percent_(0)
{}

HealthBar::~HealthBar()
{}

void HealthBar::set_percent(int percent)
{
    this->health_percent_ = percent;
    
    this->sprite_.setTextureRect(sf::IntRect((100 - percent) * this->sprite_.getTextureRect().width / 100, 0,
        this->sprite_.getTextureRect().width, this->sprite_.getTextureRect().height));
}



Unit::Unit() :
CommonElement(),
health_bar_(),
health_ ( 0 ),
spawn_health_ ( 0 ),
velocity_ ( 0 ),
alive_ ( false ),
cur_waypoint_ ( 0 ),
cost_(0),
prev_dist_x_(0),
prev_dist_y_(0),
power_(0)
{}

Unit::Unit(sf::RenderWindow *window, double health, float velocity, int cost,
         int power, float x0, float y0, sf::Sprite sprite, sf::Sprite health_sprite, 
         int pic_frame_width, int pic_frame_height, Level *level) :
CommonElement(window, x0, y0, sprite, pic_frame_width, pic_frame_height),
health_bar_(window, x0, y0, health_sprite, HEALTH_BAR_PIC_WIDTH, HEALTH_BAR_PIC_HEIGHT),\
health_ ( health ),
spawn_health_ ( health ),
velocity_ ( velocity * CELL_SIZE ),
alive_ ( false ),
cur_waypoint_ ( -1 ),
level_ (level),
cost_(cost),
prev_dist_x_(0),
prev_dist_y_(0),
power_(power)
{
    this->update_way();
    this->health_bar_.set_position(this->get_center_x(), this->get_y());
}

Unit::~Unit()
{}

bool Unit::is_alive() const { return this->alive_; }

void Unit::update_way()
{
    this->waypoint_ = this->level_->map_.next_turn(this->cur_waypoint_++);
    if (this->waypoint_ == END_POINT)
    {
        this->die();
        this->level_->damage_hq(this->power_);
    }
}

// TODO(optional): find alternative in c++ std lib
int sign(double exp)
{
    return exp == 0 ? 0 : exp/std::abs(exp);
}

void Unit::move(float dt)
{
    float dist_x = waypoint_.x - this->get_x();
    float dist_y = waypoint_.y - this->get_y();
    
    if (dist_x * prev_dist_x_ + dist_y * prev_dist_y_ < 0 || dist_x + dist_y == 0)
    {
        this->set_position(waypoint_.x, waypoint_.y);
        this->update_way();
        dt += std::abs(dist_x + dist_y) / this->velocity_;
    }

    set_position(
        this->get_x() + sign(waypoint_.x - this->get_x()) * this->velocity_ * dt,
        this->get_y() + sign(waypoint_.y - this->get_y()) * this->velocity_ * dt
    );
    this->health_bar_.set_position(this->get_center_x(), this->get_y());

    prev_dist_x_ = dist_x;
    prev_dist_y_ = dist_y;
}

void Unit::hurt(double damage)
{
    this->health_ -= damage;
    if (this->health_ <= 0)
        this->health_ = 0;
    this->health_bar_.set_percent((int)(this->health_ * 100 / this->spawn_health_));
    if (this->health_ <= 0)
    {
        if (this->alive_)
            this->level_->add_coins(this->cost_);
        this->die();
    }
}

void Unit::die()
{
    this->set_visibility(false);
    this->alive_ = false;
}

void Unit::spawn()
{
    this->set_position(this->waypoint_.x,this->waypoint_.y);
    this->alive_ = true;
}

void Unit::draw() const
{
    if (this->alive_)
    {
        CommonElement::draw();
    }
}

void Unit::draw_bar() const
{
    if (this->alive_)
    {
        this->health_bar_.draw();
    }
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
    return std::abs(this->waypoint_.x - this->get_x() + this->waypoint_.y - this->get_y());
}
