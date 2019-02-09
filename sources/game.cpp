#include "game.h"

#include <iostream> // TODO: A enlever, c'�tait pour le test

void game_tick(GameData& data, Events& events)
{
  //TODO : Handle combinaison of Horizontal and Vertical move
  // TODO(David): Commence ici
  std::cout << "Game Tick!" << "\n";

  //Horizontal Move
  if(events.h_move == HM_RIGHT)
    data.player.pos.x += 1;
  else if(events.h_move == HM_LEFT)
    data.player.pos.x -= 1;
  else
    std::cout << "Don't move H" << "\n";

  //Vertical Move
  if(events.v_move == VM_DOWN)
    data.player.pos.y += 1;
  else if(events.v_move == VM_UP)
    data.player.pos.y -= 1;
  else
    std::cout << "Don't move V" << "\n";
  

  return;
}
