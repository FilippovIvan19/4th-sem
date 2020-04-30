#include "../headers/controllers.hpp"

#include "../headers/Ui.hpp"
#include "../headers/Game.hpp"

Human::Human(Game& game) :
Control(game)
{
    using namespace std::placeholders;
    Ui::get()->on_key(std::bind(&Human::keypressed, this, _1));
}

void Human::keypressed(int key)
{
    if (stopped)
        return;

    switch(key)
    {
        case Ui::KEY_UP:
            dir = Direction::UP;
            break;
        case Ui::KEY_DOWN:
            dir = Direction::DOWN;
            break;
        case Ui::KEY_RIGHT:
            dir = Direction::RIGHT;
            break;
        case Ui::KEY_LEFT:
            dir = Direction::LEFT;
            break;
    }
}


Robot::Robot(Game& game) :
Control(game)
{
    Ui::get()->on_timer(Game::TICK, std::bind(&Robot::tick, this));
}

void Robot::tick()
{
    if (stopped)
        return;

    Ui::get()->on_timer(Game::TICK, std::bind(&Robot::tick, this));

    Direction d[] = { Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT };
    std::random_shuffle(d, d + 4);

    auto head = body.front();
    auto rabbit = game.rabbit_near(head);

    if (rabbit.has_value())
    {
        for (int i = 0; i < 4; ++i)
        {
            dir = d[i];
            Coord next = this->next();
            if (game.is_clear(next) && rabbit->dist(next) < rabbit->dist(head))
                return;
        }
    }

    for (int i = 0; i < 4; ++i)
    {
        dir = d[i];
        Coord next = this->next();
        if (game.is_clear(next))
            return;
    }
}
