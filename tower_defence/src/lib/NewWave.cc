#include "../headers/NewWave.h"

#include <string>
#include <iostream>
#include <sstream>


Wave::Wave(const char *wave_info) :
packs_(std::vector<Unitpack*> ())
{
    std::string input(wave_info);
    std::istringstream stream(input);
    std::string unit_name;
    int unit_count = -1;
    int spawn_dt = -1;
    while (!stream.eof())
    {
        stream >> unit_name >> unit_count >> spawn_dt;
        Unitpack *unit_pack = new Unitpack(unit_name, unit_count, spawn_dt);
        this->packs_.push_back(unit_pack);
    }
}

Wave::~Wave()
{
    for (auto pack : this->packs_)
        delete pack;
}

void Wave::draw() const
{
    for (auto pack : this->packs_)
        pack->draw();
}

void Wave::act(float dt)
{
    for (auto pack : this->packs_)
        pack->act(dt);
}

void Wave::update(float dt)
{
    for (auto pack : this->packs_)
        pack->update(dt);
}

