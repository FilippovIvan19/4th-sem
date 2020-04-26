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


#define FONT_DEFINE(obj) sf::Font *obj##_font;

struct all_fonts
{
    #include "fonts_list.h"
};

#undef FONT_DEFINE
