#include "../headers/BacteriaUnit.h"

BacteriaUnit::BacteriaUnit() : 
Unit()
{}

BacteriaUnit::BacteriaUnit(sf::RenderWindow *window, float x0, float y0,
    int health, float velocity, int cost, sf::Sprite sprite, sf::Sprite health_sprite, Level *level) :
Unit(window, health, velocity, cost, BACTERIA_UNIT_POWER,
    x0, y0, sprite, health_sprite, BACTERIA_UNIT_PIC_SIZE, BACTERIA_UNIT_PIC_SIZE, level)
{}

BacteriaUnit::~BacteriaUnit()
{}
