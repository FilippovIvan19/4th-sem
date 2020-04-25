#include "../headers/Unitpack.h"
#include "../headers/Unit.h"
#include "../headers/BacteriaUnit.h"
#include "../headers/VirusUnit.h"
#include <math.h>


Unitpack::Unitpack(sf::RenderWindow *window, all_sprites *sprites, Level *level,
    std::string &unit_name, int unit_count, float spawn_delta,
    float spawn_delay, float speed, int unit_cost, float health) :
spawn_delta_(spawn_delta),
spawn_delay_(spawn_delay),
units_(std::vector<Unit*> ()),
spawned_count_(0),
delayed_(0)
{

    if (unit_name == "Bacteria")
        for (int i = 0; i < unit_count; i++)
        {
            Unit *unit = new BacteriaUnit(window, 0, 0, health, speed,
                unit_cost, *sprites->bacteria_sprite, level);
            
            this->units_.push_back(unit);
        }
    else if (unit_name == "Virus")
        for (int i = 0; i < unit_count; i++)
        {
            Unit *unit = new VirusUnit(window, 0, 0, health, speed,
                unit_cost, *sprites->virus_sprite, level);
            
            this->units_.push_back(unit);
        }
    else
        printf("wrong unit name: %s\n", unit_name.c_str());
}

Unitpack::Unitpack() :
spawn_delta_(0),
spawn_delay_(0),
units_(std::vector<Unit*> ()),
spawned_count_(0),
delayed_(0)
{}

Unitpack::~Unitpack()
{
    for (auto unit : this->units_)
        delete unit;
}

void Unitpack::draw() const
{
    for (auto unit : this->units_)
        unit->draw();
}

void Unitpack::act(float dt)
{
    this->delay(dt);
    for (auto unit : this->units_)
        unit->act(dt);
}

void Unitpack::update(float dt)
{
    for (auto unit : this->units_)
        unit->update(dt);
}

void Unitpack::delay(float dt)
{
    if (this->spawned_count_ == this->units_.size())
        return;

    this->delayed_ += dt;
    int new_count = trunc((this->delayed_ - this->spawn_delay_) / this->spawn_delta_ + 1);
    if (new_count < 0)
        new_count = 0;
    if (new_count > this->units_.size())
        new_count = this->units_.size();
    for (int i = this->spawned_count_; i < new_count; i++)
        this->units_[i]->spawn();
    this->spawned_count_ = new_count;
}

bool Unitpack::is_alive() const
{
    if (this->delayed_ <= this->spawn_delay_)
        return true;
    for (auto unit : this->units_)
        if (unit->is_alive())
            return true;
    return false;
}
