#include "../headers/Level.h"


#define  MAP_FILE(num) (std::string("maps/")   + std::to_string(num) + std::string(".txt")).c_str()
#define WAVE_FILE(num) (std::string("levels/") + std::to_string(num) + std::string(".txt")).c_str()

const int MAX_STR_SIZE = 1024;


Level::Level(sf::RenderWindow *window, all_sprites *sprites, int num) :
map_(window, *sprites->map_sprite, MAP_FILE(num)),
entity_manager_(),
waves_(std::vector<Wave*> ())
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
        std::string wave_info = std::string(str);
        this->waves_.push_back(new Wave(wave_info));
        fin.getline(str, MAX_STR_SIZE + 1);
    }

    fin.close();
}

#undef  MAP_FILE
#undef WAVE_FILE


Level::Level() :
map_(),
entity_manager_(),
waves_(std::vector<Wave*> ())
{}

Level::~Level()
{
    for (auto wave : this->waves_)
        delete wave;
}

void Level::damage_hq(int n)
{
    this->hq_health_ -= n;
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
