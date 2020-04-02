#include "Cell.h"

Cell::Cell(sf::RenderWindow* window, sf::Sprite sprite,
  int col, int row, char cell_type):
cell_type_(cell_type),
CommonElement(window, col * CELL_SIZE, row * CELL_SIZE,
  sprite, CELL_PIC_SIZE, CELL_PIC_SIZE)
{
  switch(cell_type) {
    case '.':
      this->set_frame(0, 0);
    break;

    case 'O':
    case 'T':
    case 'S':
    case 'E':
      this->set_frame(1, 0);
    break;
  }
}

Cell::Cell():
cell_type_(0),
CommonElement()
{}

Cell::~Cell()
{}

char Cell::get_type() const {
  return this->cell_type_;
}

void Cell::highlight() {
  this->sprite_.setColor(sf::Color::Green);
  // this->set_frame(this->sprite_.getTextureRect().left / this->sprite_.getTextureRect().width, 1);
}

void Cell::darken() {
  this->sprite_.setColor(sf::Color::White);
  // this->set_frame(this->sprite_.getTextureRect().left / this->sprite_.getTextureRect().width, 0);
  // printf("dark\n");
}
