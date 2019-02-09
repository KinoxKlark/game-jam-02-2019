#include "inputs.h"
#include <cmath>

Inputs get_inputs(sf::Window& window)
{
	Inputs inputs;
	sf::Event event;

	inputs.direction = vector(0,0);
	inputs.quit_game = false;

	while(window.pollEvent(event))
	{
				
		if(event.type == sf::Event::Closed)
			inputs.quit_game = true;

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
				inputs.quit_game = true;
					
			if (event.key.code == sf::Keyboard::Up)
				inputs.direction.y -= 1;
			if (event.key.code == sf::Keyboard::Down)
				inputs.direction.y += 1;
			if (event.key.code == sf::Keyboard::Left)
				inputs.direction.x -= 1;
			if (event.key.code == sf::Keyboard::Right)
				inputs.direction.x += 1;
		}
	}
	
	r32 norme(std::sqrt((inputs.direction.x * inputs.direction.x) +
				   (inputs.direction.y * inputs.direction.y)));
	if(norme)
		inputs.direction /= norme;


	return inputs;
}
