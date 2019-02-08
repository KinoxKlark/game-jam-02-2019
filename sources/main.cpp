#include <iostream>
#include "game.h"

int main()
{
  std::cout << "Hello Game Jam!" << "\n";

  GameData data;
  Events events;

  game_tick(data, events);
  
  return 0;
}
