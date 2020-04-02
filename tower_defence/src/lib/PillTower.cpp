#include "PillTower.h"


PillTower::PillTower(sf::RenderWindow *window, float x0, float y0, all_sprites *sprites):
Tower(window, Tower_kind::Pill, PILL_TOWER_RANGE, x0, y0,
    *sprites->pill_tower_base_sprite, PILL_TOWER_BASE_PIC_SIZE, PILL_TOWER_BASE_PIC_SIZE,
    *sprites->pill_tower_gun_sprite, PILL_TOWER_GUN_PIC_SIZE, PILL_TOWER_BASE_PIC_SIZE,
    *sprites->pill_tower_bullet_sprite, PILL_TOWER_BULLET_PIC_SIZE, PILL_TOWER_BULLET_PIC_SIZE,
    *sprites->rank_sprite, RANK_PIC_SIZE, RANK_PIC_SIZE)
{}

PillTower::PillTower():
Tower()
{}

PillTower::~PillTower()
{}

void PillTower::shoot(CommonElement *target)
{}
