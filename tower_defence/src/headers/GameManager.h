#pragma once

#include "Level.h"
#include "Buttons.h"


class GameManager
{
private:
    Level *level_; // should be deleted soc it's a pointer
    Buttons buttons_;
    sf::RenderWindow *window_;
    sf::Event *event_;
    all_sprites *sprites_;
    int level_num_;
public:
    GameManager(sf::RenderWindow *window, sf::Event *event, all_sprites *sprites);
    GameManager();
   ~GameManager();
    
    void draw() const;
    void update(float dt);
    void act(float dt);

    point get_coordinates();

    int get_cur_lvl_pos();
    int level_menu(); // main_menu
    void play(); // main while cycle
    void pause(); // wait for tap on play
    void set_speed(); // set coef for dt arg
    void input_handler(); // poll event etc
    void add_tower();
    void quit_game();
    void save_result();
    void load_level(); // calls level constructor
    void restart_level(); // reloads level
};
