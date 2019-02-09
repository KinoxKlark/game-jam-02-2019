#include <SFML\Graphics.hpp>


#include "intrinsic.h"
#include "game.h"
#include "renderer.h"

int main()
{
	const u32 GAME_WIDTH(800), GAME_HEIGHT(600);
	const u32 FRAME_PER_SECONDS(60);
	const i32 FRAME_LENGTH_MILLISECONDS((r32)1/(r32)FRAME_PER_SECONDS);

	GameData data;
	Events events;
	
	sf::RenderWindow window(sf::VideoMode(GAME_WIDTH, GAME_HEIGHT), "Game");

	sf::Clock clock;
	sf::Time last_timestamp(clock.getElapsedTime());
	sf::Time elapsed_time(sf::Time::Zero);
	
	while(window.isOpen())
	{
		
		sf::Time current_timestamp(clock.getElapsedTime());
		elapsed_time += current_timestamp - last_timestamp;
		last_timestamp = current_timestamp;
		while(elapsed_time.asMilliseconds() > FRAME_LENGTH_MILLISECONDS)
		{
			// Gestion du timing
#if 0 
			elapsed_time -= FRAME_LENGTH_MILLISECONDS;
#else
			elapsed_time = sf::Time::Zero;
#endif

            // Récupération des inputs
			sf::Event e;
			while(window.pollEvent(e))
			{
				if(e.type == sf::Event::Closed)
					window.close();
			}


			// Game Logique
			game_tick(data, events);
			
			// Game Render
			render(data, window);
			
		}
	}

	return 0;

#if 0

	
  
	return 0;
#endif
}
