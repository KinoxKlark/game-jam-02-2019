#ifndef GAME_H
#define GAME_H
#include "intrinsic.h"
#include <SFML/System/Vector2.hpp>
typedef sf::Vector2<r32> vector;

enum HMove {
    none,
    left,
    right
};

struct Entity {
    vector pos;
};

struct GameData {
    Entity player;
};

// TODO(Sam): Est ce que c'est le bon endroit pour �a ?
struct Events {
    HMove h_move;
};

void game_tick(GameData& data, Events& events);

#endif
