#include "GameManager.h"


GameManager::GameManager():
game_objects_(std::set<CommonElement*> ())
{}

void GameManager::add_obj(CommonElement *obj_ptr)
{
    this->game_objects_.insert(obj_ptr);
}

void GameManager::draw()
{
    for (CommonElement *obj: this->game_objects_)
        obj->draw();
}

void GameManager::act(float dt)
{
    for (CommonElement *obj: this->game_objects_)
        obj->act(dt);
}

void GameManager::update(float dt)
{
    for (CommonElement *obj: this->game_objects_)
        obj->update(dt);
}

GameManager::~GameManager()
{
    // for (CommonElement *obj: this->game_objects_)
    //     delete(obj);
}
