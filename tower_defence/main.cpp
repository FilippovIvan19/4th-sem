#include "lib/tower_defence_headers.h"



int main(int argc, char const *argv[])
{
  sf::String text_scheme_1[MAP_HEIGHT] = {
    ".....................................",
    "SOOOOOOOT............................",
    "........O............................",
    "........O............................",
    "........O.........TOOOOOOOOOT........",
    "........O.........O.........O........",
    "........O.........O.........O........",
    "........TOOOOOOOOOT.........O........",
    "............................O........",
    "............................O........",
    "............................O........",
    "............................O........",
    "............................O........",
    "............................TOOOOOOOE",
    "....................................."
  };

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "TOWER DEFENCE");
    sf::Event event;

    sf::Image map_image;
  	map_image.loadFromFile("lib/map.png");
  	sf::Texture map_texture;
  	map_texture.loadFromImage(map_image);
  	sf::Sprite map_sprite;
  	map_sprite.setTexture(map_texture);

    Map map(&window, map_sprite, "lib/map_scheme.txt", 1);
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
          map.map_draw();
          window.display();
          first = false;
        }

    }

    return 0;
}
