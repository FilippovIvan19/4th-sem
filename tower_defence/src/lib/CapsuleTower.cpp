#include "../headers/CapsuleTower.h"


CapsuleTower::CapsuleTower(sf::RenderWindow *window, float x0, float y0, all_sprites *sprites):
Tower(window, Tower_kind::Capsule, CAPSULE_TOWER_RANGE, CAPSULE_TOWER_SHOOT_PERIOD, CAPSULE_TOWER_POWER, x0, y0,
    *sprites->capsule_tower_base_sprite, CAPSULE_TOWER_BASE_PIC_SIZE, CAPSULE_TOWER_BASE_PIC_SIZE,
    *sprites->capsule_tower_gun_sprite, CAPSULE_TOWER_GUN_PIC_SIZE, CAPSULE_TOWER_BASE_PIC_SIZE,
    *sprites->capsule_tower_bullet_sprite, CAPSULE_TOWER_BULLET_PIC_SIZE, CAPSULE_TOWER_BULLET_PIC_SIZE,
    *sprites->rank_sprite, RANK_PIC_SIZE, RANK_PIC_SIZE)
{
    this->gun_.set_position(x0 + 0.5 * CELL_SIZE, y0 + 0.5 * CELL_SIZE);
    this->gun_.set_origin_zero(0.5 * CAPSULE_TOWER_GUN_PIC_SIZE, 0.59 * CAPSULE_TOWER_GUN_PIC_SIZE);
}

CapsuleTower::CapsuleTower():
Tower()
{}

CapsuleTower::~CapsuleTower()
{}

// void CapsuleTower::shoot(Unit *target)
// {}
