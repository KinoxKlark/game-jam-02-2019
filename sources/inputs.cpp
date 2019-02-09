#include "inputs.h"
#include "intrinsic.h"

Inputs get_inputs(sf::Window& window)
{
	Inputs inputs;
	sf::Event event;

	inputs.direction1 = vector(0,0);
	inputs.quit_game = false;
	inputs.charging_tp = false;

	while(window.pollEvent(event))
	{
		// Fermeture de la fenetre
		if(event.type == sf::Event::Closed or
		   (event.type == sf::Event::KeyPressed and
			event.key.code == sf::Keyboard::Escape))
			inputs.quit_game = true;
	}

	
	// Recuperation de la direction1
	vector direction1(0,0);
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			direction1.y -= 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			direction1.y += 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			direction1.x -= 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			direction1.x += 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
			inputs.charging_tp = true;
		
	}
	if (sf::Joystick::isConnected(0) and
		sf::Joystick::hasAxis(0, sf::Joystick::X) and
		sf::Joystick::hasAxis(0, sf::Joystick::Y))
	{
		// Note: Ici on ecrase pas direction1, on ajoute juste a l'ancienne calculee avec
		// les touches car on veux pouvoir utiliser les deux controllers a la fois.
		direction1.x += sf::Joystick::getAxisPosition(0, sf::Joystick::X)/100.f;
		direction1.y += sf::Joystick::getAxisPosition(0, sf::Joystick::Y)/100.f;
		if(std::abs(direction1.x) < 0.1f) direction1.x = 0;
		if(std::abs(direction1.y) < 0.1f) direction1.y = 0;
	}
	r32 norm_direction1(norm(direction1));
	if(norm_direction1 > 1.f)
		direction1 /= norm_direction1;
    inputs.direction1 = direction1;

	
	// Recuperation de la direction2
	vector direction2(0,0);
#if 1
	if (sf::Joystick::isConnected(0) and
		sf::Joystick::hasAxis(0, sf::Joystick::Z) and
		sf::Joystick::hasAxis(0, sf::Joystick::R))
	{
		direction2.x += sf::Joystick::getAxisPosition(0, sf::Joystick::Z)/100.f;
		direction2.y += sf::Joystick::getAxisPosition(0, sf::Joystick::R)/100.f;
		if(std::abs(direction2.x) < 0.1f) direction2.x = 0;
		if(std::abs(direction2.y) < 0.1f) direction2.y = 0;
	}
	else
	{
		sf::Vector2u window_size(window.getSize());
		sf::Vector2i mouse_pos(sf::Mouse::getPosition(window));

		inputs.mouse_pos_tmp = mouse_pos;
		inputs.winsize_tmp = window_size;
		
		direction2.x += (mouse_pos.x - (i32)window_size.x/2);
		direction2.y += (mouse_pos.y - (i32)window_size.y/2);
	}
#else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			direction2.y = -1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			direction2.y = 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			direction2.x = -1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			direction2.x = 1;
	}
#endif
	r32 norm_direction2(norm(direction2));
	if(norm_direction2 > 1.f)
		direction2 /= norm_direction2;
    inputs.direction2 = direction2;

	return inputs;
}
