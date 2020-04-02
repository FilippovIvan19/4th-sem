#include "../headers/Map.h"


Map::Map(sf::RenderWindow* window, sf::Sprite map_sprite, const char* filename):
turn_vector(std::vector<point> ()),
free_places(std::set<point, cmp_points> ()),
busy_places(std::set<point, cmp_points> ())
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
      this->cell_array[col][row] = Cell(window, map_sprite, col, row, str[col]);
      if (str[col] == 'S') { // spawn road
        this->turn_vector.push_back( point{col, row} );
      }
      if (str[col] == 'P') { // tower placing available
        this->free_places.insert( point{col, row} );
      }
    }
    row++;
  }
  fin.close();

  row = this->turn_vector[0].y;
  col = this->turn_vector[0].x;

  int prev_dx = 0;
  int prev_dy = 0;

  while (this->cell_array[col][row].get_type() != 'E') { // end of road
    if (this->cell_array[col][row].get_type() == 'T') { //road turn
      this->turn_vector.push_back( point{col, row} );
    }

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

      char cur_type = this->cell_array[col + dx][row + dy].get_type();
      if (cur_type == 'T' || cur_type == 'O' || cur_type == 'E') {
        col += dx;
        row += dy;
        prev_dx = dx;
        prev_dy = dy;
        break_flag = true;
      }
    }
  }
  this->turn_vector.push_back( point{col, row} );
}

Map::Map():
turn_vector(std::vector<point> ()),
free_places(std::set<point, cmp_points> ()),
busy_places(std::set<point, cmp_points> ())
{}

Map::~Map()
{}

void Map::draw() const {
  for (int row = 0; row < MAP_HEIGHT; row++) {
    for (int col = 0; col < MAP_WIDTH; col++) {
      cell_array[col][row].draw();
      // printf("%c", cell_array[col][row].get_type());
    }
    // printf("\n");
  }
}

void Map::highlight_free() {
  for (auto &cell: this->free_places) {
    this->cell_array[cell.x][cell.y].highlight();
  }
}

void Map::darken_free() {
  for (auto &cell: this->free_places) {
    this->cell_array[cell.x][cell.y].darken();
  }
}

void Map::mark_busy(point cell) {
  this->free_places.erase(cell);
  this->busy_places.insert(cell);
}

void Map::mark_free(point cell) {
  this->busy_places.erase(cell);
  this->free_places.insert(cell);
}
