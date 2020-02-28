#include "lib/tower_defence_headers.h"



void init_level(sf::RenderWindow& window, all_sprites *sprites ,int level)
{
    
}


int current_position(sf::RenderWindow& window, sf::Event& event)
{
    int position = LEVEL_COUNT; // default case value

    for (int i = 0; i < LEVEL_COUNT; ++i)
    {
        if (sf::IntRect(100 + i * 100, 100 + i * 100,
             LEVEL_ICON_PIC_SIZE, LEVEL_ICON_PIC_SIZE).contains(sf::Mouse::getPosition(window)))
        {
            position = i;
            break;
        }
    }
    
    return position;
}

int main_menu(sf::RenderWindow& window, sf::Event& event, all_sprites* sprites)
{
    LevelIcon *level[LEVEL_COUNT + 1];
    for (int i = 0; i < LEVEL_COUNT; ++i)
    {
        level[i] = new LevelIcon(&window, 100 + i * 100, 100 + i * 100,
         *sprites->level_icon_sprite, i, LEVEL_ICON_PIC_SIZE, LEVEL_ICON_PIC_SIZE);
    }
    level[0]->set_lock(false);

    CommonElement menu(&window, 0, 0, *sprites->menu_background_sprite, WINDOW_WIDTH, WINDOW_HEIGHT);
    bool is_menu = true;

    int level_num;

    while(is_menu)
    {
        level_num = current_position(window, event);
        if (level_num != LEVEL_COUNT)
            level[level_num]->set_frame(1, 0); // move sprite rect to right

        window.clear();
        menu.draw();
        for(int i = 0; i < LEVEL_COUNT; ++i)
            level[i]->draw();
        window.display();

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
                return 0;
            }
            else if (event.type == sf::Event::MouseButtonPressed && 
                     sf::Mouse::isButtonPressed(sf::Mouse::Left))
                if(level_num > -1 && level_num < LEVEL_COUNT)
                    is_menu = false;
        }

        if (level_num != LEVEL_COUNT)
            level[level_num]->set_frame(0, 0); // move sprite rect to left
    }
    printf("%d level chosen\n", level_num);
    for (int i = 0; i < LEVEL_COUNT; ++i)
        delete level[i];

    return level_num;
}

#define CONCAT(num) (std::string("levels/maps/") + std::to_string(num) + std::string(".txt")).c_str()

int main(int argc, char const *argv[])
{
    all_textures textures;
    all_sprites  sprites;

    load_textures(&textures);
    load_sprites(&sprites, &textures);
    
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "TOWER DEFENCE");
    sf::Event event;

    int level = main_menu(window, event, &sprites);

    GameManager manager;
    Map map(&window, *sprites.map_sprite, CONCAT(level + 1));
    BacteriaUnit *bact = new BacteriaUnit(&window, 300, 300, 
        *sprites.bacteria_sprite, BACTERIA_UNIT_PIC_SIZE, BACTERIA_UNIT_PIC_SIZE);
    PillTower *pill = new PillTower(&window, 600, 600, &sprites);

    manager.add_obj(bact);
    manager.add_obj(pill);


    bool highlight = false;
    float delta = 0;


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
        map.draw();
        manager.draw();
        window.display();

        dt = main_clock.getElapsedTime().asMicroseconds();
        delta += dt;
        if (delta >= 1e6)
        {
            delta = 0;
            highlight = !highlight;
            if (highlight)
                map.highlight_free();
            else
                map.darken_free();
        }
        // printf("%.2f\n", 1000000.0 / dt);
        main_clock.restart();
    }

    return 0;
}

#undef CONCAT
