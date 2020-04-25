#include "headers/tower_defence_headers.h"

float get_screen_scale(float scale = 0)
{
    sf::VideoMode fullscreen = sf::VideoMode::getDesktopMode();
    float scale_x = fullscreen.width  / 1920.0;
    float scale_y = fullscreen.height / 1080.0;
    return scale ? scale : std::min(scale_x, scale_y);
}

float GLOBAL_SCALE_COEF;


int main(int argc, char const *argv[])
{
    GLOBAL_SCALE_COEF = get_screen_scale();
    // std::cout << GLOBAL_SCALE_COEF << std::endl;
    all_textures textures;
    all_sprites  sprites;
    all_fonts fonts;

    load_fonts(&fonts);
    load_textures(&textures);
    load_sprites(&sprites, &textures);
    
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "TOWER DEFENCE");
    sf::Event event;
    sf::Clock main_clock;

    GameManager manager(&window, &event, &main_clock, &sprites, &fonts);

    manager.main_cycle();

    return 0;
}
