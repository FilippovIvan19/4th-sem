#include "../headers/Tower.h"
#include <math.h>

Gun::Gun(sf::RenderWindow *window, float x0, float y0,
    sf::Sprite sprite, int pic_frame_width, int pic_frame_height):
CommonElement(window, x0, y0,   sprite,   pic_frame_width,   pic_frame_height)
{}

Gun::Gun():
CommonElement()
{}

Gun::~Gun()
{}

void Gun::rotate(Unit *target)
{
    if (!target)
        return;
    
    float dx = this->get_x() - target->get_center_x();
    float dy = this->get_y() - target->get_center_y();
    float angle = atan2(dx, dy) / M_PI * 180;
    this->sprite_.setRotation(-angle);
}


Tower::Tower(sf::RenderWindow *window, Tower_kind kind, float attack_range, float x0, float y0,
    sf::Sprite   base_sprite, int   base_frame_width, int   base_frame_height,
    sf::Sprite    gun_sprite, int    gun_frame_width, int    gun_frame_height,
    sf::Sprite bullet_sprite, int bullet_frame_width, int bullet_frame_height,
    sf::Sprite   rank_sprite, int   rank_frame_width, int   rank_frame_height):
CommonElement(window, x0, y0,   base_sprite,   base_frame_width,   base_frame_height),
gun_(         window, x0, y0,    gun_sprite,    gun_frame_width,    gun_frame_height),
bullet_(      window, x0, y0, bullet_sprite, bullet_frame_width, bullet_frame_height),
rank_(        window, x0, y0,   rank_sprite,   rank_frame_width,   rank_frame_height),
rank_num_(0),
shoot_period_(3),
shoot_ago_(0),
kind_(kind),
target_(nullptr),
attack_range_(attack_range),
is_shooting_(false),
power_(0)
{
    this->rank_.set_position(this->get_x() + RANK_SPRITE_OFFSET_X,
                             this->get_y() + RANK_SPRITE_OFFSET_Y);
    this->gun_.set_origin_center();
    this->bullet_.set_origin_center();
    this->   gun_.set_position(x0 + CELL_SIZE / 2, y0 + CELL_SIZE / 2);
    this->bullet_.set_visibility(false);
    this->bullet_.set_position(this->get_x(), this->get_y());
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
attack_range_(0),
is_shooting_(false),
power_(0)
{}

Tower::~Tower()
{}

void Tower::act(float dt)
{
    this->shoot_ago_ += dt;
    if (this->shoot_ago_ >= this->shoot_period_ && this->target_)
    {
        this->shoot();
        this->shoot_ago_ = 0;
    }

    if (this->is_shooting_)
        this->move_bullet(dt);
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

void Tower::find_target(Wave *wave)
{
    if (!wave)
        return;
    int count = wave->packs_.size();
    Unit **target_candidates = new Unit* [count] {nullptr};

    for (int i = 0; i < count; i++)
    {
        Unitpack *cur_pack = wave->packs_[i];
        for (int j = 0; j < cur_pack->units_.size(); j++)
        {
            Unit *cur_unit = cur_pack->units_[j];
            if (cur_unit->is_alive() && this->is_available(cur_unit))
            {
                target_candidates[i] = cur_unit;
                break;
            }
        }
    }

    Unit *target = nullptr;
    for (int i = 0; i < count; i++)
    {
        if (!target)
        {
            target = target_candidates[i];
        }
        else
        {
            if (target_candidates[i])
            {
                if (target_candidates[i]->cur_waypoint_ > target->cur_waypoint_)
                {
                    target = target_candidates[i];
                }
                else
                {
                    if (target_candidates[i]->cur_waypoint_ == target->cur_waypoint_)
                    {
                        if (target_candidates[i]->cur_waypoint_distance() < target->cur_waypoint_distance())
                        {
                            target = target_candidates[i];
                        }
                    }
                }
            }
        }
    }
    this->target_ = target;
}

bool Tower::is_available(Unit *target)
{
    float r2 = pow(this->get_x() - target->get_x(), 2) + pow(this->get_y() - target->get_y(), 2);
    return r2 <= pow(this->attack_range_, 2);
}

void Tower::shoot()
{
    this->bullet_target_ = this->target_;
    this->is_shooting_ = true;
    this->bullet_.set_visibility(true);
}

void Tower::move_bullet(float dt)
{
    float x = this->bullet_.get_x();
    float y = this->bullet_.get_y();
    float x1 = this->bullet_target_->get_center_x();
    float y1 = this->bullet_target_->get_center_y();

    float r = sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));

    if (r <= this->bullet_.get_center_x() - this->bullet_.get_x())
    {
        this->bullet_.set_position(this->get_center_x(), this->get_center_y());
        this->bullet_.set_visibility(false);
        this->is_shooting_ = false;
        this->bullet_target_->hurt(this->power_);
    }
    else
    {
        this->bullet_.set_position(
            this->bullet_.get_x() + BULLET_SPEED * dt / r * (x1 - x),
            this->bullet_.get_y() + BULLET_SPEED * dt / r * (y1 - y)
        );
    }

    
}
