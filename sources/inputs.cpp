#include "inputs.h"
#include "intrinsic.h"

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
	vector direction(0,0);
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			direction.y -= 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			direction.y += 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			direction.x -= 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			direction.x += 1;
	}
	if (sf::Joystick::isConnected(0) and
		sf::Joystick::hasAxis(0, sf::Joystick::X) and
		sf::Joystick::hasAxis(0, sf::Joystick::Y))
	{
		// Note: Ici on ecrase pas direction, on ajoute juste a l'ancienne calculee avec
		// les touches car on veux pouvoir utiliser les deux controllers a la fois.
		direction.x += sf::Joystick::getAxisPosition(0, sf::Joystick::X)/100.f;
		direction.y += sf::Joystick::getAxisPosition(0, sf::Joystick::Y)/100.f;
		if(std::abs(direction.x) < 0.1f) direction.x = 0;
		if(std::abs(direction.y) < 0.1f) direction.y = 0;
	}
	r32 norm_direction(norm(direction));
	if(norm_direction > 1.f)
		direction /= norm_direction;
		
	inputs.direction = direction;
    
	return inputs;
}
