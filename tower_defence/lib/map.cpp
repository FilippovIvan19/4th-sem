#include "map.h"
#include "stdio.h"

int ptr_x(int i) {
  switch(i) {
    case 0:
    return 1;
    case 1:
    return 0;
    case 2:
    return -1;
    case 3:
    return 0;
  }
}

int ptr_y(int i) {
    switch(i) {
      case 0:
      return 0;
      case 1:
      return -1;
      case 2:
      return 0;
      case 3:
      return 1;
    }
}

Map::Map(sf::RenderWindow* window, sf::Sprite map_sprite, sf::String* scheme, int map_id):
map_id_(map_id),
scheme_(scheme),
free_places(std::set <point> ()),
busy_places(std::set <point> ())
{
  int row;
  int col;
  int spawn_row;
  int spawn_col;
  int despawn_row;
  int despawn_col;
  int turn_count = 0;

  printf("\n");
  for (row = 0; row < MAP_HEIGHT; row++) {
    for (col = 0; col < MAP_WIDTH; col++) {
      switch(scheme_[row][col]) {
        case '.': // common
        printf(".");
        break;

        case 'P': // tower placing available
        point p;
        //p.x = col;
        //p.y = row;
        //free_places.insert(p);
        break;
        case '1':

        break;
        case '2':

        break;
        case '3':

        break;
        case '4':

        break;
        case '5':

        break;
        case '6':

        break;
        case '7':

        break;
        case '8':

        break;


        case 'O': // common road
        printf("O");
        break;

        case 'S': // spawn road
        printf("S");
        spawn_row = row;
        spawn_col = col;
        break;

        case 'T': // turn right
        printf("T");
        turn_count++;
        break;

        case 'E': // end road
        printf("E");
        despawn_row = row;
        despawn_col = col;
        break;

        default:
        cell_array[row][col] = Cell(window, map_sprite,
          0, 0, '?');
        break;
      }
      cell_array[row][col] = Cell(window, map_sprite, row, col, scheme_[row][col]);

    }
    printf("\n");
  }
  printf("\n turns: %d\n", turn_count);

  point* turn_array = new point [turn_count+2];
  turn_array[0].x = spawn_col;
  turn_array[0].y = spawn_row;
  turn_array[turn_count + 1].x = despawn_col;
  turn_array[turn_count + 1].y = despawn_row;

  int turn = 0;
  int wrong_way = 4;
  row = spawn_row;
  col = spawn_col;
  int itr = 0;
  while(turn < turn_count && itr < 100000) {
    itr ++;
    for (int i = 0; i < 4; i++ ) {
      int xi = col + ptr_x(i);
      int yi = row + ptr_y(i);
      if ((i != wrong_way) &&
          (xi >= 0 && xi < MAP_WIDTH) &&
          (yi >= 0 && yi < MAP_HEIGHT) &&
          ((scheme_[yi][xi] == 'T') || (scheme_[yi][xi] == 'O'))) {
            printf("type %c\n", scheme_[yi][xi]);
        col = col + ptr_x(i);
        row = row + ptr_y(i);
        if (scheme_[yi][xi] == 'T') {
          turn++;
          turn_array[turn].x = col;
          turn_array[turn].y = row;

        }
        wrong_way = (i + 2) % 4;

        break;
      }
    }
  }
  printf("\n");
  for (int turn = 0; turn < turn_count+2; turn++) {
      printf("%d) %d | %d\n", turn, turn_array[turn].x, turn_array[turn].y);
  }


}

Map::Map():
map_id_(0),
scheme_(nullptr)
{}

Map::~Map()
{}

void Map::map_draw() const {
  printf("\n\n\n");
  for (int row = 0; row < MAP_HEIGHT; row++) {
    for (int col = 0; col < MAP_WIDTH; col++) {
      cell_array[row][col].draw();
      printf("%c", cell_array[row][col].cell_type_);
    }
    printf("\n");
  }
}

point* Map::get_turns() const {
  return this->turn_vector;
}
