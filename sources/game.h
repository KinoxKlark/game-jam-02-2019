#ifndef GAME_H
#define GAME_H
#include "intrinsic.h"
#include "inputs.h"

struct Entity {
    vector pos;
    vector speed;
    r32 acceleration = 1;
    r32 max_speed = 0.5;
};


// TODO(Sam): Mettre �a dans une partie debug
struct DebugInfos {
	i32 frame_length_milliseconds;
};

struct GameData {
    Entity player;

	DebugInfos debug_infos;
};

void game_tick(GameData& data, Inputs& inputs);

#endif
