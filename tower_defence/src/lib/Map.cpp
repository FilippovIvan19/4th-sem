#include "../headers/Map.h"


Map::Map(sf::RenderWindow* window, sf::Sprite map_sprite, const char* filename):
turn_vector_(std::vector<point> ()),
free_places_(std::set<point, cmp_points> ()),
busy_places_(std::set<point, cmp_points> ())
{
    int elem_in_vector = 0;
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

      if       (str[col] == 'S') { // spawn point
          this->turn_vector_.push_back( point{col, row} ); //////////////////////////////////
          elem_in_vector++;
          this->cell_array_[col][row] = Cell(window, map_sprite, col, row, Direction::SPAWN_POINT);
      }
      else if (str[col] == '.') { // no road
          this->cell_array_[col][row] = Cell(window, map_sprite, col, row, Direction::COMMON_POINT);
      }
      else if (str[col] == 'O') { // main road
          this->cell_array_[col][row] = Cell(window, map_sprite, col, row, Direction::ROAD_POINT);
      }
      else if (str[col] == 'P') { // tower placing available
          this->free_places_.insert( point{col, row} );
          this->cell_array_[col][row] = Cell(window, map_sprite, col, row, Direction::FREE_PLACE);
      }
      else if (str[col] == 'T') { // turn point
          this->cell_array_[col][row] = Cell(window, map_sprite, col, row, Direction::TURN_POINT);
      }
      else if (str[col] == 'E') { // end of road
          this->cell_array_[col][row] = Cell(window, map_sprite, col, row, Direction::END_POINT);
      }
      else {
          this->cell_array_[col][row] = Cell(window, map_sprite, col, row, Direction::ERR);
          printf("Map: undefined map symbol.\n");
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
        !(dx || dy) || dx * dy ||
        dx == -prev_dx && dy == -prev_dy ||
        col + dx >= MAP_WIDTH || row + dy >= MAP_HEIGHT  ||
        col + dx < 0 || row + dy < 0
      ) {
        continue;
      }

      Direction cur_type = this->cell_array_[col + dx][row + dy].get_type();
      if (cur_type == Direction::TURN_POINT || cur_type == Direction::ROAD_POINT || cur_type == Direction::END_POINT) {

          make_roadside(col, row, turn_info(prev_dx, prev_dy, dx, dy, 1));
          if ( check_turn( turn_info(prev_dx, prev_dy, dx, dy) ) ) { //road turn
              this->turn_vector_.push_back( point{col, row} ); //////////////////////////////////
              this->cell_array_[col][row].set_type(Direction::TURN_POINT);
              elem_in_vector++;
#ifdef DEBUG
              printf("turn = (%d ; %d)\n", col, row);
#endif
          }


          col += dx;
          row += dy;


          //turn_info(prev_dx, prev_dy, dx, dy);

          prev_dx = dx;
          prev_dy = dy;
          break_flag = true;
      }
    }
  }
#ifdef DEBUG
  // who is here? please, change message to more appropriate. 
  //    i can guess, that's about map initialization
  printf("I'm here!\n");
#endif
  make_roadside(col, row, turn_info(prev_dx, prev_dy, prev_dx, prev_dy));
  // maybe should be deleted
  //turn_info(prev_dx, prev_dy, prev_dx, prev_dy);
  //make_roadside();
  this->turn_vector_.push_back( point{col, row} ); //////////////////////////////////////
  elem_in_vector++;
#ifdef DEBUG
  printf("T + s + e = (25) = %d\n", elem_in_vector);
#endif
}

Map::Map():
turn_vector_(std::vector<point> ()),
free_places_(std::set<point, cmp_points> ()),
busy_places_(std::set<point, cmp_points> ())
{}

Map::~Map()
{}

void Map::draw() const {
  for (int row = 0; row < MAP_HEIGHT; row++) {
    for (int col = 0; col < MAP_WIDTH; col++) {
      cell_array_[col][row].draw();
      // printf("%c", cell_array_[col][row].get_type());
    }
    // printf("\n");
  }
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
    static int i = 0;
    if (p) printf("%d. %d %d %d %d.\t", i++, x0, y0, x, y);

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
            this->cell_array_[col - 1][row + 1].set_type(Direction::LD_INT_ROADSIDE); //a
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
            this->cell_array_[col - 1][row - 1].set_type(Direction::LU_INT_ROADSIDE); //b
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
        //printf("it's_corner!\n");
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
        //printf("it's_turn!\n");
        return 1;
        default:
        return 0;
    }
    return 0;
}

point Map::next_turn(int n) const {
  return n != turn_vector_.size() - 1 ? 
  (point){turn_vector_[n + 1].x * CELL_SIZE,
          turn_vector_[n + 1].y * CELL_SIZE} : 
  END_POINT;
}