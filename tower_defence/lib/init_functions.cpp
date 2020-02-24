#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "constants.h"


#define LOAD_TEXTURE(obj) \
textures->obj##_texture = new sf::Texture;                      \
textures->obj##_texture->loadFromFile("textures/" #obj ".png");

void load_textures(all_textures *textures)
{
    LOAD_TEXTURE(pill_tower_base);
    LOAD_TEXTURE(pill_tower_gun);
    LOAD_TEXTURE(pill_tower_bullet);
    LOAD_TEXTURE(rank);
}

#undef LOAD_TEXTURE


#define LOAD_SPRITE(obj) \
sprites->obj##_sprite = new sf::Sprite;                        \
sprites->obj##_sprite->setTexture(* textures->obj##_texture);

void load_sprites(all_sprites *sprites, all_textures *textures)
{
    LOAD_SPRITE(pill_tower_base);
    LOAD_SPRITE(pill_tower_gun);
    LOAD_SPRITE(pill_tower_bullet);
    LOAD_SPRITE(rank);
}

#undef LOAD_SPRITE
