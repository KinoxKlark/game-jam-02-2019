#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include "intrinsic.h"
#include "game.h"

// struct TexturesContainer
// struct SpritesContainer;


struct TexturesContainer
{
   sf::Texture basic_pistol_texture;
};
typedef struct TexturesContainer TexturesContainer;

struct SpritesContainer
{
    sf::Sprite basic_pistol_sprite;
};
typedef struct SpritesContainer SpritesContainer;

TexturesContainer loadTextures();
SpritesContainer loadSprites(TexturesContainer& textures);

void render(GameData const& data, sf::RenderWindow& window, Inputs const& inputs);

#endif
