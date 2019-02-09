#include "game.h"

#include <iostream>

// TODO(Sam): Nettoyer ça !
void game_init(GameData& data)
{
	//data.player = Enitiy();
	data.debug_infos.frame_length_milliseconds = 0;
}

void game_tick(GameData& data, Inputs& inputs)
{
  //TODO : Handle combinaison of Horizontal and Vertical move

  data.player.speed += inputs.direction;
  
  data.player.pos += data.player.speed;

  return;
}
