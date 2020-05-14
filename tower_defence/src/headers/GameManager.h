#pragma once

#include <fstream>
#include <string.h>

#include "Buttons.h"
#include "../headers/audio.h"

class Level;

class GameManager
{
private:
    Level *level_; // should be deleted
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
    all_fonts *fonts_;

    Sound* button_click_;
    Sound* level_end_sound_;
public:
    GameManager(sf::RenderWindow *window, sf::Event *event,
        sf::Clock *main_clock, all_sprites *sprites, all_fonts *fonts);
    GameManager();
   ~GameManager();
    
    void draw() const;
    void update(float dt);
    void act(float dt);

    point get_coordinates() const;

    int get_cur_lvl_pos() const;
    GameCodes level_menu();
    void pause();
    void set_speed();
    GameCodes input_handler();
    void add_tower(point coords);
    void save_result(int score);
    LevelProgress read_info(int level_num) const;
    void load_level();
    void restart_level();
    GameCodes level_cycle();
    GameCodes main_cycle();
    void clear_state();
    GameCodes level_end(GameCodes option);
    int get_end_button_num() const;
    void update_coins();
    void update_health();
    bool is_level_end_button_active(GameCodes option, int button_num) const;
    void clear_level();
};