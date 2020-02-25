#pragma once

#include "CommonElement.h"

class Cell : public CommonElement {
private:
  char cell_type_;
public:
  Cell();
  Cell(sf::RenderWindow* window, sf::Sprite sprite,
    int col, int row, char cell_type);
 ~Cell();

  char get_type() const;
  void highlight();
  void darken();
};
