#ifndef GAME_H
#define GAME_H
#include "intrinsic.h"
#include "inputs.h"

struct Entity {
	
	// Todo(Sam): C'est des pixels par secondes, et des
	// pixels par secondes par secondes, a voir pour
	// uniformiser en game unit ou autre
    vector pos;
    vector speed;
    r32 max_speed;
    r32 acceleration;
};


// TODO(Sam): Mettre ca dans une partie debug
struct DebugInfos {
	i32 frame_length_milliseconds;
};

struct GameData {
    Entity player;

	DebugInfos debug_infos;
};

void game_tick(GameData& data, Inputs& inputs);
void game_init(GameData& data);

#endif
