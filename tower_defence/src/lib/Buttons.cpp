#include "../headers/Buttons.h"


Buttons::Buttons(sf::RenderWindow* window, sf::Sprite sprite)
{
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        this->button_array_[i] = Cell(window, sprite, MAP_WIDTH, i, Direction::ERR);
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
                break;
            case Buttons::Order::PillTower :
                this->button_array_[i].set_frame(10, 0);
                break;
            
            default:
                this->button_array_[i].set_frame(6, 0);
                break;
        }

        this->background_[i] = Cell(window, sprite, MAP_WIDTH, i, Direction::ERR);
        this->background_[i].set_frame(7, 0);
    }
}

Buttons::Buttons()
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
}

void Buttons::highlight(int num)
{
    // printf("high\n");
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
