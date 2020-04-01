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

        case '0':
        case '2':
        case '4':
        case '6':
            this->sprite_.move(CELL_SIZE / 2., CELL_SIZE / 2.);
            this->sprite_.setOrigin(CELL_SIZE, CELL_SIZE);
            this->sprite_.setRotation( (int)(cell_type - '0') * 45);
            printf("%d, %c\n", cell_type, cell_type);
            this->set_frame(2,0);
            break;

        case '1':
        case '3':
        case '5':
        case '7':
            this->sprite_.move(CELL_SIZE / 2., CELL_SIZE / 2.);
            this->sprite_.setOrigin(CELL_SIZE, CELL_SIZE);
            this->sprite_.setRotation( (int)(cell_type - '0' - 1) * 45);
            printf("%d, %c\n", cell_type, cell_type);
            this->set_frame(3,0);
            break;

        case 'a':
        case 'b':
        case 'c':
        case 'd':
            this->sprite_.move(CELL_SIZE / 2., CELL_SIZE / 2.);
            this->sprite_.setOrigin(CELL_SIZE, CELL_SIZE);
            this->sprite_.setRotation( (int)(cell_type - 'a') * 90);
            printf("%d, %c\n", cell_type, cell_type);
            this->set_frame(4,0);
            break;

        case 'O':
        case 'T':
        case 'S':
        case 'E':
            this->set_frame(1, 0);
            break;

        case 'P':
            break;
        default:
            this->set_frame(5,0);
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
  this->sprite_.setColor(sf::Color(255, 255, 255, 220));
  // this->set_frame(this->sprite_.getTextureRect().left / this->sprite_.getTextureRect().width, 1);
}

void Cell::darken() {
  this->sprite_.setColor(sf::Color::White);
  // this->set_frame(this->sprite_.getTextureRect().left / this->sprite_.getTextureRect().width, 0);
  // printf("dark\n");
}
