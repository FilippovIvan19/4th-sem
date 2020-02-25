#pragma once

#include "CommonElement.h"

class Cell : public CommonElement {
protected:
  char cell_type_;

public:
  Cell();
  Cell(sf::RenderWindow* window, sf::Sprite sprite,
    int row, int col, char cell_type);
    char get_type() const;
 ~Cell();
};
