#include "lib/tower_defence_headers.h"

int main_menu(sf::RenderWindow& window, sf::Event& event)
{
    sf::Font font;
    font.loadFromFile("font.otf");

    sf::Text text("", font, 80);
    // text.setFillColor();

    sf::Texture menu_texture;
    // menu_texture.loadFromFile("textures/menu.png");

    sf::Sprite menu_sprite(menu_texture);
    menu_texture.setSmooth(true);

    CommonElement menu(&window, 0, 0, menu_sprite, WINDOW_WIDTH, WINDOW_HEIGHT);
    
    window.clear();
    menu.draw();
    window.display();
}

int main(int argc, char const *argv[])
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "TOWER DEFENCE");
    sf::Event event;
    // GameManager manager;
    // Map map;


    sf::Clock main_clock;
    float dt = 0;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
                return 0;
            }

        // process_input(event);

        // manager.update(dt);
        // manager.act(dt);

        window.clear();
            // map.draw();
            // manager.draw();
        window.display();

        dt = main_clock.getElapsedTime().asMicroseconds();
        main_clock.restart();
    }

    return 0;
}
