#pragma once

#include "Cell.h"
#include "stdio.h"
#include <fstream>
#include <iostream>
#include <list>

#include <utility> // added

class Map {
private:
  std::set<point, cmp_points> free_places_;
  std::set<point, cmp_points> busy_places_;
  std::vector<point> turn_vector_;
  Cell cell_array[MAP_WIDTH][MAP_HEIGHT];

public:
  Map();
  Map(sf::RenderWindow* window, sf::Sprite map_sprite, const char* filename);
 ~Map();

  void draw() const;
  void highlight_free();
  void darken_free();
  void mark_busy(point cell);
  void mark_free(point cell);
  point next_turn(int n) const;
  Direction turn_info(const int x0, const int y0, const int x, const int y, bool p = false);
  void make_roadside(int col, int row, Direction type);
  bool check_corner(int col, int row);
  bool check_turn(Direction turn);
};
