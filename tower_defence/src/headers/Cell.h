#pragma once

#include "Tower.h"

class Cell : public CommonElement {
private:
  Direction cell_type_;
public:
  Tower *tower_;

  Cell();
  Cell(sf::RenderWindow* window, sf::Sprite sprite,
    int col, int row, Direction cell_type);
 ~Cell();

  Direction get_type() const;
  void set_type(Direction cell_type);
  void highlight();
  void darken();
};
