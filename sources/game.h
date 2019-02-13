#ifndef GAME_H
#define GAME_H

#include "intrinsic.h"
#include "inputs.h"
#include "assets.h"

#include <vector>

enum WeaponType {
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

	bool to_destroy;
	
    AssetType asset_type;
};

struct Weapon {
    WeaponType type;
    ProjectileType projectile_type;

    //used to avoid weapon spam.
    r32 cooldown;
    r32 waited_time;
    bool used;
};

struct Entity {
	// C'est des game_unit par sec etc...
    vector pos;
    vector speed;
	vector acc;
	
	vector orientation;

	// TODO(Sam): On veut pas garder limit_the_speed, c'est un fix
	// temporaire
	bool limit_the_speed;

	bool to_destroy;

    bool is_rolling;
    r32 rolling_duration;
    r32 time_spent_rolling;
    r32 rolling_speed;


    r32 max_speed;
    r32 acceleration;
    r32 mass;
	r32 collision_radius;
    r32 life_max;
    r32 life;

	// TODO(Sam): Est ce que les ennemis doivent avoir ca ?
	// c'est probablement le signe qu'il faut qu'on revoie
	// un jour le systeme d'entity
    r32 tp_charge;
    r32 tp_charging_speed;
    r32 tp_max_distance;

    Weapon weapon;

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
	Entity* player;
	std::vector<Entity> entities;
    std::vector<Projectile> projectiles;
	
	Camera camera;
	r32 time_factor;
	r32 ground_friction;

    Assets assets;

	DebugInfos debug_infos;
};

void game_tick(GameData& data, Inputs& inputs);
void game_init(GameData& data);

#endif
