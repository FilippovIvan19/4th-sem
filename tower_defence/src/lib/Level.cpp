#include "../headers/Level.h"
#include "string.h"

#define  MAP_FILE(num) (std::string("maps/")   + std::to_string(num) + std::string(".txt")).c_str()
#define WAVE_FILE(num) (std::string("levels/") + std::to_string(num) + std::string(".txt")).c_str()


Level::Level(sf::RenderWindow *window, all_sprites *sprites, int num) :
map_(window, *sprites->map_sprite, MAP_FILE(num)),
entity_manager_(),
waves_(std::vector<Wave*> ()),
cur_wave_num_(-1)
{
    std::ifstream fin;
    fin.open(WAVE_FILE(num));

    if (!(fin.is_open()))
    {
        printf("File not found\n");
        return;
    }

    char str[1024];
    fin.getline(str, MAX_STR_SIZE + 1, '#');
    fin.getline(str, MAX_STR_SIZE + 1);

    while(!fin.eof())
    {
        fin.getline(str, MAX_STR_SIZE + 1, '#');
        if (str[strlen(str) - 1] == '\n')
            str[strlen(str) - 1] = '\0';
        std::string wave_info = std::string(str);
        this->waves_.push_back(new Wave(window, sprites, &this->map_, wave_info));
        fin.getline(str, MAX_STR_SIZE + 1);
    }

    fin.close();
}

#undef  MAP_FILE
#undef WAVE_FILE


Level::Level() :
map_(),
entity_manager_(),
waves_(std::vector<Wave*> ()),
cur_wave_num_(-1)
{}

Level::~Level()
{
    for (auto wave : this->waves_)
        delete wave;
}

void Level::draw() const
{
    this->map_.draw();
    this->entity_manager_.draw();
}

void Level::act(float dt)
{
    this->entity_manager_.act(dt);
}

void Level::update(float dt)
{
    this->entity_manager_.update(dt);
}

void Level::run_wave(int wave_num)
{

    this->cur_wave_num_ = wave_num;
    if (wave_num >= this->waves_.size())
        this->entity_manager_.set_wave(nullptr);
    else
        this->entity_manager_.set_wave(this->waves_[wave_num]);
}

GameCodes Level::check_wave()
{
    // printf("check wave\n");
    if (!this->entity_manager_.is_cur_wave_alive())
    {
        this->run_wave(this->cur_wave_num_ + 1);
        printf("run next wave %d\n", this->cur_wave_num_);
    }
    if (this->cur_wave_num_ == this->waves_.size())
    {
        if (this->map_.get_health() <= 0)
            return GameCodes::LEVEL_FAILED;
        else
            return GameCodes::LEVEL_COMPLETED;
    }
    else
        return GameCodes::NOTHING;
}
