#include "game.h"

#include <iostream>
#include <cmath>

// TODO(Sam): Nettoyer �a !
void game_init(GameData& data)
{
	//data.player = Enitiy();
	data.debug_infos.frame_length_milliseconds = 0;
}

void game_tick(GameData& data, Inputs& inputs)
{

  data.player.speed += (inputs.direction * data.player.acceleration - data.player.speed * (r32)0.1) * inputs.delta_time;//* data.player.acceleration 

  // data.player.speed *= 0.9;

  r32 speed_norm = sqrt(data.player.speed.x*data.player.speed.x + data.player.speed.y*data.player.speed.y);

  //limits the speed
  if(speed_norm > data.player.max_speed)
    data.player.speed *= data.player.max_speed / speed_norm;
  
  data.player.pos += data.player.speed * inputs.delta_time;

  return;
}
