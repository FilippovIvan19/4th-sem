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

    load_textures(&textures);
    load_sprites(&sprites, &textures);
    
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "TOWER DEFENCE");
    sf::Event event;

    GameManager manager(&window, &event, &sprites);

    manager.level_menu();
    manager.load_level();


    sf::Clock main_clock;
    main_clock.restart();
    float dt = 0;
    float delta = 0;

    while (window.isOpen())
    {
        dt = main_clock.getElapsedTime().asMicroseconds();
        main_clock.restart();
        delta += dt;

        manager.draw();
        
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
                return 0;
            }

    }

    return 0;
}

