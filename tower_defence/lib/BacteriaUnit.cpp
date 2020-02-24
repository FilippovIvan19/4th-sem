#include "BacteriaUnit.h"

// experimental
BacteriaUnit::BacteriaUnit() : 
Unit(Unit_kind::Bacteria)
{}

BacteriaUnit::BacteriaUnit(sf::RenderWindow *window, float x0, float y0, 
        sf::Sprite sprite, int frame_width, int frame_height) :
Unit(window, Unit_kind::Bacteria, BACTERIA_UNIT_HEALTH, (float)BACTERIA_UNIT_VELOCITY,
    x0, y0, sprite, BACTERIA_UNIT_PIC_SIZE, BACTERIA_UNIT_PIC_SIZE)
{}

BacteriaUnit::~BacteriaUnit()
{}