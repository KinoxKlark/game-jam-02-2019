#include "game.h"

#include <iostream> // TODO: A enlever, c'�tait pour le test

void game_tick(GameData& data, Inputs& inputs)
{
  // TODO(David): Commence ici
  std::cout << "Game Tick!" << "\n";

  data.player.speed += inputs.direction;
  
  data.player.pos += data.player.speed;

  return;
}
