#include "../headers/Level.h"
#include "../headers/Wave.h"
#include "string.h"
#include <fstream>
#include <string>
#include <sstream>

#define  MAP_FILE(num) (std::string("maps/")   + std::to_string(num) + std::string(".txt")).c_str()
#define WAVE_FILE(num) (std::string("levels/") + std::to_string(num) + std::string(".txt")).c_str()


Level::Level(sf::RenderWindow *window, all_sprites *sprites, int num) :
waves_(std::vector<Wave*> ()),
cur_wave_num_(-1),
hq_health_(100),
coins_(0),
map_(window, *sprites->map_sprite, *sprites->heart_sprite, MAP_FILE(num)),
entity_manager_()
{
    this->heart_sound_ = new Sound("heart_warn.ogg");

    std::ifstream fin;
    fin.open(WAVE_FILE(num));

    if (!(fin.is_open()))
    {
        printf("File not found\n");
        return;
    }

    char str[1024];

    fin.getline(str, MAX_STR_SIZE + 1, '#');
    fin.getline(str, MAX_STR_SIZE + 1); // skips comments before first sharp

    fin.getline(str, MAX_STR_SIZE + 1, '#');
    std::istringstream stream(str);
    
    while (!stream.eof())
    {
        std::string arg;
        float val;
        stream >> arg >> val;
        
        if (arg == "initial_coins")
            this->coins_ = (int)val;
    }
    fin.getline(str, MAX_STR_SIZE + 1); // read init args

    while(!fin.eof())
    {
        fin.getline(str, MAX_STR_SIZE + 1, '#');
        if (str[strlen(str) - 1] == '\n')
            str[strlen(str) - 1] = '\0';
        std::string wave_info = std::string(str);
        this->waves_.push_back(new Wave(window, sprites, this, wave_info));
        fin.getline(str, MAX_STR_SIZE + 1);
    }

    fin.close();
}

#undef  MAP_FILE
#undef WAVE_FILE


Level::Level() :
waves_(std::vector<Wave*> ()),
cur_wave_num_(-1),
hq_health_(0),
coins_(0),
map_(),
//heart_sound_(nullptr),
entity_manager_()
{}

Level::~Level()
{
    for (auto wave : this->waves_)
        delete wave;
    
    if (this->heart_sound_ != nullptr) {
        delete this->heart_sound_;
        this->heart_sound_ = nullptr;
    }
}

void Level::draw() const
{
    this->map_.draw();
    this->entity_manager_.draw();
}

void Level::act(float dt)
{
    
    this->map_.heart_bit();
    this->entity_manager_.act(dt);
}

void Level::update(float dt)
{
    this->entity_manager_.update(dt);
}

void Level::run_wave(int wave_num)
{
    this->cur_wave_num_ = wave_num;
    if (wave_num >= (int)this->waves_.size())
        this->entity_manager_.set_wave(nullptr);
    else
        this->entity_manager_.set_wave(this->waves_[wave_num]);
}

GameCodes Level::check_wave()
{
    if (this->hq_health_ <= 0)
        return GameCodes::LEVEL_FAILED;
    if (!this->entity_manager_.is_cur_wave_alive())
    {
        this->run_wave(this->cur_wave_num_ + 1);
        if (this->cur_wave_num_ == (int)this->waves_.size())
        {
            return GameCodes::LEVEL_COMPLETED;
            printf("completed\n");
        }
        else
        {
            return GameCodes::WAVE_ENDED;
            printf("ended\n");
        }
        printf("run next wave %d\n", this->cur_wave_num_);
    }
    return GameCodes::NOTHING;
}

std::pair<int, int> Level::get_wave_num() const
{
    return std::pair<int, int>(this->cur_wave_num_, this->waves_.size());
}

void Level::damage_hq(int hp)
{
    this->hq_health_ -= hp;

    if (this->hq_health_ < 100 && this->hq_health_ + hp == 100) {
        this->map_.heart_bit(1);
        this->heart_sound_->play();
    }
    else if (this->hq_health_ < 50 && this->hq_health_ + hp >= 50) {
        this->map_.heart_bit(2);
        this->heart_sound_->play();
    }
    else if (this->hq_health_ < 20 && this->hq_health_ + hp >= 20) {
        this->map_.heart_bit(4);
        this->heart_sound_->play();
    }
    else if (this->hq_health_ < 10 && this->hq_health_ + hp >= 10) {
        this->map_.heart_bit(8);
        this->heart_sound_->play();
    }
    
}

void Level::add_coins(int count)
{
    this->coins_ += count;
}

int Level::get_coins() const
{
    return this->coins_;
}

int Level::get_health() const
{
    return this->hq_health_;
}
