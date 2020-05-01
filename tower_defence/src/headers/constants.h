#pragma once

#include <SFML/Graphics.hpp>

// #define DEBUG

#ifndef DEBUG
    #define RELEASE
#endif

#ifdef RELEASE
    #define printf(...) ;
#endif

#include "structs.h"

extern float GLOBAL_SCALE_COEF;

const int READY_LEVEL_COUNT = 2;

#define RANK_SPRITE_OFFSET_X (int)(GLOBAL_SCALE_COEF * 0)
#define RANK_SPRITE_OFFSET_Y (int)(GLOBAL_SCALE_COEF * 0)
#define CELL_SIZE (int)(GLOBAL_SCALE_COEF * 50)
const int CELL_PIC_SIZE = 100;
const int HEART_PIC_SIZE = 400;
#define HEART_SIZE (int)(CELL_SIZE * 5)

const int RANK_PIC_SIZE = 100;
#define RANK_SIZE (int)(GLOBAL_SCALE_COEF * 30)
#define BULLET_SPEED (CELL_SIZE * 15)

// PillTower constants
const int PILL_TOWER_COST = 20;
const float PILL_TOWER_SHOOT_PERIOD  = 0.5;
const int PILL_TOWER_POWER           = 10;
const int PILL_TOWER_BASE_PIC_SIZE   = 100;
const int PILL_TOWER_GUN_PIC_SIZE    = 120;
const int PILL_TOWER_BULLET_PIC_SIZE = 55;
#define PILL_TOWER_BULLET_SIZE (int)(GLOBAL_SCALE_COEF * 10)
#define PILL_TOWER_GUN_SIZE (int)(CELL_SIZE * 1.7)
#define PILL_TOWER_RANGE (int)(CELL_SIZE * 5)
#define PILL_TOWER_BASE_SIZE (int)(CELL_SIZE)

// CapsuleTower constants
const int CAPSULE_TOWER_COST            = 80;
const float CAPSULE_TOWER_SHOOT_PERIOD  = 1;
const int CAPSULE_TOWER_POWER           = 40;
const int CAPSULE_TOWER_BASE_PIC_SIZE   = 100;
const int CAPSULE_TOWER_GUN_PIC_SIZE    = 120;
const int CAPSULE_TOWER_BULLET_PIC_SIZE = 60;
#define CAPSULE_TOWER_BULLET_SIZE (int)(GLOBAL_SCALE_COEF * 20)
#define CAPSULE_TOWER_GUN_SIZE (int)(CELL_SIZE * 1.5)
#define CAPSULE_TOWER_RANGE (int)(CELL_SIZE * 7)
#define CAPSULE_TOWER_BASE_SIZE (int)(CELL_SIZE)

// Window constants
const int MAP_HEIGHT = 18;
const int MAP_WIDTH = 31;
#define WINDOW_WIDTH  (CELL_SIZE * (MAP_WIDTH + 1))
#define WINDOW_HEIGHT (CELL_SIZE * MAP_HEIGHT)

// Unit constants
const int BACTERIA_UNIT_PIC_SIZE = 100;
const int BACTERIA_UNIT_POWER = 1;

const int VIRUS_UNIT_PIC_SIZE = 100;
const int VIRUS_UNIT_POWER = 5;

const int HEALTH_BAR_PIC_WIDTH  = 100;
const int HEALTH_BAR_PIC_HEIGHT = 10;
#define HEALTH_BAR_WIDTH  (int)(CELL_SIZE * 0.9)
#define HEALTH_BAR_HEIGHT (int)(CELL_SIZE * 0.1)

// LevelIcon constants
const int LEVEL_ICON_PIC_SIZE = 300;
#define LEVEL_ICON_SIZE (int)(GLOBAL_SCALE_COEF * 100)
const int LEVEL_LOCK_PIC_SIZE = 500;
#define LEVEL_LOCK_SIZE (int)(GLOBAL_SCALE_COEF * 60)

// Menu constants
const int MENU_PIC_WIDTH = 1920;
const int MENU_PIC_HEIGHT = 1080;
const int LEVEL_COMPLETED_PIC_WIDTH = 1920;
const int LEVEL_COMPLETED_PIC_HEIGHT = 1080;

const int PAGE_LEVEL_COUNT_X = 4;
const int PAGE_LEVEL_COUNT_Y = 3;
const int PAGE_LEVEL_COUNT = PAGE_LEVEL_COUNT_X * PAGE_LEVEL_COUNT_Y;
#define LEVEL_OFFSET_X (int)((WINDOW_WIDTH  + LEVEL_ICON_SIZE) / (PAGE_LEVEL_COUNT_X + 1))
#define LEVEL_OFFSET_Y (int)((WINDOW_HEIGHT + LEVEL_ICON_SIZE) / (PAGE_LEVEL_COUNT_Y + 1))
#define LEVEL_GRID_X0 (LEVEL_OFFSET_X - LEVEL_ICON_SIZE)
#define LEVEL_GRID_Y0 (LEVEL_OFFSET_Y - LEVEL_ICON_SIZE)

const int MAX_STR_SIZE = 1024;

// end level menu
const int LEVEL_END_BUTTONS_SCALE_COEF = 5;
const int LEVEL_END_BUTTONS_COUNT = 3;
#define LEVEL_END_BUTTONS_SIZE (CELL_SIZE * LEVEL_END_BUTTONS_SCALE_COEF)
#define LEVEL_END_BUTTONS_OFFSET_X (int)(GLOBAL_SCALE_COEF * 50)
#define LEVEL_END_BUTTONS_X0 (int)((WINDOW_WIDTH - LEVEL_END_BUTTONS_OFFSET_X * (LEVEL_END_BUTTONS_COUNT - 1)\
    - LEVEL_END_BUTTONS_SIZE * LEVEL_END_BUTTONS_COUNT) / 2)
#define LEVEL_END_BUTTONS_Y0 (int)(GLOBAL_SCALE_COEF * 500)

const point END_POINT{ -1, -1 }; // POISON for units

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
    LU_INT_ROADSIDE = 'b',
};

enum class GameCodes
{
    WAVE_ENDED,
    LEVEL_COMPLETED,
    LAST_LEVEL_COMPLETED,
    LEVEL_FAILED,
    EXIT_LEVEL,
    EXIT_APP,
    NOTHING,
};
