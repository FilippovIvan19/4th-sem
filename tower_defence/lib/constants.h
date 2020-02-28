#pragma once

#include <SFML/Graphics.hpp>

const float RANK_SPRITE_OFFSET_X = 0;
const float RANK_SPRITE_OFFSET_Y = 0;
const int CELL_SIZE = 50;
const int CELL_PIC_SIZE = 100;
// standart PillTower constants
const int PILL_TOWER_BASE_PIC_SIZE   = 100;
const int PILL_TOWER_GUN_PIC_SIZE    = 120;
const int PILL_TOWER_BULLET_PIC_SIZE = 55;
const int PILL_TOWER_BULLET_SIZE = 20;
const int PILL_TOWER_RANGE = 150;
const int RANK_PIC_SIZE = 100;
const int RANK_SIZE = 30;
const int MAP_HEIGHT = 18;
const int MAP_WIDTH = 32;
const int WINDOW_WIDTH  = CELL_SIZE * MAP_WIDTH;
const int WINDOW_HEIGHT = CELL_SIZE * MAP_HEIGHT;

// standart BacteriaUnit constants
const int BACTERIA_UNIT_PIC_SIZE = 100;
const int BACTERIA_UNIT_HEALTH = 100;
const int BACTERIA_UNIT_VELOCITY = 10;

// LevelIcon constants
const int LEVEL_ICON_SIZE = 100;
const int LEVEL_ICON_PIC_SIZE = 100;
const int LEVEL_COUNT_X = 4;
const int LEVEL_COUNT_Y = 3;
const int LEVEL_COUNT = LEVEL_COUNT_X * LEVEL_COUNT_Y;

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
    Bacteria,
    Simple_virus,
};


#define TEXTURE_DEFINE(obj) sf::Texture *obj##_texture;

struct all_textures
{
    #include "textures_list.h"
};

#undef TEXTURE_DEFINE


#define TEXTURE_DEFINE(obj) sf::Sprite *obj##_sprite;

struct all_sprites
{
    #include "textures_list.h"
};

#undef TEXTURE_DEFINE
