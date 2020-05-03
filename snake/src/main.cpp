#include <memory>
#include <cstdio>
#include <iostream>

#include "headers/structs.hpp"
#include "headers/Game.hpp"
#include "headers/Ui.hpp"
#include "headers/controllers.hpp"

int main()
{

    std::unique_ptr<Ui> ui(Ui::get("text"));
    if (!ui)
    {
        std::cout << "wrong ui type\n";
        return 0;
    }

    Game game;
    Human h(game);
    Robot s1(game), s2(game), s3(game);

    ui->run(game);
}
