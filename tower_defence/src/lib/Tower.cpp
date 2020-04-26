#include "../headers/Tower.h"
#include "../headers/Unit.h"
#include "../headers/Wave.h"
#include "../headers/Unitpack.h"
#include <math.h>

Gun::Gun(sf::RenderWindow *window, float x0, float y0,
    sf::Sprite sprite, int pic_frame_width, int pic_frame_height):
CommonElement(window, x0, y0, sprite, pic_frame_width, pic_frame_height)
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


Bullet::Bullet(sf::RenderWindow *window, float x0, float y0,
    sf::Sprite sprite, int pic_frame_width, int pic_frame_height):
CommonElement(window, x0, y0, sprite, pic_frame_width, pic_frame_height),
target_(nullptr)
{
    this->set_origin_center();
    this->set_visibility(false);
}

Bullet::Bullet():
CommonElement(),
target_(nullptr)
{}

Bullet::~Bullet()
{}


Tower::Tower(sf::RenderWindow *window, float attack_range,
    float shoot_period, double power, float x0, float y0,
    sf::Sprite   base_sprite, int   base_frame_width, int   base_frame_height,
    sf::Sprite    gun_sprite, int    gun_frame_width, int    gun_frame_height,
    sf::Sprite bullet_sprite, int bullet_frame_width, int bullet_frame_height,
    sf::Sprite   rank_sprite, int   rank_frame_width, int   rank_frame_height) :
CommonElement(window, x0, y0,   base_sprite,   base_frame_width,   base_frame_height),
gun_(         window, x0, y0,    gun_sprite,    gun_frame_width,    gun_frame_height),
rank_(        window, x0, y0,   rank_sprite,   rank_frame_width,   rank_frame_height),
free_bullets_(std::queue<Bullet*> ()),
active_bullets_(std::set<Bullet*> ()),
rank_num_(0),
shoot_period_(shoot_period),
shoot_ago_(0),
attack_range_(attack_range),
target_(nullptr),
power_(power)
{
    this->rank_.set_position(this->get_x() + RANK_SPRITE_OFFSET_X,
                             this->get_y() + RANK_SPRITE_OFFSET_Y);
    this->gun_.set_origin_center();
    this->   gun_.set_position(x0 + CELL_SIZE / 2, y0 + CELL_SIZE / 2);

    int bullet_count = this->attack_range_ / BULLET_SPEED / this->shoot_period_ + 3;

    for (int i = 0; i < bullet_count; i++)
    {
        
        Bullet *bullet = new Bullet(window, this->get_center_x(), this->get_center_y(),
            bullet_sprite, bullet_frame_width, bullet_frame_height);
        this->free_bullets_.push(bullet);
    }
    

}

Tower::Tower():
CommonElement(),
gun_(),
rank_(),
free_bullets_(std::queue<Bullet*> ()),
active_bullets_(std::set<Bullet*> ()),
rank_num_(0),
shoot_period_(0),
shoot_ago_(0),
attack_range_(0),
target_(nullptr),
power_(0)
{}

Tower::~Tower()
{
    for (auto *bullet : this->active_bullets_)
        delete bullet;
}

void Tower::act(float dt)
{
    this->shoot_ago_ += dt;
    if (this->shoot_ago_ >= this->shoot_period_ && this->target_)
    {
        this->shoot();
        this->shoot_ago_ = 0;
    }

    this->move_bullets(dt);
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
    for (auto *bullet : this->active_bullets_)
        bullet->draw();
    this->gun_.draw();
    // this->rank_.draw();
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
        for (int j = 0; j < (int)cur_pack->units_.size(); j++)
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
    Bullet *bullet = this->free_bullets_.front();
    this->free_bullets_.pop();
    bullet->target_ = this->target_;
    bullet->set_visibility(true);
    this->active_bullets_.insert(bullet);
}

void Tower::move_bullets(float dt)
{
    std::set<Bullet*> deactive;

    for (auto *bullet : this->active_bullets_)
    {
        float x = bullet->get_x();
        float y = bullet->get_y();
        float x1 = bullet->target_->get_center_x();
        float y1 = bullet->target_->get_center_y();

        float r = sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));

        if (r <= bullet->get_center_x() - bullet->get_x())
        {
            bullet->set_position(this->get_center_x(), this->get_center_y());
            bullet->set_visibility(false);
            bullet->target_->hurt(this->power_);
            deactive.insert(bullet);
        }
        else
        {
            bullet->set_position(
                bullet->get_x() + BULLET_SPEED * dt / r * (x1 - x),
                bullet->get_y() + BULLET_SPEED * dt / r * (y1 - y)
            );
        }
    }
    
    for (auto *bullet : deactive)
    {
        this->active_bullets_.erase(bullet);
        this->free_bullets_.push(bullet);
    }
}
