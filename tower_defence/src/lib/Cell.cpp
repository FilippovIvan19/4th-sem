#include "../headers/Cell.h"

Cell::Cell(sf::RenderWindow* window, sf::Sprite sprite,
  int col, int row, Direction cell_type):
cell_type_(cell_type),
CommonElement(window, col * CELL_SIZE, row * CELL_SIZE,
  sprite, CELL_PIC_SIZE, CELL_PIC_SIZE)
{
    set_type(cell_type);
}

Cell::Cell():
cell_type_(Direction::ERR),
CommonElement()
{}

Cell::~Cell()
{}

void Cell::set_type(Direction cell_type) {
    this->cell_type_ = cell_type;
    switch(cell_type) {
        case Direction::COMMON_POINT:
            this->set_frame(0, 0);
            break;

        //case '0':
        //case '2':
        //case '4':
        //case '6':
        case Direction::D_ROADSIDE:
        case Direction::U_ROADSIDE:
        case Direction::L_ROADSIDE:
        case Direction::R_ROADSIDE:
            if (this->sprite_.getOrigin().x != CELL_PIC_SIZE / 2 ||
                this->sprite_.getOrigin().y != CELL_PIC_SIZE / 2) {
                    this->sprite_.move(CELL_SIZE / 2., CELL_SIZE / 2.);
                    this->sprite_.setOrigin(CELL_PIC_SIZE / 2, CELL_PIC_SIZE / 2);
            }
            this->sprite_.setRotation( (int)(this->cell_type_) * 45);
            this->set_frame(2,0);
            break;

        case Direction::RU_EXT_ROADSIDE:
        case Direction::RD_EXT_ROADSIDE:
        case Direction::LU_EXT_ROADSIDE:
        case Direction::LD_EXT_ROADSIDE:
            if (this->sprite_.getOrigin().x != CELL_PIC_SIZE / 2 ||
                this->sprite_.getOrigin().y != CELL_PIC_SIZE / 2) {
                    this->sprite_.move(CELL_SIZE / 2., CELL_SIZE / 2.);
                    this->sprite_.setOrigin(CELL_PIC_SIZE / 2, CELL_PIC_SIZE / 2);
            }
            this->sprite_.setRotation( ((int)(this->cell_type_) - 1) * 45);
            //printf("%d, %c\n", cell_type, cell_type);
            this->set_frame(3,0);
            break;

        case Direction::RU_INT_ROADSIDE:
        case Direction::RD_INT_ROADSIDE:
        case Direction::LD_INT_ROADSIDE:
        case Direction::LU_INT_ROADSIDE:
        if (this->sprite_.getOrigin().x != CELL_PIC_SIZE / 2 ||
            this->sprite_.getOrigin().y != CELL_PIC_SIZE / 2) {
                this->sprite_.move(CELL_SIZE / 2., CELL_SIZE / 2.);
                this->sprite_.setOrigin(CELL_PIC_SIZE / 2, CELL_PIC_SIZE / 2);
        }
            this->sprite_.setRotation( ((char)(cell_type) - 'a') * 90);
            //printf("%d, %c\n", cell_type, cell_type);
            this->set_frame(4,0);
            break;

        case Direction::ROAD_POINT:
        case Direction::SPAWN_POINT:
        case Direction::END_POINT:
        case Direction::TURN_POINT:
            this->set_frame(1, 0);
            break;

        case Direction::FREE_PLACE:
            printf("it's free place!\n");
            break;
        default:
            this->set_frame(5,0);
    }
}

Direction Cell::get_type() const {
  return this->cell_type_;
}

void Cell::highlight() {
  this->sprite_.setColor(sf::Color(255, 255, 255, 220));
  // this->set_frame(this->sprite_.getTextureRect().left / this->sprite_.getTextureRect().width, 1);
}

void Cell::darken() {
  this->sprite_.setColor(sf::Color::White);
  //this->set_frame(this->sprite_.getTextureRect().left / this->sprite_.getTextureRect().width, 0);
  // printf("dark\n");
}
