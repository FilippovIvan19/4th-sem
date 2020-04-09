#pragma once

#include <SFML/Graphics.hpp>

#define DEBUG

#ifndef DEBUG
    #define RELEASE
#endif

#ifdef RELEASE
    #define printf(...) ;
#endif

extern float GLOBAL_SCALE_COEF;

#define RANK_SPRITE_OFFSET_X (int)(GLOBAL_SCALE_COEF * 0)
#define RANK_SPRITE_OFFSET_Y (int)(GLOBAL_SCALE_COEF * 0)
#define CELL_SIZE (int)(GLOBAL_SCALE_COEF * 50)
const int CELL_PIC_SIZE = 100;

// PillTower constants
const int PILL_TOWER_BASE_PIC_SIZE   = 100;
const int PILL_TOWER_GUN_PIC_SIZE    = 120;
const int PILL_TOWER_BULLET_PIC_SIZE = 55;
#define PILL_TOWER_BULLET_SIZE (int)(GLOBAL_SCALE_COEF * 20)
#define PILL_TOWER_RANGE (int)(GLOBAL_SCALE_COEF * 150)
const int RANK_PIC_SIZE = 100;
#define RANK_SIZE (int)(GLOBAL_SCALE_COEF * 30)

// Window constants
const int MAP_HEIGHT = 18;
const int MAP_WIDTH = 31;
#define WINDOW_WIDTH  (CELL_SIZE * (MAP_WIDTH + 1))
#define WINDOW_HEIGHT (CELL_SIZE * MAP_HEIGHT)

// BacteriaUnit constants
const int BACTERIA_UNIT_PIC_SIZE = 100;
const int BACTERIA_UNIT_HEALTH = 100;
#define BACTERIA_UNIT_VELOCITY (int)(GLOBAL_SCALE_COEF * 200)

// LevelIcon constants
const int LEVEL_ICON_PIC_SIZE = 300;
#define LEVEL_ICON_SIZE (int)(GLOBAL_SCALE_COEF * 100)

// Menu constants

const int MENU_PIC_WIDTH = 1920;
const int MENU_PIC_HEIGHT = 1080;
// #define MENU_WIDTH  WINDOW_WIDTH
// #define MENU_HEIGHT WINDOW_HEIGHT

const int LEVEL_COUNT_X = 4;
const int LEVEL_COUNT_Y = 3;
const int LEVEL_COUNT = LEVEL_COUNT_X * LEVEL_COUNT_Y;
#define LEVEL_OFFSET_X (int)((WINDOW_WIDTH  + LEVEL_ICON_SIZE) / (LEVEL_COUNT_X + 1))
#define LEVEL_OFFSET_Y (int)((WINDOW_HEIGHT + LEVEL_ICON_SIZE) / (LEVEL_COUNT_Y + 1))
#define LEVEL_GRID_X0 (LEVEL_OFFSET_X - LEVEL_ICON_SIZE)
#define LEVEL_GRID_Y0 (LEVEL_OFFSET_Y - LEVEL_ICON_SIZE)

struct point {
    int x;
    int y;

    bool operator<(const point& other) const
    {
        if (this->x != other.x)
            return this->x < other.x;
        else
            return this->y < other.y;
    }

    bool operator==(const point& other) const
    {
        return (this->x == other.x) && (this->y == other.y);
    }
};


const point END_POINT{ -666, -666 }; // POISON for units



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

enum class Direction {
    U,
    D,
    L,
    R,
    UL,
    UR,
    DL,
    DR,
    LU,
    LD,
    RU,
    RD,
    ERR,

    SPAWN_POINT = 'S',
    END_POINT = 'E',
    TURN_POINT = 'T',
    ROAD_POINT = 'O',
    FREE_PLACE = 'P',
    COMMON_POINT = '.',

    D_ROADSIDE = 4,
    U_ROADSIDE = 0,
    R_ROADSIDE = 2,
    L_ROADSIDE = 6,
    RU_EXT_ROADSIDE = 1,
    RD_EXT_ROADSIDE = 3,
    LD_EXT_ROADSIDE = 5,
    LU_EXT_ROADSIDE = 7,

    RD_INT_ROADSIDE = 'd',
    RU_INT_ROADSIDE = 'c',
    LD_INT_ROADSIDE = 'a',
    LU_INT_ROADSIDE = 'b'

};
