#ifndef GAME_H
#define GAME_H
#include "intrinsic.h"
#include <SFML/System/Vector2.hpp>
typedef sf::Vector2<r32> vector;

// enum HorizontalMove {
//     HM_NONE,
//     HM_LEFT,
//     HM_RIGHT
// };

// enum VerticalMove {
//     VM_NONE,
//     VM_UP,
//     VM_DOWN
// };

struct Entity {
    vector pos;
    vector speed;
};

struct GameData {
    Entity player;
};

// TODO(Sam): Est ce que c'est le bon endroit pour �a ?
struct Inputs {
    vector direction;
};

void game_tick(GameData& data, Inputs& inputs);

#endif
