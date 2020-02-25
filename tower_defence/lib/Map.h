#pragma once

#include "Cell.h"
#include "stdio.h"
#include <fstream>
#include <iostream>
#include <list>


class Map {
private:
  std::set<point, cmp_points> free_places;
  std::set<point, cmp_points> busy_places;
  std::vector<point> turn_vector;
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
};
