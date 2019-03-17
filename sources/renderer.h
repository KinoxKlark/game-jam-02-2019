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
   sf::Texture swapper_pistol_texture;
   sf::Texture tp_target_texture;
};
typedef struct TexturesContainer TexturesContainer;

struct SpritesContainer
{
    sf::Sprite basic_pistol_sprite;
    sf::Sprite swapper_pistol_sprite;
    sf::Sprite tp_target_sprite;
};
typedef struct SpritesContainer SpritesContainer;

TexturesContainer loadTextures();
SpritesContainer loadSprites(TexturesContainer& textures);

void render(GameData const& data, sf::RenderWindow& window, SpritesContainer& game_sprites, Inputs const& inputs);

#endif
