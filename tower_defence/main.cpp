#include "tower_defence_lib.cpp"

int main(int argc, char const *argv[])
{
    /* code */

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "TOWER DEFENCE");
    sf::Event event;
    GameManager manager;
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

        manager.update(dt);
        manager.act(dt);

        window.clear();
            // map.draw();
            manager.draw();
        window.display();

        dt = main_clock.getElapsedTime().asMicroseconds();
        main_clock.restart();
    }


    return 0;
}
