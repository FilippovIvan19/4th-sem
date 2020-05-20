#include "../headers/Buttons.h"


Buttons::Buttons(sf::RenderWindow* window, sf::Sprite sprite, sf::Font *font) :
window_(window),
cur_hint_( -1 )
{
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        this->button_array_[i] = Cell(window, sprite, MAP_WIDTH, i, Direction::ERR);
        this->background_[i] = Cell(window, sprite, MAP_WIDTH, i, Direction::ERR);
        this->background_[i].set_frame(7, 0);
        this->labels_[i] = sf::Text();
        this->hints_[i] = sf::Text();

        switch (i)
        {
            case Buttons::Order::Pause :
                this->button_array_[i].set_frame(3, 0);
                this->hints_[i] = make_hint("Pause game", font, i);
                break;
            case Buttons::Order::SpeedUp :
                this->button_array_[i].set_frame(1, 0);
                this->hints_[i] = make_hint("Change speed", font, i);
                break;
            case Buttons::Order::Exit :
                this->button_array_[i].set_frame(4, 0);
                this->hints_[i] = make_hint("Exit game", font, i);
                break;
            case Buttons::Order::Menu :
                this->button_array_[i].set_frame(2, 0);
                this->hints_[i] = make_hint("Exit level", font, i);
                break;
            case Buttons::Order::Restart :
                this->button_array_[i].set_frame(5, 0);
                this->hints_[i] = make_hint("Restart level", font, i);
                break;
            case Buttons::Order::CapsuleTower :
                this->button_array_[i].set_frame(9, 0);
                this->labels_[i] = make_coins_text(std::to_string(CAPSULE_TOWER_COST), font, i);
                this->hints_[i] = make_hint(
                        "The tower shoots capsules\n"
                        "Damage : 40\n"
                        "Attack range : 7 cells\n"
                        "Tower shoot period : 1.0 sec", font, i);
                break;
            case Buttons::Order::PillTower :
                this->button_array_[i].set_frame(10, 0);
                this->labels_[i] = make_coins_text(std::to_string(PILL_TOWER_COST), font, i);
                this->hints_[i] = make_hint(
                        "The tower shoots pills\n"
                        "Damage : 10\n"
                        "Attack range : 5 cells\n"
                        "Tower shoot period : 0.5 sec", font, i);
                break;
            case Buttons::Order::Coins :
                this->button_array_[i].set_frame(6, 0);
                this->labels_[i] = make_coins_text(std::to_string(0), font, i);
                break;
            case Buttons::Order::Health :
                this->button_array_[i].set_frame(6, 0);
                this->labels_[i] = make_coins_text(std::to_string(0), font, i);
                this->hints_[i] = make_hint("Heart's remaining\n health points", font, i);
                break;
            
            default:
                this->button_array_[i].set_frame(6, 0);
                break;
        }
    }
}

Buttons::Buttons() :
window_(nullptr),
cur_hint_( -1 )
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

    printf("here %d\n", cur_hint_);
    if (cur_hint_ != -1)
        this->window_->draw(hints_[cur_hint_]);
    
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
    text.setFillColor(sf::Color::White);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(1);
    text.setScale(1.2, 1);
    return text;
}

sf::Text Buttons::make_hint(std::string str, sf::Font *font, int row)
{
    sf::Text text(str, *font, 40 * GLOBAL_SCALE_COEF);
    text.setPosition((MAP_WIDTH - 6) * CELL_SIZE, row * CELL_SIZE);
    text.setFillColor(sf::Color::White);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(1.2);
    text.setScale(1.2, 0.8);
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


void Buttons::help()
{
    point coords;
    
    sf::Vector2i coords2i = sf::Mouse::getPosition(*this->window_);
    coords = {(int)coords2i.x / CELL_SIZE, (int)coords2i.y / CELL_SIZE};
    
    if (coords.x == MAP_WIDTH)
    {
        // printf("here\n");
        switch (coords.y)
        {
        case Buttons::Order::Exit :
        case Buttons::Order::Menu :
        case Buttons::Order::Restart :
        case Buttons::Order::PillTower:
        case Buttons::Order::CapsuleTower:
        case Buttons::Order::Health:
        case Buttons::Order::Coins:
            this->cur_hint_ = coords.y;
            break;
        default:
            this->cur_hint_ = -1; 
            break;
        }
    }
    else 
        this->cur_hint_ = -1;

}
