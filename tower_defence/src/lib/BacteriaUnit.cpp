#include "../headers/BacteriaUnit.h"

BacteriaUnit::BacteriaUnit() : 
Unit()
// Unit(Unit_kind::Bacteria) // experimental
{}

BacteriaUnit::BacteriaUnit(sf::RenderWindow *window, float x0, float y0,
    int health, float velocity, sf::Sprite sprite, Level *level) :
Unit(window, Unit_kind::Bacteria, BACTERIA_UNIT_HEALTH, (float)BACTERIA_UNIT_VELOCITY,
    x0, y0, sprite, BACTERIA_UNIT_PIC_SIZE, BACTERIA_UNIT_PIC_SIZE, level)
{}

BacteriaUnit::~BacteriaUnit()
{}
