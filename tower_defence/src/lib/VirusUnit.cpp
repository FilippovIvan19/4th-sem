#include "../headers/VirusUnit.h"

VirusUnit::VirusUnit() : 
Unit()
{}

VirusUnit::VirusUnit(sf::RenderWindow *window, float x0, float y0,
    int health, float velocity, int cost, sf::Sprite sprite, sf::Sprite health_sprite, Level *level) :
Unit(window, health, velocity, cost, VIRUS_UNIT_POWER,
    x0, y0, sprite, health_sprite, VIRUS_UNIT_PIC_SIZE, VIRUS_UNIT_PIC_SIZE, level)
{}

VirusUnit::~VirusUnit()
{}
