#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "constants.h"

#define CELL_HEIGHT 100
#define CELL_WIDTH 100

class Cell : public CommonElement {
public:
  int _cell_type;
  char _arrow;
  Cell();
  Cell(sf::RenderWindow* window, sf::Sprite sprite,
    row, col, int frame_width, int frame_height, int cell_type, char arrow);
 ~Cell();
}
