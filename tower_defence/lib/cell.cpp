#include "cell.h"

Cell::Cell(sf::RenderWindow* window, sf::Sprite sprite,
  int row, int col, char cell_type):
cell_type_(cell_type),
CommonElement(window, col * CELL_WIDTH, row * CELL_HEIGHT,
  sprite, CELL_WIDTH, CELL_HEIGHT)
{
  switch(cell_type) {
    case '.':
    this->set_frame(0, 0);
    break;

    case 'O':
    this->set_frame(2, 2);
    break;

    case 'T':
    this->set_frame(2, 2);
    break;

    case 'S':
    this->set_frame(2, 2);
    break;

    case 'E':
    this->set_frame(2, 2);
    break;
  }

}

Cell::Cell():
cell_type_(0),
CommonElement()
{}

Cell::~Cell()
{}
/*
char Cell::get_type() const {
  return this->cell_type_;
}*/
