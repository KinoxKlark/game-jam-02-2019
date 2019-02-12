#include "game.h"
#include "intrinsic.h"

#include <cmath>
#include <cstdlib>
#include <iostream>

// TODO(Sam): Nettoyer ca !
void game_init(GameData& data)
{
	Weapon player_weapon;
	player_weapon.type = GT_pistol;
	player_weapon.projectile_type = PT_pistol_bullet;
	player_weapon.cooldown = 0.2; // sec
	player_weapon.used = false;
	player_weapon.waited_time = 0;

	// Entities
	data.projectiles = std::vector<Projectile>(500);
	data.entities = std::vector<Entity>(500);
	
	// Player
	data.player = &(data.entities[0]);
	data.player->to_destroy = false;
	data.player->pos.x = 3; // units
	data.player->pos.y = 2; // units
	data.player->max_speed = 10.f;    // units / sec
	data.player->acceleration = 10.f; // units / sec^2
	data.player->masse = 60.f; // 60kg
	data.player->collision_radius = .45f; // units
	data.player->tp_charge = 0;
	data.player->tp_charging_speed = 3; // units / sec
	data.player->tp_max_distance = 5;   // units
	data.player->orientation.x = 0; // Unitlength vector
	data.player->orientation.y = 1;
	data.player->weapon = player_weapon;
	data.player->asset_type = AssetType::PLAYER;
	data.player->life_max = 20;
	data.player->life = 20;

    data.player->is_rolling = false;
    data.player->rolling_duration = 0.5;
    data.player->time_spent_rolling = 0.f;
	data.player->rolling_speed = 14.f;

	// Camera
	data.camera.pos.x = data.player->pos.x;
	data.camera.pos.y = data.player->pos.y;
	data.camera.speed.x = 0;
	data.camera.speed.y = 0;
	
	data.time_factor = 1.f;

	// Debug
    data.debug_infos.frame_length_milliseconds = 0;
}

void game_tick(GameData& data, Inputs& inputs)
{
	r32 friction(0.5f); //Can depend on the floor
	r32 world_delta_time = data.time_factor*inputs.delta_time;
	
	// Slow motion
	// TODO(Sam): Transition plus smooth
	// C'est pour ce genre de test que le nom charging_tp n'est pas
	// du tout adapte, ici ce qu'on veut dire c'est : si l'action
	// secondaire est en cours alors ralentir le temps
	if(inputs.charging_tp == true)
	{
		data.time_factor = 0.2f;
	}
	else
	{
		data.time_factor = 1.f;
	}
	
	//teleportation
	if(inputs.charging_tp == true)
	{
		data.player->tp_charge += inputs.delta_time * data.player->tp_charging_speed;
		if(data.player->tp_charge > data.player->tp_max_distance)
			data.player->tp_charge = data.player->tp_max_distance;
	}
	else if(data.player->tp_charge)
	{
		data.player->pos += data.player->tp_charge * inputs.direction1;
		data.player->tp_charge = 0;
	}
	
	//moving
	{
		if(inputs.action3)
			data.player->is_rolling = true;

		if(data.player->time_spent_rolling > data.player->rolling_duration)
		{
			data.player->time_spent_rolling = 0;
			data.player->is_rolling = false;
		}

		if(data.player->is_rolling)
		{
			data.player->time_spent_rolling += world_delta_time;
			// vector deviation = inputs.direction1 * data.player->rolling_speed * 0.5f;
			vector rolling_speed = data.player->rolling_speed * data.player->orientation;
			data.player->pos += ( rolling_speed) * world_delta_time;
		}
		else
		{
		
			vector acceleration =
				inputs.direction1 * data.player->acceleration -
				data.player->speed * friction;

			data.player->speed += data.player->masse * acceleration * world_delta_time;

			r32 speed_norm = norm(data.player->speed);

			//limits the speed
			if(speed_norm > data.player->max_speed)
				data.player->speed *= data.player->max_speed / speed_norm;
	
			vector wanted_pos = data.player->pos + data.player->speed * world_delta_time;

#if 0		
			for(auto& entity: data.entities)
			{
				// TODO(Sam): Que se passe-t-il lors de la collision ?
				// Touche par un ennemi ...
			}
#endif		
    	
			data.player->pos = wanted_pos;			
		}

	}
	
	//shooting
	r32 direction2_length(norm(inputs.direction2));
	if(direction2_length > 0.1) // TODO(Sam): Quelle sensibilite ?
		data.player->orientation = inputs.direction2 / direction2_length;

	if(data.player->weapon.used)
		data.player->weapon.waited_time += world_delta_time;

	if(data.player->weapon.waited_time > data.player->weapon.cooldown)
	{
		data.player->weapon.waited_time = 0;
		data.player->weapon.used = false;
	}

	if(inputs.shooting and !data.player->weapon.used and !data.player->is_rolling)
	{
			data.player->weapon.used = true;
			// TODO(Sam): Est ce qu'on fera pas une fonction pour cr�er ces entit�s ?
			if(data.player->weapon.type == GT_pistol)
			{
				Projectile p;
				p.type = PT_pistol_bullet;
				p.life_time = 4;
				p.speed = 10;
				p.dommage = 1;
				p.pos = data.player->pos;
				p.direction = data.player->orientation;
				p.asset_type = AssetType::PROJECTILE;
				p.to_destroy = false;

				
				data.projectiles.push_back(p);
			}
	}

	// Ennemis
	// TODO(Sam): Gerer diffrement le cap max des entites
	while(data.entities.size() < 4)
	{
		r32 angle = (r32)(rand() % 360) / 360.f * PI2;
		r32 distance = 10.f;
		
	    Entity entity;
		entity.pos.x = data.player->pos.x + distance * std::cos(angle);
		entity.pos.y = data.player->pos.y + distance * std::sin(angle);
		entity.max_speed = 5.f;
		entity.acceleration = 1.f;
		entity.masse = 60.f; // 60kg
		entity.collision_radius = .4f;
		entity.life_max = 5;
		entity.life = 5;

		entity.to_destroy = false;

		data.entities.push_back(entity);
	}
	for(auto& entity : data.entities)
	{
		if(&entity == data.player) continue;
		
		if(entity.life <= 0.f)
		{
			entity.to_destroy = true;
		}
		else
		{
			vector direction = vector(data.player->pos - entity.pos);

			//moving
			vector acceleration =
				direction * entity.acceleration -
				entity.speed * friction;

			entity.speed += entity.masse * acceleration * world_delta_time;

			r32 speed_norm = norm(entity.speed);

			//limits the speed
			if(speed_norm > entity.max_speed)
				entity.speed *= entity.max_speed / speed_norm;

#if 0			// On met temporairement en pause les entitys	
			entity.pos += entity.speed * world_delta_time;
#else
			vector wanted_pos = entity.pos + entity.speed * world_delta_time;

			for(auto& other_entity: data.entities)
			{
				if(&other_entity == &entity) continue;
					
				vector wp_from_other_entity = wanted_pos - other_entity.pos;
				r32 distance_final = norm(wp_from_other_entity);
				
				const r32 distance_between = other_entity.collision_radius + entity.collision_radius;

				if(distance_final < distance_between)
				{
					vector push_direction = safe_normalise(wp_from_other_entity);
					wanted_pos = other_entity.pos + push_direction*distance_between;
				}
			}
			
			entity.pos = wanted_pos;
#endif	
		}	
	}


	// Projectiles
	for(auto& projectile : data.projectiles)
	{
		if(projectile.life_time > 0)
		{
			projectile.pos += projectile.direction *
				projectile.speed * world_delta_time;
			projectile.life_time -= world_delta_time;

			for(auto& entity: data.entities)
			{
				// TODO(Sam): Gerer la collision avec le joueur
				// TODO(Sam): Ca veut dire qu'on a besoin d'un
				// concepte de tireur ou d'invulnerabilite initiale
				if(&entity == data.player) continue;
				
				vector from_entity = projectile.pos - entity.pos;
				r32 distance = norm(from_entity);
		    
				if(distance < entity.collision_radius)
				{
					entity.life -= projectile.dommage;
					projectile.to_destroy = true;
				}
			}
		}
		else
		{
			projectile.to_destroy = true;
		}
	}


	// Camera
	{
		// Camera focus
	    r32 direction2_length(norm(inputs.direction2));
		r32 speed_factor(.1f);
		r32 distance_upfront(1.f);
		vector marker_1(
			data.player->pos+data.player->orientation*distance_upfront*direction2_length
			+ data.player->speed*speed_factor);

		vector marker_2(marker_1);
		if(data.player->tp_charge > 0)
		{
			// TODO(Sam): On a ce code aussi dans render, peut etre on veut garder
			// la position du tp dans les data pour ne pas se repeter ?
			marker_2 = data.player->pos + (data.player->tp_charge * inputs.direction1);
		}

		r32 k(0.75);
		data.camera.focus_pos = (1.f-k)*marker_1+k*marker_2;

		// Camera mouvement
		vector direction_focus = data.camera.focus_pos - data.camera.pos;
		r32 distance_focus = norm(direction_focus);
		distance_focus = distance_focus < 0.01 ? 1.f : distance_focus;
		const r32 camera_masse(20.f); // kg
		const r32 attraction_factor(5.f);
		const r32 camera_friction(0.9f);

		vector acceleration = camera_masse*(attraction_factor*direction_focus*distance_focus
			- camera_friction*data.camera.speed);

		// TOOD(Sam): Est ce qu'on utilise la vitesse du jeu ou du monde?
		data.camera.speed += acceleration * world_delta_time;
		data.camera.pos += data.camera.speed * world_delta_time;
	}


	// Destruction des divers entites et projectiles
    for(size_t i(0); i < data.entities.size() ; i++)
	{
		if(data.entities[i].to_destroy)
		{
			data.entities[i] = data.entities[data.entities.size()-1];
			data.entities.pop_back();
			i--;
		}
	}
	for(size_t i(0); i < data.projectiles.size() ; i++)
	{
		if(data.projectiles[i].to_destroy)
		{
			data.projectiles[i] = data.projectiles[data.projectiles.size()-1];
			data.projectiles.pop_back();
			i--;
		}
	}

	return;
}
