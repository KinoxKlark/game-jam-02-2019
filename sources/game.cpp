#include "game.h"

#include <iostream> // TODO: A enlever, c'�tait pour le test

void game_tick(GameData& data, Events& events)
{
  // TODO(David): Commence ici
  std::cout << "Game Tick!" << "\n";
  if(events.h_move == HMove::right)
    data.player.pos.x += 1;
  else if(events.h_move == HMove::left)
    data.player.pos.x -= 1;
  if(events.h_move == HMove::none)
    std::cout << "Don't move" << "\n";
  std::cout << data.player.pos.x << "\n";
  

  return;
}
