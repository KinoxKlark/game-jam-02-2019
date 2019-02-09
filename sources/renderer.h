#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include "intrinsic.h"
#include "game.h"

void render(GameData const& data, sf::RenderWindow& window, Inputs const& inputs);

#endif
