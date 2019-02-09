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
		// Fermeture de la fenetre
		if(event.type == sf::Event::Closed or
		   (event.type == sf::Event::KeyPressed and
			event.key.code == sf::Keyboard::Escape))
			inputs.quit_game = true;
	}

	
	// Recuperation de la direction
	if (sf::Joystick::isConnected(0) and
		sf::Joystick::hasAxis(0, sf::Joystick::X) and
		sf::Joystick::hasAxis(0, sf::Joystick::Y))
	{
		vector direction(0,0);
		direction.x = sf::Joystick::getAxisPosition(0, sf::Joystick::X)/100.f;
		direction.y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y)/100.f;
		if(std::abs(direction.x) < 0.1f) direction.x = 0;
		if(std::abs(direction.y) < 0.1f) direction.y = 0;

		r32 norme(std::sqrt((direction.x * direction.x) +
							(direction.y * direction.y)));

		if(norme > 1.f)
			direction /= norme;
		
		inputs.direction = direction;
	}
	else
	{
		vector direction(0,0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			direction.y -= 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			direction.y += 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			direction.x -= 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			direction.x += 1;

		r32 norme(std::sqrt((direction.x * direction.x) +
							(direction.y * direction.y)));
		inputs.direction = direction / (norme != 0.0 ? norme : 1);
	}

	return inputs;
}
