#include "../headers/Wave.h"

#include <string>
#include <iostream>
#include <sstream>


Wave::Wave(std::string &wave_info) :
packs_(std::vector<Unitpack*> ())
{
    printf("wave info: %s", wave_info.c_str());
    std::istringstream stream(wave_info);
    std::string unit_name;
    int unit_count = -1;
    float spawn_delta = -1;
    float spawn_delay = -1;
    while (!stream.eof())
    {
        stream >> unit_name >> unit_count >> spawn_delta >> spawn_delay;
        Unitpack *unit_pack = new Unitpack(unit_name, unit_count, spawn_delta, spawn_delay);
        this->packs_.push_back(unit_pack);
    }
}

Wave::Wave() :
packs_(std::vector<Unitpack*> ())
{}

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

