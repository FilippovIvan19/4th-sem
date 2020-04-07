#pragma once

#include "Level.h"
#include "Buttons.h"


class GameManager
{
private:
    Level *level; // should be deleted soc it's a pointer
    Buttons buttons_;
    static point get_coordinates();
public:
    GameManager(/* args */);
    // GameManager();
   ~GameManager();
    
    void draw() const;
    void update(float dt);
    void act(float dt);

    void choose_level(); // main_menu
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
