#ifndef INPUTS_H
#define INPUTS_H

#include "intrinsic.h"
#include <SFML/Window.hpp>

struct Inputs {
    vector direction;
	bool quit_game;
    r32 delta_time;
};

Inputs get_inputs(sf::Window& window);

#endif
