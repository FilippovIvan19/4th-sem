#include "../headers/Unitpack.h"
#include "../headers/BacteriaUnit.h"


Unitpack::Unitpack(std::string &unit_name, int unit_count, float spawn_delta, float spawn_delay) :
spawn_delta_(spawn_delta),
spawn_delay_(spawn_delay),
units_(std::vector<Unit*> ())
{
    if (unit_name == "BacteriaUnit")
        for (int i = 0; i < unit_count; i++)
        {
            Unit *unit = new BacteriaUnit(/**/);
            this->units_.push_back(unit);
        }
    else if (unit_name == "VirusUnit")
        for (int i = 0; i < unit_count; i++)
        {
            Unit *unit = new BacteriaUnit(/**/);
            this->units_.push_back(unit);
        }
    else
        printf("wrong unit name: %s\n", unit_name.c_str());
}

Unitpack::Unitpack() :
spawn_delta_(-1),
spawn_delay_(-1),
units_(std::vector<Unit*> ())
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
    for (auto unit : this->units_)
        unit->act(dt);
}

void Unitpack::update(float dt)
{
    for (auto unit : this->units_)
        unit->update(dt);
}
