#include "../headers/EntityManager.h"


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
    this->cur_wave_->draw();
    for (auto tower : this->towers_)
        tower->draw();
}

void EntityManager::act(float dt)
{
    this->cur_wave_->act(dt);
    for (auto tower : this->towers_)
        tower->act(dt);
}

void EntityManager::update(float dt)
{
    this->cur_wave_->update(dt);
    for (auto tower : this->towers_)
        tower->update(dt);
}
