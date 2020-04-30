#include "../headers/Game.hpp"

#include "../headers/Ui.hpp"
#include "../headers/Snake.hpp"
#include <climits>
#include <random>

static std::random_device rseed;
static std::mt19937 rgen(rseed());


Game::Game()
{
    Ui::get()->on_timer(TICK, std::bind(&Game::move, this));
}

bool Game::is_clear(Coord coord)
{
    Ui *ui = Ui::get();
    
    return (coord.first  != ui->get_width()  && coord.first  != 1 &&
            coord.second != ui->get_height() && coord.second != 1);
}

Coord Game::randxy()
{
    std::uniform_int_distribution<int> xdist(2, Ui::get()->get_width()  - 3);
    std::uniform_int_distribution<int> ydist(2, Ui::get()->get_height() - 3);

    Coord xy;
    do {
        xy = Coord(xdist(rgen), ydist(rgen));
    } while (!is_clear(xy));

    return xy;
}

void Game::add(Snake& sn)
{
    snakes.push_back(sn);
}

void Game::draw()
{
    Ui *ui = Ui::get();
    ui->draw();

    for (const Snake& sn : snakes)
    {
        Direction d = sn.dir;
        for (const auto& elem : sn.body)
        {
            ui->painter({elem, sn.id, d});
            d = Direction::BODY;
        }
        ui->painter(sn.id, sn.body.size());
    }

    for (const Rabbit& rab : rabbits)
        ui->painter(rab);
}

std::optional<Coord> Game::rabbit_near(Coord a)
{
    std::optional<Coord> near;
    int distance = INT_MAX;

    for (auto const& rab : rabbits)
    {
        int dist = rab.dist(a);
        if (dist < distance)
        {
            distance = dist;
            near = rab;
        }
    }

    return near;
}

void Game::move()
{
    Ui::get()->on_timer(TICK, std::bind(&Game::move, this));

    for (Snake &sn : snakes)
        sn.move(rabbits);

    std::uniform_int_distribution<int> dice(1,100/RABBITS_CHANCE);
    if (rabbits.size() < MAX_RABBITS && dice(rgen) == 1)
    {
        auto xy = randxy();
        rabbits.push_back(xy);

        Ui::get()->painter(xy);
    }
}
