#include <SFML\Graphics.hpp>
#include "game.h"

int main()
{
#if 0
  sf::RenderWindow window(sf::VideoMode(800,600), "Hello Game");
  while(window.isOpen())
  {
    sf::Event e;
    while(window.pollEvent(e))
    {
      if(e.type == sf::Event::Closed)
	window.close();
    }
  }

  return 0;
#endif
  // ...
  
  GameData data;
  Events events;
  
  game_tick(data, events);
  
  return 0;
}
