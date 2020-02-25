#pragma once

#include "cell.h"
#include "stdio.h"
#include <fstream>
#include <iostream>
#include <list>

typedef struct point {
  int x;
  int y;
} point;

int ptr_x(int i);
int ptr_y(int i);

class Map : public Cell {
private:
  int read_map(const char* name);
  char scheme_[MAP_HEIGHT][MAP_WIDTH];
  int map_id_;
  point* turn_vector;
protected:
public:

  std::list<point> free_places;
  std::list<point> busy_places;

  Cell cell_array[MAP_HEIGHT][MAP_WIDTH];

  Map();
  Map(sf::RenderWindow* window, sf::Sprite map_sprite, const char* filename, int map_id);
 ~Map();
 void map_draw() const;
 point* get_turns() const;
};
