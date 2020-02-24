#include "lib/tower_defence_headers.h"

int main_menu(sf::RenderWindow& window, sf::Event& event)
{
    sf::Font font;
    font.loadFromFile("font.otf");

    sf::Text text("", font, 80);
    // text.setFillColor();

    sf::Texture menu_texture;
    // menu_texture.loadFromFile("textures/menu.png");
    // add level icons textures

    sf::Sprite menu_sprite(menu_texture);
    menu_texture.setSmooth(true);


    sf::Texture level_texture;
    // level_texture.loadFromFile("textures/level.png");
    sf::Sprite level1(level_texture);
    // level1.setTextureRect(IntRect(0,0,0,0)); // sprite of a certain level from level texture
    level1.setPosition(100,100);


    CommonElement menu(&window, 0, 0, menu_sprite, WINDOW_WIDTH, WINDOW_HEIGHT);
    bool is_menu = true;

    while(is_menu)
    {
        level1.setColor(sf::Color::White);
        int level_num = 0;
        window.clear(sf::Color(255,100,100));

        // change position
        // if (IntRect(100,100,100,100).contains(Mouse::getPosition(window))) { level_num = 1}

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            switch(level_num)
            {
                case 1: 
                // init_level(level_num);
                break;

            }

        window.clear();
        menu.draw();
        window.display();
    }
}

int main(int argc, char const *argv[])
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "TOWER DEFENCE");
    sf::Event event;

    main_menu(window, event);

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
