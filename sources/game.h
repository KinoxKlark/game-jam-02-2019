#ifndef GAME_H
#define GAME_H

#include "intrinsic.h"
#include "inputs.h"
#include "assets.h"

#include <vector>

// TODO(Sam): On devrait pas merge avec le concepte d'entity ?
struct Projectile {
    r32 life_time;
    r32 speed;
    vector pos;
    vector direction;

    AssetType asset_type;
};

struct Entity {
	// C'est des game_unit par sec etc...
    vector pos;
    vector speed;
    r32 max_speed;
    r32 acceleration;
    r32 masse;

	vector direction_shoot;

    r32 tp_charge;
    r32 tp_charging_speed;
    r32 tp_max_distance;

    AssetType asset_type;
};

// TODO(Sam): On devrait pas merge avec le concepte d'entity ?
struct Camera {
    vector pos;
	vector speed;
	vector focus_pos;
};


// TODO(Sam): Mettre ca dans une partie debug
struct DebugInfos {
	i32 frame_length_milliseconds;
};

struct GameData {
    Entity player;
	Camera camera;
    std::vector<Projectile> projectiles;
    std::vector<Entity> ennemies;
	r32 time_factor;

    Assets assets;

	DebugInfos debug_infos;
};

void game_tick(GameData& data, Inputs& inputs);
void game_init(GameData& data);

#endif
