#include "inputs.h"
#include "intrinsic.h"
#include "inputs.h"

#include <iostream>

struct InputsHelper {
	struct Keyboard {
		struct Key {
			sf::Keyboard::Key sfml_key;
			r32 strength;
		};

		// TODO(Sam): Est ce qu'on veut gerer ca avec
		// une map a terme ? David: le fonctionnement ne dépendra pas de la config,
		// la config donne les valeurs à l'initalisation
		Key W, A, S, D;
	};

	Keyboard keyboard;
};


void updateHelperKeys(InputsHelper::Keyboard::Key& key, i32 dt_ms)
{
	constexpr r32 KEY_ATTACK_SPEED = 1.f / 200.f;
	constexpr r32 KEY_RELEASE_SPEED = KEY_ATTACK_SPEED;
	if(sf::Keyboard::isKeyPressed(key.sfml_key))
	{
		key.strength += KEY_ATTACK_SPEED*dt_ms;
	}
	else
	{
		key.strength -= KEY_RELEASE_SPEED*dt_ms;
	}

	if(key.strength < 0.f) key.strength = 0.f;
	if(key.strength > 1.f) key.strength = 1.f;

}


void updateHelper(InputsHelper& helper, i32 dt_ms)
{
	updateHelperKeys(helper.keyboard.W, dt_ms);
	updateHelperKeys(helper.keyboard.A, dt_ms);
	updateHelperKeys(helper.keyboard.S, dt_ms);
	updateHelperKeys(helper.keyboard.D, dt_ms);
}


InputsHelper initHelper(InputsConfig config)
{
	InputsHelper helper;
	helper.keyboard.W = { config.up, 0.f };
	helper.keyboard.A = { config.left, 0.f };
	helper.keyboard.S = { config.down, 0.f };
	helper.keyboard.D = { config.right, 0.f };

	return helper;
}

// TODO(Dav): Pouvoir charger une config depuis un fichier externe
//						renommer en "défault config" quand on aura un autre moyen de charger la config
InputsConfig get_inputs_config(){
	InputsConfig conf;
	// sf::Keyboard::isKeyPressed
	conf.up = sf::Keyboard::W;
	conf.down = sf::Keyboard::S;
	conf.left = sf::Keyboard::A;
	conf.right = sf::Keyboard::D;
	conf.charging_tp = sf::Keyboard::C;
	conf.shooting = sf::Keyboard::Space;
	conf.action3 = sf::Keyboard::R;
	conf.action4 = sf::Keyboard::E;
	conf.escape = sf::Keyboard::Escape;

	// sf::Mouse::isButtonPressed
	// conf.shooting = sf::Mouse::Button::Left;
	return conf;
}


Inputs default_inputs()
{
	Inputs inputs;
	sf::Event event;

	inputs.direction1 = vector(0,0);
	inputs.quit_game = false;
	inputs.charging_tp = false;
	inputs.shooting = false;
	inputs.action3 = false;
	inputs.action4 = false;

	return inputs;
}

//Prends en paramètre la config du joueur, semble logique, mais est-ce bien?
// Proposition: renommer en get_player_inputs et prendre un paramètre supplémentaire désignant le player (Nécessaire pour jouer en ligne)
Inputs get_inputs(sf::Window& window,InputsConfig inputs_config, i32 delta_time_ms)
{
	static InputsHelper helper = initHelper(inputs_config);
	updateHelper(helper, delta_time_ms);

	// Create inputs
	Inputs inputs(default_inputs());
	inputs.delta_time = delta_time_ms / 1000.f;// delta_time in seconds

	// Create event
	sf::Event event;


	// Fenetre
	while(window.pollEvent(event))
	{
		// Fermeture de la fenetre
		if(event.type == sf::Event::Closed or
		   (event.type == sf::Event::KeyPressed and
			event.key.code == inputs_config.escape))
			inputs.quit_game = true;
		if (event.type == sf::Event::KeyPressed and
				event.key.code == inputs_config.action4)
			inputs.action4 = true;
		
			
	}

	// Action Primaire
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			inputs.shooting = true;
		if (sf::Joystick::isConnected(0) and sf::Joystick::isButtonPressed(0, 5))
			inputs.shooting = true;
		if (sf::Keyboard::isKeyPressed(inputs_config.shooting))
			inputs.shooting = true;
	}

	// Action Secondaire
	{
		// Doublons de touche pour la même action, enlever un et mettre simplement changer de config
		if (sf::Keyboard::isKeyPressed(inputs_config.charging_tp))
			inputs.charging_tp = true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
			inputs.charging_tp = true;
		if (sf::Joystick::isConnected(0) and sf::Joystick::isButtonPressed(0, 6))
			inputs.charging_tp = true;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
			inputs.charging_tp = true;
    }

	
	// Action Tertiaire
	{
		if (sf::Joystick::isConnected(0) and sf::Joystick::isButtonPressed(0, 1))
			inputs.action3 = true;
		if (sf::Keyboard::isKeyPressed(inputs_config.action3))
			inputs.action3 = true;
		// if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		// 	inputs.action4 = true;
			
	}
	
	// Recuperation de la direction1
	vector direction1(0,0);
	{
#if 1
		direction1.y -= helper.keyboard.W.strength;
		direction1.y += helper.keyboard.S.strength;
		direction1.x -= helper.keyboard.A.strength;
		direction1.x += helper.keyboard.D.strength;
#else		
		if (sf::Keyboard::isKeyPressed(inputs_config.up))
			direction1.y -= 1;
		if (sf::Keyboard::isKeyPressed(inputs_config.left))
			direction1.y += 1;
		if (sf::Keyboard::isKeyPressed(inputs_config.down))
			direction1.x -= 1;
		if (sf::Keyboard::isKeyPressed(inputs_config.right))
			direction1.x += 1;
#endif		
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
