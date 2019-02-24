#ifndef INPUTS_H
#define INPUTS_H

#include "intrinsic.h"
#include <SFML/Window.hpp>

struct Inputs {
    vector  direction1,
		    direction2;
    r32 delta_time;
	
	bool quit_game;
    bool primaire_start, primaire_end;
	bool secondaire_start, secondaire_end;
    bool charging_tp;
    bool shooting;
    bool action3;
    bool action4;
	
	sf::Vector2i mouse_pos_tmp;
	sf::Vector2u winsize_tmp;
};

// TODO(Dav):
//      Plus généraliser pour pouvoir faire "if(config.up)"
//      Permettre autre chose que la configuration des touches? (ex: mouse click?)
//      InputsConfig est lié au joueur: attribut de GameData?
struct InputsConfig {
    // sf::Keyboard::isKeyPressed
    sf::Keyboard::Key
		up,
		down,
		left,
		right,
        charging_tp,
        shooting,
        action3,
        action4,
        escape;
    // sf::Mouse::isButtonPressed
    // sf::Mouse::Button
    //     shooting;
};

InputsConfig get_inputs_config();

Inputs default_inputs();

Inputs get_inputs(sf::Window& window,InputsConfig inputs_config, i32 delta_time_ms);

#endif
