#include "../headers/Wave.h"
#include "../headers/Unitpack.h"
// #include "../headers/Wave.h"

#include <string>
#include <sstream>
#include <iostream>


Wave::Wave(sf::RenderWindow *window, all_sprites *sprites, Level *level, std::string &wave_info) :
packs_(std::vector<Unitpack*> ())
{
    // printf("wave info: %s\n\n", wave_info.c_str());
    std::istringstream stream(wave_info);
    std::string unit_name;
    int unit_count = 0;
    float spawn_delta = 0;
    float spawn_delay = 0;
    float speed = 0;
    int unit_cost = 0;
    float health = 0;
    while (!stream.eof())
    {
        stream >> unit_name >> unit_count >> spawn_delta >> spawn_delay >> speed >> unit_cost >> health;
        // std::cout << unit_name << unit_count << spawn_delta << spawn_delay << speed << unit_cost << health << std::endl; 
        Unitpack *unit_pack = new Unitpack(window, sprites, level,
            unit_name, unit_count, spawn_delta, spawn_delay, speed, unit_cost, health);
        this->packs_.push_back(unit_pack);
    }
    // printf("packs count %d\n", this->packs_.size());
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

bool Wave::is_alive() const
{
    // printf("1\n");
    for (auto pack : this->packs_)
    {
        // printf("pack->is_alive() %d\n", pack->is_alive());
        if (pack->is_alive())
            return true;
    }
    // printf("2\n");

    return false;
}
