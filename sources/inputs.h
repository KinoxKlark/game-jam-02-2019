#ifndef INPUTS_H
#define INPUTS_H

#include "intrinsic.h"
#include <SFML/Window.hpp>

struct Inputs {
    vector direction1,
		direction2;
    r32 delta_time;
	
	bool quit_game;
    bool primaire_start, primaire_end;
	bool secondaire_start, secondaire_end;

	sf::Vector2i mouse_pos_tmp;
	sf::Vector2u winsize_tmp;
};

Inputs get_inputs(sf::Window& window);

#endif
