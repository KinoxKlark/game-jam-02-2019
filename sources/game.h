#ifndef GAME_H
#define GAME_H

#include "intrinsic.h"
#include "inputs.h"
#include "assets.h"

#include <vector>

struct Entity;

enum EntityType {
    ET_None, //Valeure par défaut
    ET_player,
    ET_alien,
};

enum WeaponType {
    GT_None, //Quand pas d'arme, valeure par défaut
    GT_pistol,
    GT_swapper,
};

enum ProjectileType {
    PT_None, //Quand pas de projectile, valeure par défaut
    PT_pistol_bullet,
    PT_swap_bullet,
};

// TODO(Sam): On devrait pas merge avec le concepte d'entity ?
struct Projectile {
    ProjectileType type;

    Entity* user;

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

    Entity* user;

    //used to avoid weapon spam.
    r32 cooldown;
    r32 waited_time;
    bool used;
};

Weapon createWeapon(WeaponType type,Entity* user = nullptr);

struct Entity {
    EntityType type;

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
    std::vector<Weapon> weapons;
    size_t weapon_id; //indew of the weapon in weapons

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
Entity createEntity(EntityType type);

void clean_up_entities(GameData& data);
void clean_up_projectiles(GameData& data);
void clean_up(GameData& data);


void game_apply_physic_entities(GameData& data, r32 world_delta_time);
void game_apply_physic_projectiles(GameData& data, r32 world_delta_time);
void game_apply_physic(GameData& data, r32 world_delta_time);

#endif
