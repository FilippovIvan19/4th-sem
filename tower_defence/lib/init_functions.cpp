#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "constants.h"


#define TEXTURE_DEFINE(obj) \
textures->obj##_texture = new sf::Texture;                      \
textures->obj##_texture->loadFromFile("textures/" #obj ".png");

void load_textures(all_textures *textures)
{
    #include "textures_list.cpp"
}

#undef TEXTURE_DEFINE


#define TEXTURE_DEFINE(obj) \
sprites->obj##_sprite = new sf::Sprite;                        \
sprites->obj##_sprite->setTexture(* textures->obj##_texture);

#define SET_SCALE(obj, x, y) \
sprites->obj##_sprite->setScale(x, y);

void load_sprites(all_sprites *sprites, all_textures *textures)
{
    #include "textures_list.cpp"

    SET_SCALE(pill_tower_base,   (float)CELL_SIZE / PILL_TOWER_BASE_PIC_SIZE,
                                 (float)CELL_SIZE / PILL_TOWER_BASE_PIC_SIZE)

    SET_SCALE(pill_tower_gun,    (float)CELL_SIZE / PILL_TOWER_GUN_PIC_SIZE,
                                 (float)CELL_SIZE / PILL_TOWER_GUN_PIC_SIZE)

    SET_SCALE(pill_tower_bullet, (float)PILL_TOWER_BULLET_SIZE / PILL_TOWER_BULLET_PIC_SIZE,
                                 (float)PILL_TOWER_BULLET_SIZE / PILL_TOWER_BULLET_PIC_SIZE)

    SET_SCALE(bacteria, (float)CELL_SIZE / BACTERIA_UNIT_PIC_SIZE,
                        (float)CELL_SIZE / BACTERIA_UNIT_PIC_SIZE)

    SET_SCALE(rank, (float)RANK_SIZE / RANK_PIC_SIZE,
                               (float)RANK_SIZE / RANK_PIC_SIZE)

}

#undef TEXTURE_DEFINE
#undef SET_SCALE
