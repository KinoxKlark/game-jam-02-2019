#include "game.h"
#include "intrinsic.h"

#include <cmath>
#include <iostream>

// TODO(Sam): Nettoyer ca !
void game_init(GameData& data)
{
	// Player
	data.player.pos.x = 300;
	data.player.pos.y = 200;
	data.player.max_speed = 1000.f;
	data.player.acceleration = 1000.f;
	data.player.masse = 60.f;// 60kg
	data.player.tp_charge = 0;
	data.player.tp_charging_speed = 300;
	data.player.tp_max_distance = 500;

	data.time_factor = 1.f;

	// data.projectiles = std::vector<Projectile>();

	// Debug
    data.debug_infos.frame_length_milliseconds = 0;
}

void game_tick(GameData& data, Inputs& inputs)
{
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
	r32 world_delta_time = data.time_factor*inputs.delta_time;
	
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
	r32 friction(0.5f);
	vector acceleration =
		inputs.direction1 * data.player.acceleration -
		data.player.speed * friction;

	data.player.speed += data.player.masse * acceleration * world_delta_time;

	r32 speed_norm = norm(data.player.speed);

	//limits the speed
	if(speed_norm > data.player.max_speed)
		data.player.speed *= data.player.max_speed / speed_norm;
  
	data.player.pos += data.player.speed * world_delta_time;

	//shooting
	if(inputs.shooting)
	{
		Projectile p;
		p.life_time = 4;
		p.speed = 200;
		p.pos = data.player.pos;
		p.direction = inputs.direction2;

		data.projectiles.push_back(p);
	}

	for(size_t i(0); i < data.projectiles.size() ; i++)
	{
		if(data.projectiles[i].life_time > 0)
		{
			data.projectiles[i].pos += data.projectiles[i].direction * data.projectiles[i].speed * world_delta_time;
			data.projectiles[i].life_time -= world_delta_time;
		}
		else
		{
			data.projectiles[i] = data.projectiles[data.projectiles.size()-1];
			data.projectiles.pop_back();
			i--;
		}
		

	}


	return;
}
