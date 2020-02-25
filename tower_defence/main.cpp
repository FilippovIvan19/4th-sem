#include "lib/tower_defence_headers.h"


int main(int argc, char const *argv[])
{
    /*
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
    */


    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "TOWER DEFENCE");
    sf::Event event;
    
    /*
    printf("before map\n");

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

    }
    */
    


    // printf("before loading\n");

    sf::Image map_image;
  	map_image.loadFromFile("lib/map.png");
  	sf::Texture map_texture;
  	map_texture.loadFromImage(map_image);
  	sf::Sprite map_sprite;
  	map_sprite.setTexture(map_texture);
  	map_sprite.setScale((float)CELL_SIZE / CELL_PIC_SIZE, (float)CELL_SIZE / CELL_PIC_SIZE);

    // printf("before map\n");

    Map map(&window, map_sprite, "lib/map_scheme.txt");


    // printf("after map\n");
    //map_sprite.setTextureRect(sf::IntRect(10, 10, CELL_WIDTH, CELL_HEIGHT));
    //Cell cell(&window, map_sprite, 2,2, 'O');
    bool first = true;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
                return 0;
            }
        if (first) {
          window.clear();
          //cell.draw();
          map.draw();
          window.display();
          first = false;
        //   printf("drawed\n");
        }

    }

    return 0;
}
