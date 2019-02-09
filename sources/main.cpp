#include <SFML\Graphics.hpp>

#include "intrinsic.h"
#include "game.h"

int main()
{
	const u32 GAME_WIDTH(800), GAME_HEIGHT(600);

	sf::RenderWindow window(sf::VideoMode(GAME_WIDTH, GAME_HEIGHT), "Game");
	
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

#if 0

	GameData data;
	Events events;
	
	game_tick(data, events);
  
	return 0;
#endif
}
