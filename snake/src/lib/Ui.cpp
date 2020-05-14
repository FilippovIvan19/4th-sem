#include "../headers/Ui.hpp"

#include <cstring>
#include "../headers/TextUi.hpp"

Ui* Ui::instance = nullptr;

Ui* Ui::get(const char* ui_type)
{
    if (ui_type && !instance)
    {
        if (!strcmp(ui_type, "text"))
            instance = new TextUi();
        // if (!strcmp(ui_type, "graph"))
        //     instance = new GraphUi();
    }
    return instance;
}

Ui::~Ui()
{
    instance = nullptr;
}
