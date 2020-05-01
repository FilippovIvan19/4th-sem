#include "../headers/PillTower.h"


PillTower::PillTower(sf::RenderWindow *window, float x0, float y0, all_sprites *sprites):
Tower(window, PILL_TOWER_RANGE, PILL_TOWER_SHOOT_PERIOD, PILL_TOWER_POWER, x0, y0,
    *sprites->pill_tower_base_sprite, PILL_TOWER_BASE_PIC_SIZE, PILL_TOWER_BASE_PIC_SIZE,
    *sprites->pill_tower_gun_sprite, PILL_TOWER_GUN_PIC_SIZE, PILL_TOWER_BASE_PIC_SIZE,
    *sprites->pill_tower_bullet_sprite, PILL_TOWER_BULLET_PIC_SIZE, PILL_TOWER_BULLET_PIC_SIZE,
    *sprites->rank_sprite, RANK_PIC_SIZE, RANK_PIC_SIZE)
{
    this->gun_.set_position(x0 + 0.5 * CELL_SIZE, y0 + 0.5 * CELL_SIZE);
    this->gun_.set_origin_zero(0.5 * PILL_TOWER_GUN_PIC_SIZE, 0.59 * PILL_TOWER_GUN_PIC_SIZE);
}

PillTower::PillTower():
Tower()
{}

PillTower::~PillTower()
{}
