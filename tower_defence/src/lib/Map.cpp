#include "../headers/Map.h"
#include <fstream>

#include "math.h"


Map::Map(sf::RenderWindow* window, sf::Sprite map_sprite, sf::Sprite heart_sprite, const char* filename):
free_places_(std::set<point> ()),
busy_places_(std::set<point> ()),
turn_vector_(std::vector<point> ()),
heart_phase_(0),
heart_scale_(1),
heart_rate_(0.01 * M_PI), // 1% of phase
heart_(window, 0, 0, heart_sprite, HEART_PIC_SIZE, HEART_PIC_SIZE)
{
  int row = 0;
  int col = 0;
  char str[MAP_WIDTH];
  std::ifstream fin;
  fin.open(filename);
  if (!fin) {
    printf("error openning map file\n");
    return;
  }

  while(!fin.eof() && row < MAP_HEIGHT) {
    fin.getline(str, MAP_WIDTH + 1);
    for (col = 0; col < MAP_WIDTH; col++) {
      if (str[col] == (char)Direction::SPAWN_POINT)
        this->turn_vector_.push_back( point{col, row} );
      else if (str[col] == (char)Direction::FREE_PLACE)
        this->free_places_.insert( point{col, row} );
      
      if (   str[col] != (char)Direction::END_POINT
          && str[col] != (char)Direction::COMMON_POINT
          && str[col] != (char)Direction::ROAD_POINT
          && str[col] != (char)Direction::SPAWN_POINT
          && str[col] != (char)Direction::FREE_PLACE) {
        this->cell_array_[col][row] = Cell(window, map_sprite, col, row, Direction::ERR);
        printf("Map: undefined map symbol.\n");
      } else {
        this->cell_array_[col][row] = Cell(window, map_sprite, col, row, (Direction)str[col]);
      }
    }
    row++;
  }
  fin.close();

  row = this->turn_vector_[0].y;
  col = this->turn_vector_[0].x;

  int prev_dx = 0;
  int prev_dy = 0;

  while (this->cell_array_[col][row].get_type() != Direction::END_POINT) { // end of road


    bool break_flag = false;
    for (int dx = -1; dx <= 1 && !break_flag; dx++)
    for (int dy = -1; dy <= 1 && !break_flag; dy++) {

     if (
        !(dx || dy) || (dx * dy != 0) ||
        (dx == -prev_dx && dy == -prev_dy) ||
        col + dx >= MAP_WIDTH || row + dy >= MAP_HEIGHT  ||
        col + dx < 0 || row + dy < 0
      ) {
        continue;
      }

      Direction cur_type = this->cell_array_[col + dx][row + dy].get_type();
      if (cur_type == Direction::TURN_POINT || cur_type == Direction::ROAD_POINT || cur_type == Direction::END_POINT) {

          make_roadside(col, row, turn_info(prev_dx, prev_dy, dx, dy));
          if ( check_turn( turn_info(prev_dx, prev_dy, dx, dy) ) ) { 
              this->turn_vector_.push_back( point{col, row} );
              this->cell_array_[col][row].set_type(Direction::TURN_POINT);
          }


          col += dx;
          row += dy;


          prev_dx = dx;
          prev_dy = dy;
          break_flag = true;
      }
    }
  }
  
  
  make_roadside(col, row, turn_info(prev_dx, prev_dy, prev_dx, prev_dy));
  this->turn_vector_.push_back( point{col, row} );
  
  this->heart_.set_origin_center();
  this->heart_.set_position((col + 0.5) * CELL_SIZE, (row + 0.5) * CELL_SIZE);
}

Map::Map():
free_places_(std::set<point> ()),
busy_places_(std::set<point> ()),
turn_vector_(std::vector<point> ()),
heart_()
{}

Map::~Map()
{}

void Map::draw() const {
  for (int row = 0; row < MAP_HEIGHT; row++) {
    for (int col = 0; col < MAP_WIDTH; col++) {
      cell_array_[col][row].draw();
    }
  }

  this->heart_.draw();
}

void Map::highlight_free() {
  for (auto &cell: this->free_places_) {
    this->cell_array_[cell.x][cell.y].highlight();
  }
}

void Map::darken_free() {
  for (auto &cell: this->free_places_) {
    this->cell_array_[cell.x][cell.y].darken();
  }
}

void Map::mark_busy(point cell) {
  this->free_places_.erase(cell);
  this->busy_places_.insert(cell);
}

void Map::mark_free(point cell) {
  this->busy_places_.erase(cell);
  this->free_places_.insert(cell);
}

Direction Map::turn_info(const int x0, const int y0, const int x, const int y, bool p) const {
    #ifdef DEBUG
    static int i = 0;
    #endif
    //if (p) printf("%d. %d %d %d %d.\t", i++, x0, y0, x, y);

    // start point directions
    if (x0 == 0 && y0 == 0) {
        if (y == 0) {
            if (x == -1) {
                if (p) printf("Direction: < <\n");
                return Direction::L;
            }
            if (x == 1) {
                if (p) printf("Direction: > >\n");
                return Direction::R;
            }
        }
        if (x == 0) {
            if (y == -1) {
                if (p) printf("Direction:   ^\n");
                return Direction::U;
            }
            if (y == 1) {
                if (p) printf("Direction:   v\n");
                return Direction::D;
            }
        }
    }

    // straight directions
    if (y0 == 0 && y == 0) {
        if (x0 == 1 && x == 1) {
            if (p) printf("Direction: > >\n");
            return Direction::R;
        }
        if (x0 == -1 && x == -1) {
            if (p) printf("Direction: < <\n");
            return Direction::L;
        }
    }

    if (x0 == 0 && x == 0) {
        if (y0 == 1 && y == 1) {
            if (p) printf("Direction:   v\n");
            return Direction::D;
        }
        else if (y0 == -1 && y == -1) {
            if (p) printf("Direction:   ^\n");
            return Direction::U;
        }
    }

    // corner directions
    if (y0 == 0 && x == 0) {
        if (x0 == -1) {
            if (y == -1) {
                if (p) printf("Direction: < ^\n");
                return Direction::LU;
            }
            if (y == 1) {
                if (p) printf("Direction: < v\n");
                return Direction::LD;
            }
        }
        if (x0 == 1) {
            if (y == -1) {
                if (p) printf("Direction: > ^\n");
                return Direction::RU;
            }
            if (y == 1) {
                if (p) printf("Direction: > v\n");
                return Direction::RD;
            }
        }
    }

    if (x0 == 0 && y == 0) {
        if (y0 == -1) {
            if (x == -1) {
                if (p) printf("Direction: ^ <\n");
                return Direction::UL;
            }
            if (x == 1) {
                if (p) printf("Direction: ^ >\n");
                return Direction::UR;
            }
        }
        if (y0 == 1) {
            if (x == -1) {
                if (p) printf("Direction: v <\n");
                return Direction::DL;
            }
            if (x == 1) {
                if (p) printf("Direction: v >\n");
                return Direction::DR;
            }
        }
    }

    printf("Error: unknown direction or wrong arguments!\n");
    return Direction::ERR;
}

void Map::make_roadside(int col, int row, Direction type) {

    if (type == Direction::R || type == Direction::L) {
        if (row - 1 >= 0 && !check_corner(col, row - 1)) {
            this->cell_array_[col][row - 1].set_type(Direction::U_ROADSIDE);
        }
        if (row + 1 < MAP_HEIGHT && !check_corner(col, row + 1)) {
            this->cell_array_[col][row + 1].set_type(Direction::D_ROADSIDE);
        }
        return;
    }
    if (type == Direction::U || type == Direction::D) {
        if (col - 1 >= 0 && !check_corner(col - 1, row)) {
            this->cell_array_[col - 1][row].set_type(Direction::L_ROADSIDE);
        }
        if (col + 1 < MAP_WIDTH && !check_corner(col + 1, row)) {
            this->cell_array_[col + 1][row].set_type(Direction::R_ROADSIDE);
        }
        return;
    }

    if (type == Direction::UL || type == Direction::RD) {
        if (col - 1 >= 0 && row + 1 < MAP_HEIGHT) {
            this->cell_array_[col - 1][row + 1].set_type(Direction::LD_INT_ROADSIDE); // a
        }
        if (col + 1 < MAP_WIDTH && row - 1 >= 0)
            this->cell_array_[col + 1][row - 1].set_type(Direction::RU_EXT_ROADSIDE);
        if (col + 1 < MAP_WIDTH && !check_corner(col + 1, row))
            this->cell_array_[col + 1][row    ].set_type(Direction::R_ROADSIDE);
        if (row - 1 >= 0 && !check_corner(col, row - 1))
            this->cell_array_[col    ][row - 1].set_type(Direction::U_ROADSIDE);
        return;
    }

    if (type == Direction::RU || type == Direction::DL) {
        if (col - 1 >= 0 && row - 1 >= 0) {
            this->cell_array_[col - 1][row - 1].set_type(Direction::LU_INT_ROADSIDE); // b
        }
        if (col + 1 < MAP_WIDTH && row + 1 < MAP_HEIGHT)
            this->cell_array_[col + 1][row + 1].set_type(Direction::RD_EXT_ROADSIDE);
        if (row + 1 < MAP_HEIGHT && !check_corner(col, row + 1))
            this->cell_array_[col    ][row + 1].set_type(Direction::D_ROADSIDE);
        if (col + 1 < MAP_WIDTH && !check_corner(col + 1, row))
            this->cell_array_[col + 1][row    ].set_type(Direction::R_ROADSIDE);
        return;
    }

    if (type == Direction::UR || type == Direction::LD) {
        if (col + 1 < MAP_WIDTH && row + 1 < MAP_HEIGHT) {
            this->cell_array_[col + 1][row + 1].set_type(Direction::RD_INT_ROADSIDE); // d
        }
        if (col - 1 >= 0 && row - 1 >= 0)
            this->cell_array_[col - 1][row - 1].set_type(Direction::LU_EXT_ROADSIDE);
        if (row - 1 >= 0 && !check_corner(col, row - 1))
            this->cell_array_[col    ][row - 1].set_type(Direction::U_ROADSIDE);
        if (col - 1 >= 0 && !check_corner(col - 1, row))
            this->cell_array_[col - 1][row    ].set_type(Direction::L_ROADSIDE);
        return;
    }

    if (type == Direction::DR || type == Direction::LU) {
        if (col + 1 < MAP_WIDTH && row - 1 >= 0) {
            this->cell_array_[col + 1][row - 1].set_type(Direction::RU_INT_ROADSIDE); // c
        }
        if (col - 1 >= 0 && row + 1 < MAP_HEIGHT)
            this->cell_array_[col - 1][row + 1].set_type(Direction::LD_EXT_ROADSIDE);
        if (row + 1 < MAP_HEIGHT && !check_corner(col, row + 1))
            this->cell_array_[col    ][row + 1].set_type(Direction::D_ROADSIDE);
        if (col - 1 >= 0 && !check_corner(col - 1, row))
            this->cell_array_[col - 1][row    ].set_type(Direction::L_ROADSIDE);
        return;
    }

    printf("Map: Error making roadside.\n");
}

bool Map::check_corner(int col, int row) const {
    switch (this->cell_array_[col][row].get_type()) {
        case Direction::RD_INT_ROADSIDE:
        case Direction::RU_INT_ROADSIDE:
        case Direction::LD_INT_ROADSIDE:
        case Direction::LU_INT_ROADSIDE:
        case Direction::RU_EXT_ROADSIDE:
        case Direction::RD_EXT_ROADSIDE:
        case Direction::LU_EXT_ROADSIDE:
        case Direction::LD_EXT_ROADSIDE:
            return 1;
        default:
            return 0;
    }
    return 0;
}

bool Map::check_turn(Direction turn) const {
    switch (turn) {
        case Direction::RD:
        case Direction::RU:
        case Direction::LD:
        case Direction::LU:
        case Direction::UR:
        case Direction::DR:
        case Direction::UL:
        case Direction::DL:
        return 1;
        default:
        return 0;
    }
    return 0;
}

point Map::next_turn(int n) const {
  return n != (int)(turn_vector_.size() - 1) ? 
  (point){turn_vector_[n + 1].x * CELL_SIZE,
          turn_vector_[n + 1].y * CELL_SIZE} : 
  END_POINT;
}

bool Map::is_free(point cell) const
{
  return (bool)this->free_places_.count(cell);
}

void Map::heart_bit(double delta) {
    if (delta >= 0) {
        delta *= (2 * M_PI / 100);
        this->heart_rate_ = delta;
    }
    
    double new_scale = 1;
    if (this->heart_phase_ <= M_PI * 2) {
        new_scale = 1 + sin(this->heart_phase_) * 0.04 * this->heart_rate_ ;
        this->heart_scale_ *= new_scale;
        this->heart_.scale(new_scale, new_scale);
    }
    else if (this->heart_phase_ >= M_PI * 4) {
        this->heart_phase_ = 0;
        if (abs(this->heart_scale_ - 1) >= 0.001) {
            new_scale = 1 / this->heart_scale_;
            this->heart_.scale(new_scale, new_scale);
            this->heart_scale_ *= new_scale;
        }
        //printf("%lf\n", this->heart_scale_);
    }

    this->heart_phase_ += this->heart_rate_;
}
