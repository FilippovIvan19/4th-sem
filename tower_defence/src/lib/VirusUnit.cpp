#include "../headers/VirusUnit.h"

VirusUnit::VirusUnit() : 
Unit()
// Unit(Unit_kind::Bacteria) // experimental
{}

VirusUnit::VirusUnit(sf::RenderWindow *window, float x0, float y0,
    int health, float velocity, int cost, sf::Sprite sprite, Level *level) :
Unit(window, Unit_kind::Simple_virus, health, velocity, cost, VIRUS_UNIT_POWER,
    x0, y0, sprite, VIRUS_UNIT_PIC_SIZE, VIRUS_UNIT_PIC_SIZE, level)
{}

VirusUnit::~VirusUnit()
{}
