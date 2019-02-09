#include <SFML/Graphics.hpp>
#include <cmath>


#include "intrinsic.h"
#include "game.h"
#include "renderer.h"

int main()
{
	const u32 GAME_WIDTH(800), GAME_HEIGHT(600);
	const u32 FRAME_PER_SECONDS(60);
	const i32 FRAME_LENGTH_MILLISECONDS((r32)1/(r32)FRAME_PER_SECONDS);

	GameData data;
	Inputs inputs;
	
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
#if 0 
			elapsed_time -= FRAME_LENGTH_MILLISECONDS;
#else
			elapsed_time = sf::Time::Zero;
#endif

            // R�cup�ration des inputs
			sf::Event e;
			inputs.direction = vector(0,0);

			while(window.pollEvent(e))
			{
				
				if(e.type == sf::Event::Closed)
					window.close();
				//Plus rapide pour fermer la fenetre, je préfère ça qu'interrompre le programme, il faudra le gerer proprement
				if (e.type == sf::Event::KeyPressed)
				{
					if (e.key.code == sf::Keyboard::Escape)
						window.close();
					
					if (e.key.code == sf::Keyboard::Up)
						inputs.direction.y -= 1;
					if (e.key.code == sf::Keyboard::Down)
						inputs.direction.y += 1;
					if (e.key.code == sf::Keyboard::Left)
						inputs.direction.x -= 1;
					if (e.key.code == sf::Keyboard::Right)
						inputs.direction.x += 1;
				}
			}
			r32 norme(sqrt((inputs.direction.x * inputs.direction.x) + (inputs.direction.y * inputs.direction.y)));
			if(norme)
				inputs.direction /= norme;


			// Game Logique
			game_tick(data, inputs);
			
			// Game Render
			// ...
			render(data,window);
			
		}
	}

	return 0;

#if 0

	
  
	return 0;
#endif
}
