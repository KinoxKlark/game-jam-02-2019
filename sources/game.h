#ifndef GAME_H
#define GAME_H

#include "intrinsic.h"
#include "inputs.h"
#include "assets.h"

#include <vector>

enum GunType {
    GT_pistol
};

enum ProjectileType {
    PT_pistol_bullet
};

// TODO(Sam): On devrait pas merge avec le concepte d'entity ?
struct Projectile {
    ProjectileType type;
    r32 life_time;
    r32 speed;
    vector pos;
    vector direction;
    r32 dommage;
    AssetType asset_type;
};

struct Gun {
    GunType type;
    ProjectileType projectile_type;
};

struct Entity {
	// C'est des game_unit par sec etc...
    vector pos;
    vector speed;
	vector orientation;

    r32 max_speed;
    r32 acceleration;
    r32 masse;
    r32 life;

	// TODO(Sam): Est ce que les ennemis doivent avoir ca ?
	// c'est probablement le signe qu'il faut qu'on revoie
	// un jour le système d'entity
    r32 tp_charge;
    r32 tp_charging_speed;
    r32 tp_max_distance;

    Gun gun;

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
