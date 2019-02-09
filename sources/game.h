#ifndef GAME_H
#define GAME_H
#include "intrinsic.h"
#include <SFML/System/Vector2.hpp>
typedef sf::Vector2<r32> vector;

enum HorizontalMove {
    HM_NONE,
    HM_LEFT,
    HM_RIGHT
};

enum VerticalMove {
    VM_NONE,
    VM_UP,
    VM_DOWN
};

struct Entity {
    vector pos;
};


// TODO(Sam): Mettre �a dans une partie debug
struct DebugInfos {
	i32 frame_length_milliseconds;
};

struct GameData {
    Entity player;

	DebugInfos debug_infos;
};

// TODO(Sam): Est ce que c'est le bon endroit pour �a ?
struct Events {
    HorizontalMove h_move;
    VerticalMove v_move;
};

void game_tick(GameData& data, Events& events);
void game_init(GameData& data);

#endif
