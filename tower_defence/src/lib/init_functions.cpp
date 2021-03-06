#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../headers/constants.h"


#define TEXTURE_DEFINE(obj) \
textures->obj##_texture = new sf::Texture;                      \
textures->obj##_texture->loadFromFile("textures/" #obj ".png"); \
textures->obj##_texture->setSmooth(true);

void load_textures(all_textures *textures)
{
    #include "../headers/textures_list.h"
}

#undef TEXTURE_DEFINE


#define TEXTURE_DEFINE(obj) \
sprites->obj##_sprite = new sf::Sprite;                        \
sprites->obj##_sprite->setTexture(* textures->obj##_texture);

#define SET_SCALE(obj, x, y) \
sprites->obj##_sprite->setScale(x, y);

void load_sprites(all_sprites *sprites, all_textures *textures)
{
    #include "../headers/textures_list.h"

    SET_SCALE(pill_tower_base,   (float)PILL_TOWER_BASE_SIZE / PILL_TOWER_BASE_PIC_SIZE,
                                 (float)PILL_TOWER_BASE_SIZE / PILL_TOWER_BASE_PIC_SIZE)

    SET_SCALE(pill_tower_gun,    (float)PILL_TOWER_GUN_SIZE / PILL_TOWER_GUN_PIC_SIZE,
                                 (float)PILL_TOWER_GUN_SIZE / PILL_TOWER_GUN_PIC_SIZE)

    SET_SCALE(pill_tower_bullet, (float)PILL_TOWER_BULLET_SIZE / PILL_TOWER_BULLET_PIC_SIZE,
                                 (float)PILL_TOWER_BULLET_SIZE / PILL_TOWER_BULLET_PIC_SIZE)

    SET_SCALE(capsule_tower_base,   (float)CAPSULE_TOWER_BASE_SIZE / CAPSULE_TOWER_BASE_PIC_SIZE,
                                    (float)CAPSULE_TOWER_BASE_SIZE / CAPSULE_TOWER_BASE_PIC_SIZE)

    SET_SCALE(capsule_tower_gun,    (float)CAPSULE_TOWER_GUN_SIZE / CAPSULE_TOWER_GUN_PIC_SIZE,
                                    (float)CAPSULE_TOWER_GUN_SIZE / CAPSULE_TOWER_GUN_PIC_SIZE)

    SET_SCALE(capsule_tower_bullet, (float)CAPSULE_TOWER_BULLET_SIZE / CAPSULE_TOWER_BULLET_PIC_SIZE,
                                    (float)CAPSULE_TOWER_BULLET_SIZE / CAPSULE_TOWER_BULLET_PIC_SIZE)

    SET_SCALE(map, (float)CELL_SIZE / CELL_PIC_SIZE,
                   (float)CELL_SIZE / CELL_PIC_SIZE)

    SET_SCALE(bacteria, (float)CELL_SIZE / BACTERIA_UNIT_PIC_SIZE,
                        (float)CELL_SIZE / BACTERIA_UNIT_PIC_SIZE)

    SET_SCALE(virus, (float)CELL_SIZE / VIRUS_UNIT_PIC_SIZE,
                     (float)CELL_SIZE / VIRUS_UNIT_PIC_SIZE)

    SET_SCALE(rank, (float)RANK_SIZE / RANK_PIC_SIZE,
                    (float)RANK_SIZE / RANK_PIC_SIZE)

    SET_SCALE(level_icon, (float)LEVEL_ICON_SIZE / LEVEL_ICON_PIC_SIZE,
                          (float)LEVEL_ICON_SIZE / LEVEL_ICON_PIC_SIZE)

    SET_SCALE(menu_background, (float)WINDOW_WIDTH  / MENU_PIC_WIDTH,
                               (float)WINDOW_HEIGHT / MENU_PIC_HEIGHT)

    SET_SCALE(level_completed, (float)WINDOW_WIDTH  / LEVEL_COMPLETED_PIC_WIDTH,
                               (float)WINDOW_HEIGHT / LEVEL_COMPLETED_PIC_HEIGHT)

    SET_SCALE(buttons, (float)CELL_SIZE / CELL_PIC_SIZE,
                       (float)CELL_SIZE / CELL_PIC_SIZE)

    SET_SCALE(heart, (float)HEART_SIZE / HEART_PIC_SIZE,
                     (float)HEART_SIZE / HEART_PIC_SIZE)

    SET_SCALE(lock,  (float)LEVEL_LOCK_SIZE / LEVEL_LOCK_PIC_SIZE,
                     (float)LEVEL_LOCK_SIZE / LEVEL_LOCK_PIC_SIZE)

    SET_SCALE(health_bar, (float)HEALTH_BAR_WIDTH  / HEALTH_BAR_PIC_WIDTH,
                          (float)HEALTH_BAR_HEIGHT / HEALTH_BAR_PIC_HEIGHT)

}

#undef TEXTURE_DEFINE
#undef SET_SCALE


#define FONT_DEFINE(obj) \
fonts->obj##_font = new sf::Font;                        \
fonts->obj##_font->loadFromFile("fonts/" #obj ".ttf");

void load_fonts(all_fonts *fonts)
{
    #include "../headers/fonts_list.h"
}

#undef FONT_DEFINE