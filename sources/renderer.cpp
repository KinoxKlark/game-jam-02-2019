#include "renderer.h"
#include "assets.h"

#include <cstdio>

// TODO(Sam): Est ce qu'on met �a dans un assets.cpp ?
bool load_assets(Assets& assets)
{
    if (!assets.font.loadFromFile("assets/fonts/ConnectionII.otf"))
		return false;
	return true;
}

void render(GameData const& data, sf::RenderWindow& window, Inputs const& inputs)
{
	//Center the view on the player
	sf::View view(sf::FloatRect(0,0, window.getSize().x, window.getSize().y));
	view.setCenter(data.camera.pos.x, data.camera.pos.y);
	window.setView(view);

	// TODO(Sam): Fair un vrai syst�me d'asset
	sf::CircleShape player(50);
	player.setOrigin(50,50);
	player.setFillColor(sf::Color::Red);
	player.setPosition(data.player.pos.x,data.player.pos.y);


	sf::CircleShape ennemies(50);
	ennemies.setOrigin(50,50);
	ennemies.setFillColor(sf::Color::Black);

	sf::CircleShape projectile(10);
	projectile.setOrigin(10,10);
	projectile.setFillColor(sf::Color::Blue);

	// TODO(Sam): Une GUI qui tient la route...
	char debug_string[1024];
	std::sprintf(debug_string, "FPS: %f \nDirection1.x = %f \nDirection1.y = %f \nDirection2.x = %f \nDirection2.y = %f \nMouse.x = %d \nMouse.y = %d \nWidth = %d \nHeight = %d",
				 1000.f/data.debug_infos.frame_length_milliseconds,
				 inputs.direction1.x,
				 inputs.direction1.y,
				 inputs.direction2.x,
				 inputs.direction2.y,
				 inputs.mouse_pos_tmp.x,
				 inputs.mouse_pos_tmp.y,
				 inputs.winsize_tmp.x,
				 inputs.winsize_tmp.y);
    sf::Text text(debug_string, data.assets.font, 18);
	text.setFillColor(sf::Color::Black);

	// end tmp

	window.clear(sf::Color::White);
	
	// Le rendu va ici...
	for(auto& e: data.ennemies)
	{
		ennemies.setPosition(e.pos.x,e.pos.y);
		window.draw(ennemies);
	}

	window.draw(player);

	for(auto& p: data.projectiles)
	{
		projectile.setPosition(p.pos.x,p.pos.y);
		window.draw(projectile);
	}

	if(data.player.tp_charge > 0)
	{
		sf::CircleShape tp_target(20);
		tp_target.setOrigin(20,20);
		tp_target.setFillColor(sf::Color::Green);
		tp_target.setPosition(data.player.pos.x + (data.player.tp_charge * inputs.direction1.x),
		data.player.pos.y + data.player.tp_charge * inputs.direction1.y);
		window.draw(tp_target);
	}

	window.draw(text);
	
	window.display();
	
	return;
}
