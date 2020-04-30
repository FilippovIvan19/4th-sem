#include "../headers/Control.hpp"

#include "../headers/Game.hpp"
#include "../headers/Ui.hpp"

Control::Control(Game& game) :
Snake(game),
game(game)
{
    game.add(*this);
}
