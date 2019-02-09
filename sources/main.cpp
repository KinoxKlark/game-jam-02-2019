#include <SFML/Graphics.hpp>


#include "intrinsic.h"
#include "game.h"
#include "renderer.h"

int main()
{
	const u32 GAME_WIDTH(800), GAME_HEIGHT(600);
	const u32 FRAME_PER_SECONDS(60);
	const i32 FRAME_LENGTH_MILLISECONDS(1000.f/FRAME_PER_SECONDS);

	GameData data;
	Events events;

	game_init(data);

	data.debug_infos.frame_length_milliseconds = 0;
	
	sf::RenderWindow window(sf::VideoMode(GAME_WIDTH, GAME_HEIGHT), "Game");

	sf::Clock clock;
	sf::Time last_timestamp(clock.getElapsedTime());
	sf::Time elapsed_time(sf::Time::Zero);
	
	while(window.isOpen())
	{
		
		sf::Time current_timestamp(clock.getElapsedTime());
		elapsed_time = current_timestamp - last_timestamp;
	    if(elapsed_time.asMilliseconds() > FRAME_LENGTH_MILLISECONDS)
		{
			data.debug_infos.frame_length_milliseconds = elapsed_time.asMilliseconds();
			last_timestamp = current_timestamp;

            // Recuperation des inputs
			sf::Event e;
			events.h_move = HM_RIGHT;
			events.v_move = VM_DOWN;
			while(window.pollEvent(e))
			{
				if(e.type == sf::Event::Closed)
					window.close();
				//Plus rapide pour fermer la fenetre, je préfère ça qu'interrompre le programme, il faudra le gerer proprement
				if (e.type == sf::Event::KeyPressed)
				{
					if (e.key.code == sf::Keyboard::Escape)
						window.close();
				}
			}


			// Game Logique
			game_tick(data, events);
			
			// Game Render
			render(data,window);

			
		}
	}

	return 0;

#if 0

	
  
	return 0;
#endif
}