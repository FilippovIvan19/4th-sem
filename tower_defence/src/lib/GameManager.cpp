#include "../headers/GameManager.h"
#include "../headers/LevelIcon.h"


GameManager::GameManager(sf::RenderWindow *window, sf::Event *event, all_sprites *sprites) :
level_(nullptr),
buttons_(window, *sprites->buttons_sprite),
window_(window),
event_(event),
sprites_(sprites),
level_num_(-1)
{}

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

int GameManager::level_menu()
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
                this->window_->close();
                return 0;
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
    return this->level_num_;
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
    this->level_ = new Level(this->window_, this->sprites_, this->level_num_);
}
