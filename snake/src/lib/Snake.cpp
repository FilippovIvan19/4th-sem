#include "../headers/Snake.hpp"

#include <climits>
#include <random>
#include "../headers/Ui.hpp"
#include "../headers/Game.hpp"


Snake::Snake(Game& g) :
stopped(false),
dir(Direction::RIGHT),
game(g)
{
    static int b = 1;
    id = b++;
    body.push_back(g.randxy());
    Ui::get()->painter(id, body.size());
}

Coord Snake::next()
{
    Coord head = body.front();
    switch(dir)
    {
        case UP:
            --head.second;
            break;
        case DOWN:
            ++head.second;
            break;
        case RIGHT:
            ++head.first;
            break;
        case LEFT:
            --head.first;
            break;
        default:
            break;
    }
    return head;
}

void Snake::move(std::list<Coord>& rabbits)
{
    if (stopped)
        return;

    Coord tail = this->body.back();
    Coord head = this->body.front();
    Coord next = this->next();

    Ui *ui = Ui::get();

    if (!game.is_clear(next))
    {
        stopped = true;
        return;
    }

    body.push_front(next);

    ui->painter({next, id, dir});
    if (tail != head)
        ui->painter({head, id, Direction::BODY});
    
    auto i = std::find(rabbits.begin(), rabbits.end(), next);
    if (i == rabbits.end())
    {
        body.pop_back();
        ui->painter({tail, id, Direction::NONE});
    }
    else
    {
        rabbits.erase(i);
        ui->painter(id, body.size());
    }
}