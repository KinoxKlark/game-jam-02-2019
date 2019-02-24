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

Inputs default_inputs();

Inputs get_inputs(sf::Window& window, i32 delta_time_ms);

#endif
