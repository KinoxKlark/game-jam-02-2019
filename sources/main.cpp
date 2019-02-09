#include <SFML/Graphics.hpp>


#include "intrinsic.h"
#include "inputs.h"
#include "game.h"
#include "renderer.h"

int main()
{
	const u32 GAME_WIDTH(800), GAME_HEIGHT(600);
	const u32 FRAME_PER_SECONDS(60);
	const i32 FRAME_LENGTH_MILLISECONDS(1000.f/FRAME_PER_SECONDS);

	GameData data;
	
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
		    Inputs inputs = get_inputs(window);
			inputs.delta_time = FRAME_LENGTH_MILLISECONDS;
			
			// Game Logique
			game_tick(data, inputs);
			
			// Game Render
			render(data,window,inputs);
			// TODO(Sam): Faut enlever les input d'ici, je l'ai mis seulement pour qu'on
			// puisse afficher dans le debug. Faudra a terme trouver une meilleur solution

			// Quit game
			if(inputs.quit_game)
			{
				window.close();
			}
		}
	}

	return 0;

#if 0

	
  
	return 0;
#endif
}
