#pragma once

#include "constants.h"
// #include <SFML/Window/Event.hpp>
#include <SFML/Audio.hpp>


#include "GameManager.h"
#include "LevelIcon.h"
#include "PillTower.h"
#include "BacteriaUnit.h"
#include "Map.h"
#include "Buttons.h"
#include "Level.h"


void load_textures(all_textures *textures);
void load_sprites(all_sprites *sprites, all_textures *textures);
