#pragma once

#include "cell.h"
#include <set>

typedef struct point {
  int x;
  int y;
} point;

int ptr_x(int i);
int ptr_y(int i);

class Map : public Cell {
private:
protected:
public:
  sf::String* scheme_;
  int map_id_;
  point* turn_vector;
  std::set <point> free_places;
  std::set <point> busy_places;

  Cell cell_array[MAP_HEIGHT][MAP_WIDTH];

  Map();
  Map(sf::RenderWindow* window, sf::Sprite map_sprite, sf::String* scheme, int map_id);
 ~Map();
 void map_draw() const;
 point* get_turns() const;
};
