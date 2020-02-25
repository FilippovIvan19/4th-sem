#pragma once

#include "CommonElement.h"

class Cell : public CommonElement {
public:
  char cell_type_;
  //char get_type() const;
  Cell();
  Cell(sf::RenderWindow* window, sf::Sprite sprite,
    int row, int col, char cell_type);
 ~Cell();
};
