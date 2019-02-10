#ifndef GAME_H
#define GAME_H

#include "intrinsic.h"
#include "inputs.h"
#include "assets.h"

#include <vector>


struct Projectile {
    r32 life_time;
    r32 speed;
    vector pos;
    vector direction;

	AssetType asset_type;
};

struct Entity {
	
	// Todo(Sam): C'est des pixels par secondes, et des
	// pixels par secondes par secondes, a voir pour
	// uniformiser en game unit ou autre
    vector pos;
    vector speed;
    r32 max_speed;
    r32 acceleration;
    r32 masse;

    r32 tp_charge;
    r32 tp_charging_speed;
    r32 tp_max_distance;

AssetType asset_type;
};


// TODO(Sam): Mettre ca dans une partie debug
struct DebugInfos {
	i32 frame_length_milliseconds;
};

struct GameData {
    Entity player;
    std::vector<Projectile> projectiles;
	r32 time_factor;

Assets assets;

	DebugInfos debug_infos;
};

void game_tick(GameData& data, Inputs& inputs);
void game_init(GameData& data);

#endif
