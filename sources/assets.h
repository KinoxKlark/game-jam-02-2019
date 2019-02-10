#ifndef ASSETS_H
#define ASSETS_H

#include "intrinsic.h"
#include <SFML/Graphics.hpp>

enum AssetType {
	NONE,
	PLAYER,
    PROJECTILE
};

struct Assets {
	sf::Font font;
	sf::CircleShape player;
	sf::CircleShape projectile;
};

bool load_assets(Assets& assets);

#endif
