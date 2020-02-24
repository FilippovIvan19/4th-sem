#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "constants.h"


#define LOAD_TEXTURE(obj) \
textures->obj##_texture = new sf::Texture;                      \
textures->obj##_texture->loadFromFile("textures/" #obj ".png");

void load_textures(all_textures *textures)
{
    LOAD_TEXTURE(pill_tower_base)
    LOAD_TEXTURE(pill_tower_gun)
    LOAD_TEXTURE(pill_tower_bullet)
    LOAD_TEXTURE(rank)
}

#undef LOAD_TEXTURE


#define LOAD_SPRITE(obj) \
sprites->obj##_sprite = new sf::Sprite;                        \
sprites->obj##_sprite->setTexture(* textures->obj##_texture);

#define SET_SCALE(obj, x, y) \
sprites->obj##_sprite->setScale(x, y);

void load_sprites(all_sprites *sprites, all_textures *textures)
{
    LOAD_SPRITE(pill_tower_base)
    SET_SCALE(pill_tower_base, (float)CELL_SIZE / PILL_TOWER_BASE_PIC_SIZE,
                               (float)CELL_SIZE / PILL_TOWER_BASE_PIC_SIZE)

    LOAD_SPRITE(pill_tower_gun)
    SET_SCALE(pill_tower_base, (float)CELL_SIZE / PILL_TOWER_GUN_PIC_SIZE,
                               (float)CELL_SIZE / PILL_TOWER_GUN_PIC_SIZE)

    LOAD_SPRITE(pill_tower_bullet)
    SET_SCALE(pill_tower_base, (float)CELL_SIZE / PILL_TOWER_BULLET_PIC_SIZE,
                               (float)CELL_SIZE / PILL_TOWER_BULLET_PIC_SIZE)

    LOAD_SPRITE(rank)
    SET_SCALE(pill_tower_base, (float)RANK_SIZE / RANK_PIC_SIZE,
                               (float)RANK_SIZE / RANK_PIC_SIZE)

}

#undef LOAD_SPRITE
#undef SET_SCALE
