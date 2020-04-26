#include "../headers/BacteriaUnit.h"

BacteriaUnit::BacteriaUnit() : 
Unit()
// Unit(Unit_kind::Bacteria) // experimental
{}

BacteriaUnit::BacteriaUnit(sf::RenderWindow *window, float x0, float y0,
    int health, float velocity, int cost, sf::Sprite sprite, Level *level) :
Unit(window, Unit_kind::Bacteria, health, velocity, cost,
    x0, y0, sprite, BACTERIA_UNIT_PIC_SIZE, BACTERIA_UNIT_PIC_SIZE, level)
{}

BacteriaUnit::~BacteriaUnit()
{}
