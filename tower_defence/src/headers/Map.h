#pragma once

#include "Cell.h"


class Map {
private:
  std::set<point> free_places_;
  std::set<point> busy_places_;
  std::vector<point> turn_vector_;
  CommonElement heart_;

public:
  Cell cell_array_[MAP_WIDTH][MAP_HEIGHT];

  Map();
  Map(sf::RenderWindow* window, sf::Sprite map_sprite, sf::Sprite heart_sprite, const char* filename);
 ~Map();

  void draw() const;
  void highlight_free();
  void darken_free();
  void mark_busy(point cell);
  void mark_free(point cell);
  point next_turn(int n) const;
  Direction turn_info(const int x0, const int y0, const int x, const int y, bool p = false) const;
  void make_roadside(int col, int row, Direction type);
  bool check_corner(int col, int row) const;
  bool check_turn(Direction turn) const;
  bool is_free(point cell) const;
};
