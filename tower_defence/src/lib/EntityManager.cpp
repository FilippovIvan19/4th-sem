#include "../headers/EntityManager.h"
#include "../headers/Wave.h"
#include "../headers/Tower.h"


EntityManager::EntityManager() :
towers_(std::set<Tower*> ()),
cur_wave_(nullptr)
{}

EntityManager::~EntityManager()
{
    for (auto tower : this->towers_)
        delete tower;
}

void EntityManager::draw() const
{
    if (this->cur_wave_)
        this->cur_wave_->draw();
    for (auto tower : this->towers_)
        tower->draw();
}

void EntityManager::act(float dt)
{
    if (this->cur_wave_)
        this->cur_wave_->act(dt);
    for (auto tower : this->towers_)
    {
        tower->find_target(this->cur_wave_);
        tower->act(dt);
    }
}

void EntityManager::update(float dt)
{
    if (this->cur_wave_)
        this->cur_wave_->update(dt);
    for (auto tower : this->towers_)
        tower->update(dt);
}

void EntityManager::add(Tower *tower)
{
    this->towers_.insert(tower);
}

void EntityManager::set_wave(Wave *wave)
{
    this->cur_wave_ = wave;
}

bool EntityManager::is_cur_wave_alive()
{
    return this->cur_wave_->is_alive();
}
