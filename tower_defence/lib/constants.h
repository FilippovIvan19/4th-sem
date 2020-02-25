#pragma once

#include <SFML/Graphics.hpp>

const float RANK_SPRITE_OFFSET_X = 10;
const float RANK_SPRITE_OFFSET_Y = 10;
const int CELL_SIZE = 50;
const int CELL_PIC_SIZE = 100;
const int PILL_TOWER_BASE_PIC_SIZE   = 100;
const int PILL_TOWER_GUN_PIC_SIZE    = 120;
const int PILL_TOWER_BULLET_PIC_SIZE = 100;
const int PILL_TOWER_RANGE = 150;
const int RANK_PIC_SIZE = 100;
const int RANK_SIZE = 10;
const int MAP_HEIGHT = 15;
const int MAP_WIDTH = 37;
const int WINDOW_WIDTH  = CELL_SIZE * MAP_WIDTH;
const int WINDOW_HEIGHT = CELL_SIZE * MAP_HEIGHT;


struct point {
  int x;
  int y;
};

struct cmp_points
{
    bool operator()(const point& left, const point& right)
    {
        if (left.x != right.x)
            return left.x < right.x;
        else
            return left.y < right.y;
    }
};


enum class Tower_kind
{
    Pill,
    Capsule,
    Mixture,
};


enum Unit_kind
{
    simple_virus,
};


#define ADD_TEXTURE(obj) sf::Texture *obj##_texture;

struct all_textures
{
    ADD_TEXTURE(pill_tower_base);
    ADD_TEXTURE(pill_tower_gun);
    ADD_TEXTURE(pill_tower_bullet);
    ADD_TEXTURE(rank);
};

#undef ADD_TEXTURE


#define ADD_SPRITE(obj) sf::Sprite *obj##_sprite;

struct all_sprites
{
    ADD_SPRITE(pill_tower_base);
    ADD_SPRITE(pill_tower_gun);
    ADD_SPRITE(pill_tower_bullet);
    ADD_SPRITE(rank);
};

#undef ADD_SPRITE
