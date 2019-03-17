#include "renderer.h"
#include "assets.h"

#include <iostream>
#include <cstdio>


// TODO(Sam): Est ce qu'on met �a dans un assets.cpp ?
bool load_assets(Assets& assets)
{
    if (!assets.font.loadFromFile("assets/fonts/ConnectionII.otf"))
		return false;
	return true;
}

void render(GameData const& data, sf::RenderWindow& window, SpritesContainer& game_sprites, Inputs const& inputs)
{

	// Camera
	r32 window_ratio = (r32)window.getSize().x / (r32)window.getSize().y;
	r32 const seen_world_width(10*window_ratio), seen_world_height(10);
	sf::View view(sf::FloatRect(0,0, seen_world_width, seen_world_height));
	view.setCenter(data.camera.pos.x, data.camera.pos.y);
	window.setView(view);

    vector const TOP_LEFT = {data.camera.pos.x - 0.5f*seen_world_width,
							 data.camera.pos.y - 0.5f*seen_world_height};
	vector const BOTTOM_RIGHT =  {data.camera.pos.x + 0.5f*seen_world_width,
								  data.camera.pos.y + 0.5f*seen_world_height};
	
	//lifebar
	sf::RectangleShape life_bar_bg(sf::Vector2f(.5, .05));
	sf::RectangleShape life_bar_fg(sf::Vector2f(.5, .05));
	life_bar_bg.setOrigin(.5,.05);
	life_bar_fg.setOrigin(.5,.05);
	life_bar_bg.setFillColor(sf::Color::Cyan);
	life_bar_fg.setFillColor(sf::Color::Blue);

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

	// =================================================================================
	window.clear(sf::Color::White);

#if 1
	// Damier temporaire
	
	vector size = BOTTOM_RIGHT-TOP_LEFT;

    r32 tile_size = 2.f;
	u32 nb_tile_x = (u32)(size.x/tile_size)+3;
	u32 nb_tile_y = (u32)(size.y/tile_size)+3;

	i32 top_left_x = (i32)((TOP_LEFT.x-tile_size)/tile_size);
	i32 top_left_y = (i32)((TOP_LEFT.y-tile_size)/tile_size);

	top_left_x += (top_left_x)%2;
	top_left_y += (top_left_y)%2;

	top_left_x *= tile_size;
	top_left_y *= tile_size;
	
	sf::RectangleShape tile({tile_size, tile_size});
	tile.setFillColor({100,100,100});
	for(u32 x(0); x < nb_tile_x; ++x)
	{
		for(u32 y(0); y < nb_tile_y; ++y)
		{
			if((top_left_x+x)%2 == (top_left_y+y)%2)
			{
				tile.setPosition(top_left_x + x*tile_size,
								 top_left_y + y*tile_size);
				window.draw(tile);
			}
		}
	}
							 
#endif	
	
	// Le rendu va ici...
	for(auto& e: data.entities)
	{
		if(e.type == ET_player) continue;
		
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
		if(p.type == PT_swap_bullet)
			projectile.setFillColor(sf::Color::Red);
		else
			projectile.setFillColor(sf::Color::Blue);
			
		projectile.setPosition(p.pos.x,p.pos.y);
		window.draw(projectile);
	}

	if(data.player->tp_charge > 0)
	{
		// sf::CircleShape tp_target(.20);
		// tp_target.setOrigin(.20,.20);
		// tp_target.setFillColor(sf::Color::Green);
		// tp_target.setPosition(data.player->pos.x + (data.player->tp_charge * inputs.direction1.x),
		// 	data.player->pos.y + data.player->tp_charge * inputs.direction1.y);
		// window.draw(tp_target);

		game_sprites.tp_target_sprite.setPosition(data.player->pos.x + (data.player->tp_charge * inputs.direction1.x),
			data.player->pos.y + data.player->tp_charge * inputs.direction1.y);
		window.draw(game_sprites.tp_target_sprite);
	}

	//TODO(Dav)
	//This camera let draw static elements, use another view instead?
	sf::Vector2f topLeftOfWindow = window.mapPixelToCoords(sf::Vector2i(0, 0));

	// Weapons/Tools' bar
	for(size_t i(0); i < data.player->weapons.size(); i++)
	{
		// One boxe
		r32 width(1);
		r32 thickness(0.1);
		sf::RectangleShape box(sf::Vector2f(width,width));
		box.setOutlineThickness(0.1);
		box.setOutlineColor(sf::Color::Black);

		// Fill it if selected, else transparent
		if(data.player->weapon_id == i)
			box.setFillColor(sf::Color::Yellow);
		else
			box.setFillColor(sf::Color::Transparent);


		box.setPosition(i*(width+ thickness)+topLeftOfWindow.x + 4, 8 + topLeftOfWindow.y);
		window.draw(box);

		if(data.player->weapons[i].type == GT_pistol)
		{
			game_sprites.basic_pistol_sprite.setPosition(i*(width+ thickness)+topLeftOfWindow.x + 4 + width/2, 8 + topLeftOfWindow.y + width/2);
			window.draw(game_sprites.basic_pistol_sprite);
		}
		else if(data.player->weapons[i].type == GT_swapper)
		{
			game_sprites.swapper_pistol_sprite.setPosition(i*(width+ thickness)+topLeftOfWindow.x + 4 + width/2, 8 + topLeftOfWindow.y + width/2);
			window.draw(game_sprites.swapper_pistol_sprite);
		}
	}

	window.draw(text);
	
	window.display();
	
	return;
}


TexturesContainer loadTextures()
{
	TexturesContainer textures;

	textures.basic_pistol_texture.loadFromFile("ressources/basic_pistol.png");//Attention,Path n'est valable que si le programme est lancé depuis la racine!
	// if (!basic_pistol_texture.loadFromFile("ressources/basic_pistol.png"))
	// {
	// 	// erreur...
	// }


	textures.swapper_pistol_texture.loadFromFile("ressources/swapper_pistol.png");
	textures.tp_target_texture.loadFromFile("ressources/tp_target2.png");

	return textures;
}
SpritesContainer loadSprites(TexturesContainer& textures)
{
	SpritesContainer sprites;
	
	//basic_pistol
	sprites.basic_pistol_sprite.setTexture(textures.basic_pistol_texture);
	sprites.basic_pistol_sprite.setScale(sf::Vector2f(0.05f, 0.05f));
	sprites.basic_pistol_sprite.setOrigin(sprites.basic_pistol_sprite.getTextureRect().width * 0.5,sprites.basic_pistol_sprite.getTextureRect().height * 0.5);

	//Swapper_pistol

    sprites.swapper_pistol_sprite.setTexture(textures.swapper_pistol_texture);
	sprites.swapper_pistol_sprite.setScale(sf::Vector2f(0.04f, 0.04f));
	sprites.swapper_pistol_sprite.setOrigin(sprites.swapper_pistol_sprite.getTextureRect().width * 0.5,sprites.swapper_pistol_sprite.getTextureRect().height * 0.5);

	//tp_target
	sprites.tp_target_sprite.setTexture(textures.tp_target_texture);
	sprites.tp_target_sprite.setScale(sf::Vector2f(0.03f, 0.03f));
	sprites.tp_target_sprite.setOrigin(sprites.tp_target_sprite.getTextureRect().width * 0.5,sprites.tp_target_sprite.getTextureRect().height * 0.5);

	return sprites;
}