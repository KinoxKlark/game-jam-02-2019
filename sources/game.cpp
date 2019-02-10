#include "game.h"
#include "intrinsic.h"

#include <cmath>
#include <iostream>

// TODO(Sam): Nettoyer ca !
void game_init(GameData& data)
{
	Weapon player_weapon;
	player_weapon.type = GT_pistol;
	player_weapon.projectile_type = PT_pistol_bullet;
	player_weapon.cooldown = 0.2;
	player_weapon.used = false;
	player_weapon.waited_time = 0;
	// Player
	data.player.to_destroy = false;
	data.player.pos.x = 300;
	data.player.pos.y = 200;
	data.player.max_speed = 1000.f;
	data.player.acceleration = 1000.f;
	data.player.masse = 60.f;// 60kg
	data.player.collision_radius = 45.f;
	data.player.tp_charge = 0;
	data.player.tp_charging_speed = 300;
	data.player.tp_max_distance = 500;
	data.player.orientation.x = 0;
	data.player.orientation.y = 1;
	data.player.weapon = player_weapon;
	data.player.asset_type = AssetType::PLAYER;
	data.player.life_max = 20;
	data.player.life = 20;
	
	data.camera.pos.x = data.player.pos.x;
	data.camera.pos.y = data.player.pos.y;
	data.camera.speed.x = 0;
	data.camera.speed.y = 0;
	
	data.time_factor = 1.f;

	data.projectiles = std::vector<Projectile>(500);
	data.ennemies = std::vector<Entity>(500);

	for(size_t i(0); i < 3; i++)
	{
		Entity e;
		e.pos.x = data.player.pos.x + (i+1) * 100;
		e.pos.y = data.player.pos.y;
		e.max_speed = 500.f;
		e.acceleration = 100.f * i;
		e.masse = 60.f;// 60kg
		e.collision_radius = 45.f;
		e.life_max = 5;
		e.life = 1;

		e.to_destroy = false;

		data.ennemies.push_back(e);
	}

	// Debug
    data.debug_infos.frame_length_milliseconds = 0;
}

void game_tick(GameData& data, Inputs& inputs)
{
	r32 friction(0.5f);//Can depend on the floor
	r32 world_delta_time = data.time_factor*inputs.delta_time;
	
	// Slow motion
	// TODO(Sam): Transition plus smooth
	// C'est pour ce genre de test que le nom charging_tp n'est pas
	// du tout adapt�, ici ce qu'on veut dire c'est : si l'action
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
		data.player.tp_charge += world_delta_time * data.player.tp_charging_speed;
		if(data.player.tp_charge > data.player.tp_max_distance)
			data.player.tp_charge = data.player.tp_max_distance;
	}
	else if(data.player.tp_charge)
	{
		// std::cout << "tp_charge" << data.player.tp_charge << std::endl;
		// std::cout << "x" << inputs.direction1.x << std::endl;
		// std::cout << "y" << inputs.direction1.y << std::endl;
		data.player.pos += data.player.tp_charge * inputs.direction1;
		data.player.tp_charge = 0;
	}
	
	//moving
	{
		vector acceleration =
			inputs.direction1 * data.player.acceleration -
			data.player.speed * friction;

		data.player.speed += data.player.masse * acceleration * world_delta_time;

		r32 speed_norm = norm(data.player.speed);

		//limits the speed
		if(speed_norm > data.player.max_speed)
			data.player.speed *= data.player.max_speed / speed_norm;
  
		vector wanted_pos = data.player.pos + data.player.speed * world_delta_time;

#if 0		
		for(auto& entity: data.ennemies)
		{
			vector wp_from_entity = wanted_pos - entity.pos;
			r32 distance_final = norm(wp_from_entity);
			
			const r32 distance_between = entity.collision_radius + data.player.collision_radius;

			if(distance_final < distance_between)
			{
				// TODO(Sam): Que se passe-t-il lors de la collision ?
				// Touche par un ennemi ...

				//vector push_direction = safe_normalise(wp_from_entity);
				//wanted_pos = entity.pos + push_direction*distance_between;
			}
		}
#endif		
    	
		data.player.pos = wanted_pos;
	}
	
	//shooting
	r32 direction2_length(norm(inputs.direction2));
	if(direction2_length > 0.1) // TODO(Sam): Quelle sensibilit� ?
		data.player.orientation = inputs.direction2 / direction2_length;

	if(data.player.weapon.used)
		data.player.weapon.waited_time += world_delta_time;

	if(data.player.weapon.waited_time > data.player.weapon.cooldown)
	{
		data.player.weapon.waited_time = 0;
		data.player.weapon.used = false;
	}

	if(inputs.shooting and !data.player.weapon.used)
	{
			data.player.weapon.used = true;
			// TODO(Sam): Est ce qu'on fera pas une fonction pour cr�er ces entit�s ?
			if(data.player.weapon.type == GT_pistol)
			{
				Projectile p;
				p.type = PT_pistol_bullet;
				p.life_time = 4;
				p.speed = 200;
				p.dommage = 1;
				p.pos = data.player.pos;
				p.direction = data.player.orientation;
				p.asset_type = AssetType::PROJECTILE;
				p.to_destroy = false;

				
				data.projectiles.push_back(p);
			}
	}

	// Ennemis
	{
		for(auto& ennemi : data.ennemies)
		{
			// TODO(Sam): C'est bien le bon endroit pour faire ca ?
			if(ennemi.life <= 0.f)
			{
				ennemi.to_destroy = true;
			}
			else
			{
				vector direction = vector(data.player.pos - ennemi.pos);

				//moving
				vector acceleration =
					direction * ennemi.acceleration -
					ennemi.speed * friction;

				ennemi.speed += ennemi.masse * acceleration * world_delta_time;

				r32 speed_norm = norm(ennemi.speed);

				//limits the speed
				if(speed_norm > ennemi.max_speed)
					ennemi.speed *= ennemi.max_speed / speed_norm;

#if 0			// On met temporairement en pause les ennemis	
				ennemi.pos += ennemi.speed * world_delta_time;
#else
				vector wanted_pos = ennemi.pos + ennemi.speed * world_delta_time;

				for(auto& entity: data.ennemies)
				{
					if(&entity == &ennemi) continue;
					
					vector wp_from_entity = wanted_pos - entity.pos;
					r32 distance_final = norm(wp_from_entity);
				
					const r32 distance_between = entity.collision_radius + ennemi.collision_radius;

					if(distance_final < distance_between)
					{
						vector push_direction = safe_normalise(wp_from_entity);
						wanted_pos = entity.pos + push_direction*distance_between;
					}
				}
				// TODO(Sam): Il faut merger les deux, les collisions devrait etre testee
				// sur les entites et pas seulement les ennemis...
				if(true)
				{
					vector wp_from_entity = wanted_pos - data.player.pos;
					r32 distance_final = norm(wp_from_entity);
				
					const r32 distance_between = data.player.collision_radius + ennemi.collision_radius;

					if(distance_final < distance_between)
					{
						vector push_direction = safe_normalise(wp_from_entity);
						wanted_pos = data.player.pos + push_direction*distance_between;
					}
				}
			
				ennemi.pos = wanted_pos;
#endif	
			}	
		}
	}

	// Projectiles
	for(auto& projectile : data.projectiles)
	for(size_t i(0); i < data.projectiles.size() ; i++)
	{
		if(projectile.life_time > 0)
		{
			projectile.pos += projectile.direction *
				projectile.speed * world_delta_time;
			projectile.life_time -= world_delta_time;

			for(auto& entity: data.ennemies)
			{
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
		vector marker_1(
			data.player.pos+data.player.orientation*100.f*direction2_length
			+ data.player.speed*speed_factor);

		vector marker_2(marker_1);
		if(data.player.tp_charge > 0)
		{
			// TODO(Sam): On a ce code aussi dans render, peut etre on veut garder
			// la position du tp dans les data pour ne pas se repeter ?
			marker_2 = data.player.pos + (data.player.tp_charge * inputs.direction1);
		}

		r32 k(0.75);
		data.camera.focus_pos = (1.f-k)*marker_1+k*marker_2;

		// Camera mouvement
		vector direction_focus = data.camera.focus_pos - data.camera.pos;
		r32 distance_focus = norm(direction_focus);
		distance_focus = distance_focus < 0.01 ? 1.f : distance_focus;
		const r32 camera_masse(20.f); // kg
		const r32 attraction_factor(.1f);
		const r32 camera_friction(0.9f);

		vector acceleration = camera_masse*(attraction_factor*direction_focus*distance_focus
			- camera_friction*data.camera.speed);

		// TOOD(Sam): Est ce qu'on utilise la vitesse du jeu ou du monde?
		data.camera.speed += acceleration * world_delta_time;
		data.camera.pos += data.camera.speed * world_delta_time;
	}


	// Destruction des divers entites et projectiles
    for(size_t i(0); i < data.ennemies.size() ; i++)
	{
		if(data.ennemies[i].to_destroy)
		{
			data.ennemies[i] = data.ennemies[data.ennemies.size()-1];
			data.ennemies.pop_back();
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
