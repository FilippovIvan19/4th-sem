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
    sf::Clock *main_clock_;
    all_sprites *sprites_;
    int level_num_;
    float time_coef_;
    bool is_pause_;
    bool is_speed_up_;
    int chosen_tower_;
public:
    GameManager(sf::RenderWindow *window, sf::Event *event, sf::Clock *main_clock, all_sprites *sprites);
    GameManager();
   ~GameManager();
    
    void draw() const; //ready
    void update(float dt); //ready
    void act(float dt); //ready

    point get_coordinates(); //ready

    int get_cur_lvl_pos(); //ready
    int level_menu(); // main_menu //ready
    void pause(); // wait for tap on play //ready
    void set_speed(); // set coef for dt arg //ready
    void input_handler(); // poll event etc
    void add_tower(point coords); //ready
    void quit_game();
    void save_result();
    void load_level(); // calls level constructor //ready
    void restart_level(); // reloads level //ready
    void main_cycle(); //ready
};
