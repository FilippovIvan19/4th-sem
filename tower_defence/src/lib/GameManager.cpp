#include "../headers/GameManager.h"
#include "../headers/LevelIcon.h"
#include "../headers/PillTower.h"


GameManager::GameManager(sf::RenderWindow *window, sf::Event *event, sf::Clock *main_clock, all_sprites *sprites) :
level_(nullptr),
buttons_(window, *sprites->buttons_sprite),
window_(window),
event_(event),
main_clock_(main_clock),
sprites_(sprites),
level_num_(-1),
time_coef_(1),
is_pause_(false),
is_speed_up_(false),
chosen_tower_(-1)
{
    this->pause();
}

//add initialisation
GameManager::GameManager() :
level_(nullptr),
buttons_()
{}


void GameManager::draw() const
{
    this->window_->clear();

    this->buttons_.draw();
    if (this->level_)
        this->level_->draw();
    
    this->window_->display();
}

void GameManager::act(float dt)
{
    if (this->level_)
        this->level_->act(dt);
}

void GameManager::update(float dt)
{
    if (this->level_)
        this->level_->update(dt);
}

GameManager::~GameManager()
{}

GameCodes GameManager::level_menu()
{
    LevelIcon *level[LEVEL_COUNT + 1];
    for (int i = 0; i < LEVEL_COUNT; ++i)
    {
        level[i] = new LevelIcon(this->window_, LEVEL_GRID_X0 + LEVEL_OFFSET_X * (i % LEVEL_COUNT_X),
         LEVEL_GRID_Y0 + LEVEL_OFFSET_Y * (i / LEVEL_COUNT_X), *this->sprites_->level_icon_sprite,
         i, LEVEL_ICON_PIC_SIZE, LEVEL_ICON_PIC_SIZE);
    }
    level[0]->set_lock(false);

    CommonElement menu(this->window_, 0, 0, *this->sprites_->menu_background_sprite, MENU_PIC_WIDTH, MENU_PIC_HEIGHT);
    bool is_menu = true;

    int level_num;

    while(is_menu)
    {
        level_num = this->get_cur_lvl_pos();
        if (level_num != LEVEL_COUNT)
            level[level_num]->set_frame(1, 0); // move sprite rect to right

        this->window_->clear();
        menu.draw();
        for(int i = 0; i < LEVEL_COUNT; ++i)
            level[i]->draw();
        this->window_->display();

        while (this->window_->pollEvent(*this->event_))
        {
            if (this->event_->type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                return GameCodes::EXIT_APP;
            }
            else if (this->event_->type == sf::Event::MouseButtonPressed && 
                     sf::Mouse::isButtonPressed(sf::Mouse::Left))
                if(level_num > -1 && level_num < LEVEL_COUNT)
                {
                    if(!level[level_num]->is_locked())
                        is_menu = false;
                }
        }

        if (level_num != LEVEL_COUNT)
            level[level_num]->set_frame(0, 0); // move sprite rect to left
    }
    printf("%d level chosen\n", level_num);
    for (int i = 0; i < LEVEL_COUNT; ++i)
        delete level[i];

    this->level_num_ = level_num + 1;
    this->load_level();
    return GameCodes::NOTHING;
}

int GameManager::get_cur_lvl_pos()
{
    int position = LEVEL_COUNT; // LEVEL_COUNT is a default case value

    for (int i = 0; i < LEVEL_COUNT; ++i)
    {
        if (sf::IntRect(LEVEL_GRID_X0 + LEVEL_OFFSET_X * (i % LEVEL_COUNT_X),
         LEVEL_GRID_Y0 + LEVEL_OFFSET_Y * (i / LEVEL_COUNT_X),
         LEVEL_ICON_SIZE, LEVEL_ICON_SIZE).contains(sf::Mouse::getPosition(*this->window_)))
        {
            position = i;
            break;
        }
    }
    
    return position;
}

void GameManager::load_level()
{
    if (this->level_)
        delete this->level_;
    if (this->level_num_ < 1)
        printf("wrong level number");
    this->level_ = new Level(this->window_, this->sprites_, this->level_num_);
    
    this->level_->run_wave(0);
}

GameCodes GameManager::main_cycle()
{
    GameCodes retval = GameCodes::NOTHING;
    while (true)
    {
        retval = this->level_menu();
        if (retval == GameCodes::EXIT_APP)
        {
            this->window_->close();
            return GameCodes::EXIT_APP;
        }

        retval = this->level_cycle();
        switch (retval)
        {
            case GameCodes::LEVEL_COMPLETED:
                this->clear_state();
                break;

            case GameCodes::EXIT_APP:
                this->window_->close();
                return GameCodes::EXIT_APP;
                break;
            
            default:
                break;
        }
    }
}

GameCodes GameManager::level_cycle()
{
    GameCodes retval = GameCodes::NOTHING;
    this->main_clock_->restart();
    float dt = 0;
    this->draw();

    while (this->window_->isOpen())
    {
        retval = this->input_handler();
        if (retval == GameCodes::EXIT_APP || retval == GameCodes::EXIT_LEVEL)
            return retval;

        dt = this->main_clock_->getElapsedTime().asMicroseconds();
        this->main_clock_->restart();

        if (!this->is_pause_)
        {
            dt *= this->time_coef_ / 1e6;

            this->act(dt);
            this->update(dt);
        }

        this->draw();

        retval = this->level_->check_wave();
        if (retval == GameCodes::EXIT_APP || retval == GameCodes::LEVEL_COMPLETED)
            return retval;
    }
    return GameCodes::EXIT_APP;
}

GameCodes GameManager::input_handler()
{
    while (this->window_->pollEvent(*this->event_))
    {
        point coords;
        switch (this->event_->type)
        {
            case sf::Event::Closed:
                return GameCodes::EXIT_APP;
                break;

            case sf::Event::KeyPressed:
                switch (this->event_->key.code)
                {
                    case sf::Keyboard::Escape:
                        return GameCodes::EXIT_APP;
                        break;

                    case sf::Keyboard::R:
                        this->restart_level();
                        break;

                    case sf::Keyboard::Right:
                        this->set_speed();
                        break;

                    case sf::Keyboard::Space:
                        this->pause();
                        break;
                    
                    default:
                        // printf("nothing to do\n");
                        break;
                }
                break;

            case sf::Event::MouseButtonPressed:
                coords = this->get_coordinates();
                if (coords.x == MAP_WIDTH)
                    switch (coords.y)
                    {
                        case Buttons::Order::Pause:
                            this->pause();
                            break;

                        case Buttons::Order::Exit:
                            return GameCodes::EXIT_APP;
                            break;

                        case Buttons::Order::Restart:
                            this->restart_level();
                            break;

                        case Buttons::Order::SpeedUp:
                            this->set_speed();
                            break;

                        case Buttons::Order::CapsuleTower:
                        case Buttons::Order::PillTower:
                        // case Buttons::Order::MixtureeTower:
                            this->add_tower(coords);
                            break;
                        
                        default:
                            // printf("nothing to do\n");
                            break;
                    }
                else
                    this->add_tower(coords);
                break;
            
            default:
                // printf("nothing to do\n");
                break;
        }
    }
}

point GameManager::get_coordinates()
{
    sf::Vector2i coords = sf::Mouse::getPosition(*this->window_);
    return {(int)coords.x / CELL_SIZE, (int)coords.y / CELL_SIZE};
}


void GameManager::pause()
{
    if (this->is_pause_)
        this->buttons_.darken(Buttons::Order::Pause);
    else
        this->buttons_.highlight(Buttons::Order::Pause);
    this->is_pause_ = !this->is_pause_;
}

void GameManager::set_speed()
{
    if (this->is_speed_up_)
    {
        this->buttons_.darken(Buttons::Order::SpeedUp);
        this->time_coef_ = 1;
    }
    else
    {
        this->buttons_.highlight(Buttons::Order::SpeedUp);
        this->time_coef_ = 7;
    }
    this->is_speed_up_ = !this->is_speed_up_;
}

void GameManager::clear_state()
{
    if (this->is_speed_up_)
        this->set_speed();
    if (!this->is_pause_)
        this->pause();
    if (this->chosen_tower_ != -1)
        this->buttons_.darken(this->chosen_tower_);
    this->chosen_tower_ = -1;
    
    while (this->window_->pollEvent(*this->event_));
    
    this->main_clock_->restart();
}

void GameManager::restart_level()
{
    this->clear_state();
    this->load_level();
}

void GameManager::add_tower(point coords)
{
    if (coords.x == MAP_WIDTH)
    {
        if (coords.y == this->chosen_tower_)
        {
            this->chosen_tower_ = -1;
            this->buttons_.darken(coords.y);
            printf("case1\n");
        }
        else
        {
            if (this->chosen_tower_ != -1)
                this->buttons_.darken(this->chosen_tower_);
            this->chosen_tower_ = coords.y;
            this->buttons_.highlight(this->chosen_tower_);
            printf("case2\n");
        }
    }
    else
    {
        if (this->chosen_tower_ == -1 || !this->level_->map_.is_free(coords))
        {
            printf("case3\n");
            return;
        }
        else
        {
            printf("case4\n");
            Tower *tower;
            switch (this->chosen_tower_)
            {
                // case Buttons::Order::CapsuleTower:
                //     tower = new CapsuleTower();
                //     break;
                case Buttons::Order::PillTower:
                    tower = new PillTower(this->window_, coords.x * CELL_SIZE, coords.y * CELL_SIZE, this->sprites_);
                    break;
                
                default:
                    break;
            }
            this->level_->map_.mark_busy(coords);
            this->level_->map_.cell_array_[coords.x][coords.y].tower_ = tower;
            this->level_->entity_manager_.add(tower);
        }
    }
}

void GameManager::save_result()
{

}
