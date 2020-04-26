#include "../headers/Buttons.h"


Buttons::Buttons(sf::RenderWindow* window, sf::Sprite sprite, sf::Font *font) :
window_(window)
{
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        this->button_array_[i] = Cell(window, sprite, MAP_WIDTH, i, Direction::ERR);
        this->background_[i] = Cell(window, sprite, MAP_WIDTH, i, Direction::ERR);
        this->background_[i].set_frame(7, 0);
        this->labels_[i] = sf::Text();

        switch (i)
        {
            case Buttons::Order::Pause :
                this->button_array_[i].set_frame(3, 0);
                break;
            case Buttons::Order::SpeedUp :
                this->button_array_[i].set_frame(1, 0);
                break;
            case Buttons::Order::Exit :
                this->button_array_[i].set_frame(4, 0);
                break;
            case Buttons::Order::Menu :
                this->button_array_[i].set_frame(2, 0);
                break;
            case Buttons::Order::Restart :
                this->button_array_[i].set_frame(5, 0);
                break;
            case Buttons::Order::CapsuleTower :
                this->button_array_[i].set_frame(9, 0);
                this->labels_[i] = make_coins_text(std::to_string(CAPSULE_TOWER_COST), font, i);
                break;
            case Buttons::Order::PillTower :
                this->button_array_[i].set_frame(10, 0);
                this->labels_[i] = make_coins_text(std::to_string(PILL_TOWER_COST), font, i);
                break;
            case Buttons::Order::Coins :
                this->button_array_[i].set_frame(6, 0);
                this->labels_[i] = make_coins_text(std::to_string(0), font, i);
                break;
            case Buttons::Order::Health :
                this->button_array_[i].set_frame(6, 0);
                this->labels_[i] = make_coins_text(std::to_string(0), font, i);
                break;
            
            default:
                this->button_array_[i].set_frame(6, 0);
                break;
        }
    }
}

Buttons::Buttons() :
window_(nullptr)
{}

Buttons::~Buttons()
{}

void Buttons::draw() const
{
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        this->background_[i].draw();
        this->button_array_[i].draw();
    }
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        this->window_->draw(this->labels_[i]);
    }
    
}

void Buttons::highlight(int num)
{
    this->background_[num].set_frame(8, 0);
    if (num == Buttons::Order::Pause)
        this->button_array_[num].set_frame(0, 0);
}

void Buttons::darken(int num)
{
    this->background_[num].set_frame(7, 0);
    if (num == Buttons::Order::Pause)
        this->button_array_[num].set_frame(3, 0);
}

sf::Text Buttons::make_coins_text(std::string str, sf::Font *font, int row)
{
    sf::Text text(str, *font, 30 * GLOBAL_SCALE_COEF);
    text.setPosition(MAP_WIDTH * CELL_SIZE + 2, row * CELL_SIZE);
    text.setFillColor(sf::Color::Yellow);
    text.setOutlineColor(sf::Color::Red);
    text.setOutlineThickness(1);
    text.setScale(1.2, 1);
    return text;
}

void Buttons::set_coins(int count)
{
    this->labels_[Buttons::Order::Coins].setString("coins\n" + std::to_string(count));
}

void Buttons::set_health(int count)
{
    this->labels_[Buttons::Order::Health].setString("hp\n" + std::to_string(count));
}
