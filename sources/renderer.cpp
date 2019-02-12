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
	//lifebar
	sf::RectangleShape life_bar_bg(sf::Vector2f(.5, .05));
	sf::RectangleShape life_bar_fg(sf::Vector2f(.5, .05));
	life_bar_bg.setOrigin(.5,.05);
	life_bar_fg.setOrigin(.5,.05);
	life_bar_bg.setFillColor(sf::Color::Cyan);
	life_bar_fg.setFillColor(sf::Color::Blue);

	// Camera
	r32 window_ratio = (r32)window.getSize().x / (r32)window.getSize().y;
	sf::View view(sf::FloatRect(0,0, 10*window_ratio, 10));
	view.setCenter(data.camera.pos.x, data.camera.pos.y);
	window.setView(view);

	// TODO(Sam): Fair un vrai systeme d'asset
	r32 player_radius = .5f;
	sf::CircleShape player(player_radius),
		player_direction(.1);
	player.setOrigin(player_radius,player_radius);
	player_direction.setOrigin(.1,.1);
	player.setFillColor(sf::Color::Red);
	player_direction.setFillColor(sf::Color::Red);
	player.setPosition(data.player->pos.x,data.player->pos.y);
	player_direction.setPosition(
		data.player->pos.x + data.player->orientation.x*player_radius,
		data.player->pos.y + data.player->orientation.y*player_radius);

	sf::CircleShape camera_focus(.05);
	camera_focus.setOrigin(.05,.05);
	camera_focus.setFillColor(sf::Color::Black);
	camera_focus.setPosition(data.camera.focus_pos.x, data.camera.focus_pos.y);

	sf::CircleShape entities(.5);
	entities.setOrigin(.5,.5);
	entities.setFillColor(sf::Color::Black);

	sf::CircleShape projectile(.1);
	projectile.setOrigin(.1,.1);
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
    sf::Text text(debug_string, data.assets.font, .18);
	text.setFillColor(sf::Color::Black);

	// end tmp

	window.clear(sf::Color::White);
	
	// Le rendu va ici...
	for(auto& e: data.entities)
	{
		if(&e == data.player) continue;
		
		entities.setPosition(e.pos.x,e.pos.y);

		life_bar_fg.setSize(
			sf::Vector2f(life_bar_bg.getSize().x * e.life
						 / e.life_max, life_bar_bg.getSize().y));
		life_bar_bg.setPosition(e.pos.x,e.pos.y - .6);
		life_bar_fg.setPosition(e.pos.x,e.pos.y - .6);

		window.draw(entities);
		window.draw(life_bar_bg);
		window.draw(life_bar_fg);
	}

	life_bar_fg.setSize(
		sf::Vector2f(life_bar_bg.getSize().x * data.player->life
					 / data.player->life_max, life_bar_bg.getSize().y));
	life_bar_bg.setPosition(data.player->pos.x,data.player->pos.y - .60);
	life_bar_fg.setPosition(data.player->pos.x,data.player->pos.y - .60);

	window.draw(player);
	window.draw(life_bar_bg);
	window.draw(life_bar_fg);

	window.draw(player_direction);
	window.draw(camera_focus);

	for(auto& p: data.projectiles)
	{
		projectile.setPosition(p.pos.x,p.pos.y);
		window.draw(projectile);
	}

	if(data.player->tp_charge > 0)
	{
		sf::CircleShape tp_target(.20);
		tp_target.setOrigin(.20,.20);
		tp_target.setFillColor(sf::Color::Green);
		tp_target.setPosition(data.player->pos.x + (data.player->tp_charge * inputs.direction1.x),
		data.player->pos.y + data.player->tp_charge * inputs.direction1.y);

		window.draw(tp_target);
	}

	window.draw(text);
	
	window.display();
	
	return;
}
