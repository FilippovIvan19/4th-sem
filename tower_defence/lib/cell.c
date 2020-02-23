#include<cell.h>

Cell::Cell(sf::RenderWindow* window, sf::Sprite sprite,
  row, col, int frame_width, int frame_height, int cell_type, char arrow):
_cell_type(cell_type),
_arrow(arrow),
CommonElement(window, col * frame_width, row * frame_height,
  sprite, frame_width, frame_height),
{}

Cell::Cell():
_cell_type(0),
_arrow(0),
CommonElement()
{}

Cell::~Cell
{}
