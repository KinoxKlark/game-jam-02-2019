#include "game.h"
#include "intrinsic.h"

#include <cmath>

// TODO(Sam): Nettoyer ca !
void game_init(GameData& data)
{
	// Player
	data.player.pos.x = 300;
	data.player.pos.y = 200;
	data.player.max_speed = 1000.f;
	data.player.acceleration = 1000.f;

	// Debug
    data.debug_infos.frame_length_milliseconds = 0;
}

void game_tick(GameData& data, Inputs& inputs)
{
	r32 masse(60.f); // 60kg
	r32 friction(0.5f);
	vector acceleration =
		inputs.direction * data.player.acceleration -
		data.player.speed * friction;

	data.player.speed += masse * acceleration * inputs.delta_time;
	// * data.player.acceleration 

	// data.player.speed *= 0.9;

	r32 speed_norm = norm(data.player.speed);

	//limits the speed
	if(speed_norm > data.player.max_speed)
		data.player.speed *= data.player.max_speed / speed_norm;
  
	data.player.pos += data.player.speed * inputs.delta_time;

	return;
}
